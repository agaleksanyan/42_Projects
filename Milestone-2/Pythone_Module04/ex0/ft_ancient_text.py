import sys


def main() -> None:
    if len(sys.argv) != 2:
        print("Usage: ft_ancient_text.py <file>")
        sys.exit(1)

    filename = sys.argv[1]

    print("=== Cyber Archives Recovery ===")
    print(f"Accessing file '{filename}'")

    try:
        file = open(filename, "r")
        content = file.read()

        print("---")
        print(content)
        print("---")

        file.close()
        print(f"File '{filename}' closed.")

    except ValueError as e:
        print(f"Error opening file '{filename}': {e}")


if __name__ == "__main__":
    main()
