import os
import site
import sys


def is_inside_venv() -> bool:
    return sys.prefix != sys.base_prefix


def show_outside_matrix() -> None:
    print("MATRIX STATUS: You're still plugged in", end="\n\n")
    print(f"Current Python: {sys.executable}")
    print("Virtual Environment: None detected", end="\n\n")
    print("WARNING: You're in the global environment!")
    print("The machines can see everything you install.", end="\n\n")
    print("To enter the construct, run:")
    print("python -m venv matrix_env")
    print("source matrix_env/bin/activate # On Unix")
    print(r"matrix_env\Scripts\activate # On Windows", end="\n\n")
    print("Then run this program again.")


def show_inside_construct() -> None:
    env_path = sys.prefix
    env_name = os.path.basename(env_path)
    packages = site.getsitepackages()

    print("MATRIX STATUS: Welcome to the construct", end="\n\n")
    print(f"Current Python: {sys.executable}")
    print(f"Virtual Environment: {env_name}")
    print(f"Environment Path: {env_path}", end="\n\n")
    print("SUCCESS: You're in an isolated environment!")
    print("Safe to install packages without affecting")
    print("the global system.", end="\n\n")
    print("Package installation path:")
    print(packages[0])


def main() -> None:
    if is_inside_venv():
        show_inside_construct()
    else:
        show_outside_matrix()


if __name__ == "__main__":
    main()
