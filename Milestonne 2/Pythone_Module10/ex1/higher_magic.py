from collections.abc import Callable


def spell_combiner(spell1: Callable, spell2: Callable) -> Callable:

    def combined_spell(target: str, power: int) -> tuple[str, str]:
        return (
            spell1(target, power),
            spell2(target, power),
        )

    return combined_spell


def power_amplifier(base_spell: Callable, multiplier: int) -> Callable:

    def power_reinforced(target: str, power: int) -> str:
        return base_spell(target, power * multiplier)

    return power_reinforced


def conditional_caster(condition: Callable, spell: Callable) -> Callable:

    def safe_spell(target: str, power: int) -> str:
        if condition(target, power):
            return spell(target, power)
        else:
            return "Spell fizzled"

    return safe_spell


def spell_sequence(spells: list[Callable]) -> Callable:

    def combo_spell(target: str, power: int) -> list[str]:
        return list(map(lambda spell: spell(target, power), spells))

    return combo_spell


if __name__ == "__main__":

    def fireball(target: str, power: int) -> str:
        return f"Fireball hits {target} with {power} power"

    def heal(target: str, power: int) -> str:
        return f"Heals {target} with {power} power"

    def has_enough_power(target: str, power: int) -> bool:
        return power >= 10

    print()
    print("Testing spell combiner...")
    combined = spell_combiner(fireball, heal)
    print(f"Combined spell result: {combined('Dragon', 10)}")

    print()
    print("Testing power amplifier...")
    amplified = power_amplifier(fireball, 3)
    print(f"Original: {fireball('Dragon', 10)}")
    print(f"Amplified: {amplified('Dragon', 10)}")

    print()
    print("Testing conditional caster...")
    safe_fireball = conditional_caster(has_enough_power, fireball)
    print(safe_fireball("Dragon", 15))
    print(safe_fireball("Dragon", 5))

    print()
    print("Testing spell sequence...")
    sequence = spell_sequence([fireball, heal])
    print(sequence("Dragon", 20))
