def ft_count_harvest_recursive() -> None:
    n = int(input("Days until harvest: "))

    def helper(day: int) -> None:
        if day > n:
            print("Harvest time!")
            return
        print(f"Day {day}")
        helper(day + 1)

    helper(1)
