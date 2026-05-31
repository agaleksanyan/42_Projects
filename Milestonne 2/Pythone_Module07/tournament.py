from ex0 import AquaFactory, FlameFactory
from ex0.creature import CreatureFactory
from ex1 import HealingCreatureFactory, TransformCreatureFactory
from ex2 import BattleStrategy
from ex2 import AggressiveStrategy, DefensiveStrategy, NormalStrategy

Opponent = tuple[CreatureFactory, BattleStrategy]


def battle(first: Opponent, second: Opponent) -> None:

    first_factory, first_strategy = first
    second_factory, second_strategy = second

    first_creature = first_factory.create_base()
    second_creature = second_factory.create_base()

    print("* Battle *")

    print(first_creature.describe())
    print("vs.")
    print(second_creature.describe())

    print("now fight!")

    first_strategy.act(first_creature)
    second_strategy.act(second_creature)


def tournament(opponents: list[Opponent]) -> None:

    print("*** Tournament ***")

    print(f"{len(opponents)} opponents involved")

    for i in range(len(opponents)):
        for j in range(i + 1, len(opponents)):
            try:
                battle(opponents[i], opponents[j])
            except ValueError as error:
                print(
                    "Battle error, aborting tournament:",
                    error,
                )
                return


def main() -> None:
    normal = NormalStrategy()
    aggressive = AggressiveStrategy()
    defensive = DefensiveStrategy()

    print("Tournament 0 (basic)")
    print("[ (Flameling+Normal), (Healing+Defensive) ]")
    tournament([
        (FlameFactory(), normal),
        (HealingCreatureFactory(), defensive)
        ])

    print("Tournament 1 (error)")
    print("[ (Flameling+Aggressive), (Healing+Defensive) ]")
    tournament(
        [
            (FlameFactory(), aggressive),
            (HealingCreatureFactory(), defensive),
        ]
    )

    print("Tournament 2 (multiple)")
    print("[ (Aquabub+Normal), (Healing+Defensive), (Transform+Aggressive) ]")
    tournament(
        [
            (AquaFactory(), normal),
            (HealingCreatureFactory(), defensive),
            (TransformCreatureFactory(), aggressive),
        ]
    )


if __name__ == "__main__":
    main()
