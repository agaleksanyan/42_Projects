import argparse
from pathlib import Path

DEFAULT_FUNCTION_PATH = Path("data/input/functions_definition.json")
DEFAULT_INPUT_PATH = Path("data/input/function_calling_tests.json")
DEFAULT_OUTPUT_PATH = Path("data/output/function_calling_results.json")


def parse_arguments() -> argparse.Namespace:
    
    parser = argparse.ArgumentParser()
    

def main() -> int:
    
    arguments = parse_arguments()
    return 0