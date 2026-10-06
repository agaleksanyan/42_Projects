import argparse
import sys
from time import perf_counter

from pydantic import TypeAdapter

from .file_io import read_json, write_json
from .models import FunctionCallingRequest, FunctionDefinition
from .pipeline import run_requests


def main() -> int:
    """Read inputs, generate function calls, and save the complete batch."""
    parser = argparse.ArgumentParser(
        description="Convert natural-language requests into function calls."
    )
    parser.add_argument(
        "--input",
        "-i",
        default="data/input/function_calling_tests.json",
        help="Path to the input JSON file.",
    )
    parser.add_argument(
        "--functions_definition",
        "-f",
        default="data/input/functions_definition.json",
        help="Path to the function definitions JSON file.",
    )
    parser.add_argument(
        "--output",
        "-o",
        default="data/output/function_calling_results.json",
        help="Path to the output JSON file.",
    )
    args = parser.parse_args()

    started = perf_counter()

    try:
        definitions = TypeAdapter(
            list[FunctionDefinition]
        ).validate_python(
            read_json(args.functions_definition)
        )

        requests = TypeAdapter(
            list[FunctionCallingRequest]
        ).validate_python(
            read_json(args.input)
        )

        print(f"Loaded functions: {len(definitions)}")
        print(f"Loaded requests: {len(requests)}")

        results = run_requests(requests, definitions)
        write_json(args.output, results)

        elapsed = perf_counter() - started
        print(f"Saved {len(results)} calls to {args.output}")
        print(f"Elapsed: {elapsed:.2f} seconds")
        return 0

    except KeyboardInterrupt:
        print("Interrupted.", file=sys.stderr)
        return 130

    except Exception as error:
        print(f"Error: {error}", file=sys.stderr)
        return 1
