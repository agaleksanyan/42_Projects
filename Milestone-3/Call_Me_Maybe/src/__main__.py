import os


def launch() -> int:
    """Configure CPU threads before importing the application."""
    os.environ.setdefault("OMP_NUM_THREADS", "2")
    os.environ.setdefault("MKL_NUM_THREADS", "2")

    from .main import main

    return main()


if __name__ == "__main__":
    raise SystemExit(launch())
