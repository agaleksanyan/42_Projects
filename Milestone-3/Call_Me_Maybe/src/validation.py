import math

from .models import FunctionDefinition


def validate_parameters(
    parameters: object,
    definition: FunctionDefinition,
) -> None:
    """Validate parameter keys and scalar values against a function schema."""
    if not isinstance(parameters, dict):
        raise ValueError("Parameters must be a JSON object.")

    expected_keys = set(definition.parameters)
    actual_keys = set(parameters)

    if actual_keys != expected_keys:
        raise ValueError(
            f"Incorrect parameter keys for {definition.name!r}. "
            f"Expected {expected_keys}, got {actual_keys}."
        )

    for name, schema in definition.parameters.items():
        value = parameters[name]
        kind = schema.type

        valid = (
            (kind == "string" and type(value) is str)
            or (kind == "number" and type(value) in (int, float))
            or (kind == "integer" and type(value) is int)
            or (kind == "boolean" and type(value) is bool)
            or (kind == "null" and value is None)
        )

        if not valid:
            raise ValueError(
                f"Parameter {name!r} must have JSON type {kind!r}."
            )

        if isinstance(value, float) and not math.isfinite(value):
            raise ValueError(f"Parameter {name!r} must be finite.")
