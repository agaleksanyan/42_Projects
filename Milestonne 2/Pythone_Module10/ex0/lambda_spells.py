def artifact_sorter(artifacts: list[dict]) -> list[dict]:
    return sorted(
        artifacts,
        key=lambda artifact: artifact["power"],
        reverse=True
    )


def power_filter(mages: list[dict], min_power: int) -> list[dict]:
    return list(filter(lambda mage: mage["power"] >= min_power, mages))


def spell_transformer(spells: list[str]) -> list[str]:
    return list(map((lambda spell: "* " + spell + " *"), spells))


def mage_stats(mages: list[dict]) -> dict:

    maximum = max(mages, key=lambda mage: mage["power"])["power"]
    minimum = min(mages, key=lambda mage: mage["power"])["power"]
    power = map(lambda mage: mage["power"], mages)
    average = round(sum(power) / len(mages), 2)

    return {"max_power": maximum, "min_power": minimum, "avg_power": average}


if __name__ == "__main__":

    artifacts = [
        {"name": "Crystal Orb", "power": 85, "type": "arcane"},
        {"name": "Fire Staff", "power": 92, "type": "fire"},
    ]

    spells = ["fireball", "heal", "shield"]

    sorted_artifacts = artifact_sorter(artifacts)
    transformed_spells = spell_transformer(spells)

    print()
    print("Testing artifact sorter...")
    print(
        f"{sorted_artifacts[0]['name']} "
        f"({sorted_artifacts[0]['power']} power) comes before "
        f"{sorted_artifacts[1]['name']} "
        f"({sorted_artifacts[1]['power']} power)"
    )

    print("\nTesting spell transformer...")
    print(" ".join(transformed_spells))
