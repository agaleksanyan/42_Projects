from ex1 import HealingCreatureFactory, TransformCreatureFactory


def test_healing_factory(factory: HealingCreatureFactory) -> None:

    print("Testing Creature with healing capability")

    base = factory.create_base()
    evolved = factory.create_evolved()

    print("base:")

    print(base.describe())
    print(base.attack())

    print(base.heal())

    print("evolved:")

    print(evolved.describe())
    print(evolved.attack())
    print(evolved.heal())


def test_transform_factory(factory: TransformCreatureFactory) -> None:

    print("Testing Creature with transform capability")

    base = factory.create_base()
    evolved = factory.create_evolved()

    print("base:")

    print(base.describe())
    print(base.attack())
    print(base.transform())
    print(base.attack())
    print(base.revert())

    print("evolved:")

    print(evolved.describe())
    print(evolved.attack())
    print(evolved.transform())
    print(evolved.attack())
    print(evolved.revert())


def main() -> None:
    healing_factory = HealingCreatureFactory()
    transform_factory = TransformCreatureFactory()

    test_healing_factory(healing_factory)
    print()
    test_transform_factory(transform_factory)


if __name__ == "__main__":
    main()
