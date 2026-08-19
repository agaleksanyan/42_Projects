"""Time-reserved scheduling for the drone simulation."""

from __future__ import annotations

from typing import TYPE_CHECKING

from algorithms.path_selector import PathSelector
from models.drone import Drone
from models.zone import Zone
from simulation.turn import Move, Turn
from utils.exceptions import AlgorithmError

if TYPE_CHECKING:
    from models.connection import Connection
    from models.graph import Graph
    from simulation.state import SimulationState


class Scheduler:
    """Build and replay a capacity-safe schedule using shortest paths only."""

    _MAX_SCHEDULED_TURNS = 10_000

    def __init__(
        self,
        graph: Graph,
        path_selector: PathSelector | None = None,
    ) -> None:
        self._graph = graph
        self._path_selector = path_selector or PathSelector(graph)
        self._planned_moves: dict[int, list[Move]] | None = None

    def schedule(self, state: SimulationState) -> Turn:
        """Return the capacity-safe moves scheduled for the next turn."""
        if self._planned_moves is None:
            self._planned_moves = self._build_plan(state)

        turn_number = state.current_turn + 1
        moves = self._planned_moves.get(turn_number, [])
        return Turn(moves=list(moves))

    def _build_plan(self, state: SimulationState) -> dict[int, list[Move]]:
        """Reserve every drone's shortest path in a shared time table.

        A restricted move starts on turn ``T`` and reaches its destination on
        turn ``T + 1``. The zone table records occupancy at the end of every
        turn, so a following drone may start transit on ``T`` when the first
        drone will leave the destination on ``T + 1``. This is the pipeline
        handoff required by the movement rules.
        """
        planned_moves: dict[int, list[Move]] = {}
        zone_occupancy: dict[tuple[int, Zone], int] = {}
        connection_usage: dict[tuple[int, Connection], int] = {}

        for drone in sorted(state.drones, key=lambda item: item.id):
            path = self._path_selector.find_path(
                state.graph.start,
                state.graph.end,
            )
            drone.path = list(path.zones)
            drone.path_index = 0

            self._reserve_drone_path(
                drone,
                path.zones,
                path.connections,
                planned_moves,
                zone_occupancy,
                connection_usage,
            )

        return planned_moves

    def _reserve_drone_path(
        self,
        drone: Drone,
        zones: list[Zone],
        connections: list[Connection],
        planned_moves: dict[int, list[Move]],
        zone_occupancy: dict[tuple[int, Zone], int],
        connection_usage: dict[tuple[int, Connection], int],
    ) -> None:
        """Reserve the earliest legal slots for one already-selected path."""
        next_turn = 1
        zone_arrival_turn: int | None = None

        for index, destination in enumerate(zones[1:]):
            source = zones[index]
            connection = connections[index]
            move_turn = self._find_earliest_move_turn(
                next_turn,
                destination,
                connection,
                zone_occupancy,
                connection_usage,
            )

            if zone_arrival_turn is not None:
                self._reserve_zone_stay(
                    source,
                    zone_arrival_turn,
                    move_turn,
                    zone_occupancy,
                )

            connection_usage[(move_turn, connection)] = (
                connection_usage.get((move_turn, connection), 0) + 1
            )

            if destination.movement_cost() == 2:
                self._add_move(planned_moves, move_turn, drone, connection)
                arrival_turn = move_turn + 1
                self._add_move(
                    planned_moves,
                    arrival_turn,
                    drone,
                    destination,
                )
            else:
                arrival_turn = move_turn
                self._add_move(
                    planned_moves,
                    arrival_turn,
                    drone,
                    destination,
                )

            zone_arrival_turn = arrival_turn
            next_turn = arrival_turn + 1

    def _find_earliest_move_turn(
        self,
        first_turn: int,
        destination: Zone,
        connection: Connection,
        zone_occupancy: dict[tuple[int, Zone], int],
        connection_usage: dict[tuple[int, Connection], int],
    ) -> int:
        """Find the first turn whose connection and arrival slot are free."""
        move_turn = first_turn
        arrival_delay = destination.movement_cost() - 1

        while move_turn <= self._MAX_SCHEDULED_TURNS:
            arrival_turn = move_turn + arrival_delay
            connection_busy = connection_usage.get(
                (move_turn, connection),
                0,
            ) >= connection.max_link_capacity

            if connection_busy or not self._zone_is_available(
                destination,
                arrival_turn,
                zone_occupancy,
            ):
                move_turn += 1
                continue

            return move_turn

        raise AlgorithmError(
            "Could not reserve a legal movement within "
            f"{self._MAX_SCHEDULED_TURNS} turns."
        )

    @staticmethod
    def _zone_is_available(
        zone: Zone,
        turn: int,
        zone_occupancy: dict[tuple[int, Zone], int],
    ) -> bool:
        """Check capacity at the end of a future turn."""
        if zone.is_start or zone.is_end:
            return True
        return zone_occupancy.get((turn, zone), 0) < zone.max_drones

    @staticmethod
    def _reserve_zone_stay(
        zone: Zone,
        arrival_turn: int,
        departure_turn: int,
        zone_occupancy: dict[tuple[int, Zone], int],
    ) -> None:
        """Reserve a zone from arrival until the drone leaves it."""
        if zone.is_start or zone.is_end:
            return

        for turn in range(arrival_turn, departure_turn):
            key = (turn, zone)
            zone_occupancy[key] = zone_occupancy.get(key, 0) + 1

    @staticmethod
    def _add_move(
        planned_moves: dict[int, list[Move]],
        turn: int,
        drone: Drone,
        destination: Zone | Connection,
    ) -> None:
        """Append one scheduled movement to its output turn."""
        planned_moves.setdefault(turn, []).append(
            Move(drone=drone, destination=destination)
        )
