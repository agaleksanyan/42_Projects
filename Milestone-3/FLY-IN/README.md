*This project has been created as part of the 42 curriculum by agaleksaX.*

# Fly-in

## Description

Fly-in simulates a fleet of drones moving from one start hub to one end hub
through a graph of connected zones. The scheduler minimizes the number of
simulation turns while respecting zone capacity, connection capacity, blocked
zones, restricted two-turn movements, and priority zones.

For each map, the program parses the network, calculates one Dijkstra shortest
path, assigns every drone to that path, then prints every movement turn by
turn. Restricted zones are reached through their connection on one turn and
arrive on the following turn.

## Instructions

Requirements: Python 3.10 or newer.

```sh
make install
make run MAP=maps/easy/01_linear_path.txt
make run MAP=maps/challenger/01_the_impossible_dream.txt
make run MAP=maps/hard/03_ultimate_challenge.txt FLAG=-v
make lint
```

Available Makefile targets are `install`, `run`, `debug`, `clean`, `lint`, and
`lint-strict`. The map path is passed through the `MAP` variable. Add `FLAG=-v`
to display the animation, or `FLAG=-s` for per-turn snapshots.

## Algorithm and design

The project is object-oriented and separates parsing, graph models,
pathfinding, scheduling, simulation, and visualization.

- Dijkstra provides the normal weighted shortest path, where restricted zones
  cost two turns and priority zones are preferred on equal-cost routes.
- Every drone follows that same shortest path; the scheduler does not select
  alternate routes.
- Before the simulation starts, the scheduler reserves connection usage and
  future zone occupancy for every turn. A drone may enter a restricted
  connection on turn `T` when the preceding drone is guaranteed to leave that
  restricted zone on turn `T + 1`. This creates a safe pipeline without
  exceeding zone or connection capacity.

For a graph with `V` zones and `E` connections, one Dijkstra lookup is
`O((V + E) log V)`. Time reservation is linear in the number of planned moves
plus any required waiting slots. Its memory use is proportional to those
reserved moves and occupancy slots.

## Visual representation

Terminal output uses each zone's optional color and prints one line per turn.
Matplotlib visualization is available with `FLAG=-v` or `FLAG=-s`; it draws
the graph and shows the drones' movements so capacity bottlenecks and
restricted transit are visible.

## Example

```text
$ make run MAP=maps/easy/01_linear_path.txt
Turn  1: D1-zone_a
Turn  2: D1-zone_b D2-zone_a
...
SIMULATION COMPLETE
```

The exact names and number of turns depend on the chosen map. The Challenger
map completes in 43 turns with the included scheduler.

## Resources

- Python documentation: https://docs.python.org/3/
- Dijkstra's algorithm: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
- Breadth-first search: https://en.wikipedia.org/wiki/Breadth-first_search
- 42 Fly-in subject, version 1.6.

AI was used to review the subject requirements, identify a capacity scheduling
bug, design the shortest-path reservation strategy, and generate validation
checks. The resulting code and behavior were reviewed and tested locally.
