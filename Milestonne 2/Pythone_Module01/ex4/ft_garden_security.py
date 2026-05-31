class Plant:
    def __init__(self, name: str, height: float, age: int) -> None:
        self.name = name
        self._height = height if height >= 0 else 0.0
        self._age = age if age >= 0 else 0

    def show(self) -> None:
        print(f"{self.name}: {self._height:.1f}cm, {self._age} days old")

    def set_height(self, height: float) -> None:
        if height < 0:
            print(f"{self.name}: Error, height can't be negative")
            print("Height update rejected")
            return
        self._height = height
        print(f"Height updated: {height}cm")

    def get_height(self) -> float:
        return self._height

    def set_age(self, age: int) -> None:
        if age < 0:
            print(f"{self.name}: Error, age can't be negative")
            print("Age update rejected")
            return
        self._age = age
        print(f"Age updated: {age} days")

    def get_age(self) -> int:
        return self._age


if __name__ == "__main__":
    print("=== Garden Security System ===")
    plant = Plant("Rose", 15.0, 10)
    print("Plant created:", end=" ")
    plant.show()
    plant.set_height(25)
    plant.set_age(30)
    plant.set_height(-5)
    plant.set_age(-10)
    print("Current state:", end=" ")
    plant.show()
