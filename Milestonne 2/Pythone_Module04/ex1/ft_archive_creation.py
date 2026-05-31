import sys


def main() -> None:
    if len(sys.argv) != 2:
        print("Usage: ft_archive_creation.py <file>")
        sys.exit(1)

    filename = sys.argv[1]

    print("=== Cyber Archives Recovery & Preservation ===")
    print(f"Accessing file '{filename}'")

    try:
        file = open(filename, "r")
        content = file.read()

        print("---")
        print(content, end="")
        print("---")

        file.close()
        print(f"File '{filename}' closed.")

    except Exception as e:
        print(f"Error opening file '{filename}': {e}")
        return

    lines = content.split("\n")
    new_lines = []

    for line in lines:
        new_lines.append(line + "#")

    new_content = "\n".join(new_lines)

    print("Transform data:")
    print("---")
    print(new_content)
    print("---")

    new_filename = input("Enter new file name (or empty): ")

    if new_filename == "":
        print("Not saving data.")
    else:
        try:
            print(f"Saving data to '{new_filename}'")
            new_file = open(new_filename, "w")
            new_file.write(new_content)
            new_file.close()
            print(f"Data saved in file '{new_filename}'.")
        except Exception as e:
            print(f"Error opening file '{new_filename}': {e}")


if __name__ == "__main__":
    main()
