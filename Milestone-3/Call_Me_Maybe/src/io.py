import json
from pathlib import Path

from pydantic import TypeAdapter

from .models import FunctionCallingTest, FunctionDefinition

_FUNCTION_DEFINITIONS_ADAPTER = TypeAdapter(list[FunctionDefinition])
_FUNCTION_CALLING_TESTS_ADAPTER = TypeAdapter(list[FunctionCallingTest])


def load_function_definitions(
    path: Path,
) -> list[FunctionDefinition]:

    text = path.read_text(encoding="utf-8")
    raw_data = json.loads(text)

    return _FUNCTION_DEFINITIONS_ADAPTER.validate_python(raw_data)


def load_function_calling_tests(
    path: Path,
) -> list[FunctionCallingTest]:

    text = path.read_text(encoding="utf-8")
    raw_data = json.loads(text)

    return _FUNCTION_CALLING_TESTS_ADAPTER.validate_python(raw_data)
