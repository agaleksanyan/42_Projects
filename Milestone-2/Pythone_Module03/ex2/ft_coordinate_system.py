import math


def get_player_pos() -> tuple[float, float, float]:
    while True:
        try:
            user_input = input("Enter new coordinates as floats "
                               "in format 'x,y,z': ")
            parts = user_input.split(",")

            try:
                x_str, y_str, z_str = parts
            except ValueError:
                print("Invalid syntax")
                continue

            x = float(x_str.strip())
            y = float(y_str.strip())
            z = float(z_str.strip())

            return (x, y, z)

        except ValueError as e:
            for part in parts:
                try:
                    float(part.strip())
                except ValueError:
                    print(f"Error on parameter '{part.strip()}': " f"{e}")
                    break

        except EOFError:
            return (0.0, 0.0, 0.0)


def distance(
    p1: tuple[float, float, float],
    p2: tuple[float, float, float],
) -> float:
    return math.sqrt(
        (p2[0] - p1[0]) ** 2
        + (p2[1] - p1[1]) ** 2
        + (p2[2] - p1[2]) ** 2
    )


def main() -> None:
    print("=== Game Coordinate System ===")

    print("Get a first set of coordinates")
    pos1 = get_player_pos()

    print(f"Got a first tuple: {pos1}")
    print(f"It includes: X={pos1[0]}, " f"Y={pos1[1]}, Z={pos1[2]}")

    center = (0.0, 0.0, 0.0)
    dist_center = distance(pos1, center)
    print("Distance to center: " f"{dist_center:.4f}")

    print("Get a second set of coordinates")
    pos2 = get_player_pos()

    dist_between = distance(pos1, pos2)
    print("Distance between the 2 sets of coordinates: " f"{dist_between:.4f}")


if __name__ == "__main__":
    main()
