from collections.abc import Callable
import time
import functools


def spell_timer(func: Callable) -> Callable:

    @functools.wraps(func)
    def wrap(*args, **kwargs) -> str:
        print(f"Casting {func.__name__}...")
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        durationn = end - start
        print(f"Spell completed in {durationn:.3f} seconds")
        return result

    return wrap


def power_validator(min_power: int) -> Callable:

    def decorator(func: Callable) -> Callable:

        @functools.wraps(func)
        def wrap(*args, **kwargs) -> str:

            power = args[-1]

            if power < min_power:
                return "Insufficient power for this spell"

            return func(*args, **kwargs)

        return wrap

    return decorator


def retry_spell(max_attempts: int) -> Callable:

    def decorator(func: Callable) -> Callable:

        @functools.wraps(func)
        def wrap(*args, **kwargs) -> str:
            for attempt in range(1, max_attempts + 1):
                try:
                    return func(*args, **kwargs)
                except Exception:
                    if attempt < max_attempts:
                        print(
                            "Spell failed, retrying... (attempt "
                            f"{attempt}/{max_attempts})"
                        )
                    else:
                        return (
                            "Spell casting failed after "
                            f"{max_attempts} attempts"
                        )
            return f"Spell casting failed after {max_attempts} attempts"

        return wrap

    return decorator


class MageGuild:

    @staticmethod
    def validate_mage_name(name: str) -> bool:
        return len(name) >= 3 and name.replace(" ", "").isalpha()

    @power_validator(10)
    def cast_spell(self, spell_name: str, power: int) -> str:
        return f"Successfully cast {spell_name} with {power} power"


def main() -> None:

    print("Testing spell timer...")

    @spell_timer
    def fireball() -> str:
        time.sleep(0.1)
        return "Fireball cast!"

    result = fireball()
    print(f"Result: {result}")

    print()
    print("Testing power validator...")

    @power_validator(10)
    def simple_spell(power: int) -> str:
        return f"Spell cast with {power} power"

    print(simple_spell(15))
    print(simple_spell(5))

    print()
    print("Testing retrying spell...")

    @retry_spell(3)
    def broken_spell() -> str:
        raise RuntimeError("Failed spell")

    print(broken_spell())

    print("Waaaaaaagh spelled !")

    print()
    print("Testing MageGuild...")
    guild = MageGuild()

    print(MageGuild.validate_mage_name("Gandalf"))
    print(MageGuild.validate_mage_name("Ab"))

    print(guild.cast_spell("Lightning", 15))
    print(guild.cast_spell("Lightning", 5))


if __name__ == "__main__":
    main()
