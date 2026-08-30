import argparse
from pathlib import Path

DEFAULT_FUNCTION_PATH = Path("data/input/functions_definition.json")
DEFAULT_INPUT_PATH = Path("data/input/function_calling_tests.json")
DEFAULT_OUTPUT_PATH = Path("data/output/function_calling_results.json")


def parse_arguments() -> argparse.Namespace:

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-f",
        "--functions_definition",
        type=Path,
        default=DEFAULT_FUNCTION_PATH,
        help="Path to the JSON file containing function definitions.",
    )
    parser.add_argument(
        "-i",
        "--input",
        type=Path,
        default=DEFAULT_INPUT_PATH,
        help="Path to the JSON file containing function calling tests.",
    )
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=DEFAULT_OUTPUT_PATH,
        help="Path to the JSON file where function calling results will be saved.",
    )
    return parser.parse_args()


def main() -> int:

    arguments = parse_arguments()
    return 0
