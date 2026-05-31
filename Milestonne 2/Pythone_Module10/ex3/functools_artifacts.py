from collections.abc import Callable
from typing import Any
import functools
import operator


def spell_reducer(spells: list[int], operation: str) -> int:

    if not spells:
        return 0

    operations: dict[str, Callable[[int, int], int]] = {
        "add": operator.add,
        "multiply": operator.mul,
        "max": max,
        "min": min,
    }

    if operation not in operations:
        raise ValueError("Unknown operation")

    return functools.reduce(operations[operation], spells)


def partial_enchanter(base_enchantment: Callable) -> dict[str, Callable]:

    fire_enchant = functools.partial(base_enchantment, 50, "fire")
    ice_enchant = functools.partial(base_enchantment, 50, "ice")
    electric_enchant = functools.partial(base_enchantment, 50, "electric")

    result: dict[str, Callable] = {
        "fire_enchant": fire_enchant,
        "ice_enchant": ice_enchant,
        "electric_enchant": electric_enchant,
    }

    return result


@functools.lru_cache(maxsize=None)
def memoized_fibonacci(n: int) -> int:

    if n <= 1:
        return n

    return memoized_fibonacci(n - 1) + memoized_fibonacci(n - 2)


def spell_dispatcher() -> Callable[[Any], str]:

    @functools.singledispatch
    def cast_spell(spell: Any) -> str:
        return "Unknown spell type"

    @cast_spell.register
    def _(spell: str) -> str:
        return f"Enchantment: {spell}"

    @cast_spell.register
    def _(spell: int) -> str:
        return f"Damage spell: {spell} damage"

    @cast_spell.register
    def _(spell: list) -> str:
        return f"Multi-cast: {len(spell)} spells"

    return cast_spell


def main() -> None:

    print("Testing spell reducer...")
    spells = [10, 20, 30, 40]

    print(f"Sum: {spell_reducer(spells, 'add')}")
    print(f"Product: {spell_reducer(spells, 'multiply')}")
    print(f"Max: {spell_reducer(spells, 'max')}")

    print()
    print("Testing partial enchanter...")

    def base_enchantment(power: int, element: str, target: str) -> str:
        return f"{element} enchantment " f"on {target} " f"with power {power}"

    enchants = partial_enchanter(base_enchantment)

    print(enchants["fire_enchant"]("Dragon"))

    print(enchants["ice_enchant"]("Knight"))

    print(enchants["electric_enchant"]("Goblin"))

    print()
    print("Testing memoized fibonacci...")
    print(f"Fib(0): {memoized_fibonacci(0)}")
    print(f"Fib(1): {memoized_fibonacci(1)}")
    print(f"Fib(10): {memoized_fibonacci(10)}")
    print(f"Fib(15): {memoized_fibonacci(15)}")

    print()
    print("Testing spell dispatcher...")
    dispatcher = spell_dispatcher()

    print(dispatcher(42))
    print(dispatcher("fireball"))
    print(dispatcher(["fire", "ice", "heal"]))
    print(dispatcher(3.14))


if __name__ == "__main__":
    main()
