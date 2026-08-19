class PlantError(Exception):
    def __init__(self, message: str = "Invalid plant name") -> None:
        super().__init__(message)


def water_plant(plant_name: str) -> None:
    if plant_name != plant_name.capitalize():
        raise PlantError(f"Invalid plant name to water: '{plant_name}'")
    print(f"Watering {plant_name}: [OK]")


def test_watering_system() -> None:
    print("=== Garden Watering System ===")

    print("Testing valid plants...")
    try:
        print("Opening watering system")

        water_plant("Tomato")
        water_plant("Lettuce")
        water_plant("Carrots")

    except PlantError as e:
        print(f"Caught PlantError: {e}")

    finally:
        print("Closing watering system")

    print("Testing invalid plants...")
    try:
        print("Opening watering system")

        water_plant("Tomato")
        water_plant("lettuce")

    except PlantError as e:
        print(f"Caught PlantError: {e}")
        print(".. ending tests and returning to main")
        return

    finally:
        print("Closing watering system")


if __name__ == "__main__":
    test_watering_system()
    print("Cleanup always happens, even with errors!")
