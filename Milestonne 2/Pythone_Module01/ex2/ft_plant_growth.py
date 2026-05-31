class Plant:
    def __init__(self, name: str, height: float, age: int) -> None:
        self.name: str = name
        self.height: float = height
        self.age: int = age

    def grow(self, cm: float = 0.8) -> None:
        self.height += cm

    def age_plant(self, days: int = 1) -> None:
        self.age += days

    def show(self) -> None:
        print(
            f"{self.name}: {round(self.height, 1)}cm, "
            f"{self.age} days old"
        )


if __name__ == "__main__":
    rose = Plant("Rose", 25.0, 30)
    print("=== Garden Plant Growth ===")
    rose.show()

    for day in range(1, 8):
        print(f"=== Day {day} ===")
        rose.grow()
        rose.age_plant()
        rose.show()

    growth = round(rose.height - 25.0, 1)
    print(f"Growth this week: {growth}cm")
