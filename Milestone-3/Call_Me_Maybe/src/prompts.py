"""Chat prompts for function selection and argument extraction."""

import json

from .models import FunctionDefinition


def build_selection_prompt(
    request: str,
    definitions: list[FunctionDefinition],
) -> str:
    """Build a prompt for selecting one available function name."""
    descriptions = json.dumps(
        [
            {
                "name": item.name,
                "description": item.description,
            }
            for item in definitions
        ],
        ensure_ascii=False,
        separators=(",", ":"),
    )

    return (
        "<|im_start|>system\n"
        "Choose the function that matches the user request. "
        "Return only its name as a JSON string.\n"
        f"Available functions:\n{descriptions}<|im_end|>\n"
        f"<|im_start|>user\n{request}<|im_end|>\n"
        "<|im_start|>assistant\n"
        "<think>\n\n</think>\n\n"
    )


def build_argument_prompt(
    request: str,
    definition: FunctionDefinition,
) -> str:
    """Build a compact prompt for extracting function arguments."""
    parameter_types = {
        key: schema.type
        for key, schema in definition.parameters.items()
    }
    parameter_types_json = json.dumps(
        parameter_types,
        ensure_ascii=False,
        separators=(",", ":"),
    )

    return (
        "<|im_start|>system\n"
        "Extract function INPUT arguments, not its result. "
        "Do not execute the function. "
        "Copy source strings character for character. "
        "Return only the JSON parameter object.\n"
        f"Function: {definition.name}\n"
        f"Purpose: {definition.description}\n"
        f"Parameter types: {parameter_types_json}"
        "<|im_end|>\n"
        f"<|im_start|>user\n{request}<|im_end|>\n"
        "<|im_start|>assistant\n"
        "<think>\n\n</think>\n\n"
    )
