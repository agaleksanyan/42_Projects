def secure_archive(
    filename: str, mode: str = "r", content: str = ""
) -> tuple[bool, str]:
    try:
        if mode == "r" or mode == "read":
            with open(filename, "r") as file:
                data = file.read()
            return True, data

        if mode == "w" or mode == "write":
            with open(filename, "w") as file:
                file.write(content)
            return True, "Content successfully written to file"

        return False, "Invalid mode"

    except Exception as e:
        return False, f"{e}"


def main() -> None:
    print("=== Cyber Archives Security ===\n")

    print("Using 'secure_archive' to read from a nonexistent file:")
    print(secure_archive("/not/existing/file"))
    print("")
    print("Using 'secure_archive' to read from an inaccessible file:")
    print(secure_archive("/etc/master.passwd"))
    print("")
    print("Using 'secure_archive' to read from a regular file:")
    success, data = secure_archive("ancient_fragment.txt")
    print((success, data))
    print("")
    print("Using 'secure_archive' to write previous content to a new file:")
    if success:
        print(secure_archive("new_file.txt", "w", data))
    else:
        print("Write skipped due to read error.")


if __name__ == "__main__":
    main()
