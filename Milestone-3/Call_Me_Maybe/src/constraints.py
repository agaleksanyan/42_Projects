"""Byte-level grammar for flat JSON parameter objects."""

import json
from typing import TypeAlias

from .models import FunctionDefinition

GrammarPart: TypeAlias = tuple[str, bytes]
PartState: TypeAlias = int | str
GrammarState: TypeAlias = tuple[int, PartState]


def string_step(state: str, byte: int) -> str | None:
    """Accept ASCII JSON text, simple escapes, and four-digit escapes."""
    if state == "start":
        return "body" if byte == 34 else None
    if state == "body":
        if byte == 34:
            return "done"
        if byte == 92:
            return "escape"
        return "body" if 32 <= byte <= 127 else None
    if state == "escape":
        if byte in b'"\\/bfnrt':
            return "body"
        return "hex4" if byte == 117 else None
    if state in ("hex4", "hex3", "hex2", "hex1"):
        if byte not in b"0123456789abcdefABCDEF":
            return None
        remaining = int(state[-1]) - 1
        return f"hex{remaining}" if remaining else "body"
    return None


def allowed_choice_tokens(
    prefix: bytes,
    vocabulary: dict[int, bytes],
    choices: list[bytes],
) -> list[int]:
    """Find tokens that preserve a prefix of an allowed choice."""
    allowed_ids: list[int] = []

    for token_id, fragment in vocabulary.items():
        if not fragment:
            continue

        candidate = prefix + fragment

        for choice in choices:
            if choice.startswith(candidate):
                allowed_ids.append(token_id)
                break

    return allowed_ids


def literal_step(expected: bytes, position: int, byte: int) -> int | None:
    """Check one byte against a fixed sequence and advance its position."""
    if position < 0 or position >= len(expected):
        return None

    if byte != expected[position]:
        return None

    return position + 1


def integer_step(state: str, byte: int) -> str | None:
    """Advance one byte through the JSON integer grammar."""
    if state == "start":
        if byte == 45:
            return "sign"
        if byte == 48:
            return "zero"
        if 49 <= byte <= 57:
            return "digits"
        return None

    if state == "sign":
        if byte == 48:
            return "zero"
        if 49 <= byte <= 57:
            return "digits"
        return None

    if state == "digits":
        if 48 <= byte <= 57:
            return "digits"
        return None
    return None


def is_complete_integer(state: str) -> bool:
    """Check whether the integer can end in its current state."""
    return state in ("zero", "digits")


def number_step(state: str, byte: int) -> str | None:
    """Advance one byte through the JSON number grammar."""
    if state in ("start", "sign"):
        return integer_step(state, byte)

    if state in ("zero", "digits"):
        if state == "digits" and 48 <= byte <= 57:
            return "digits"

        if byte == 46:
            return "dot"

        if byte in (69, 101):
            return "exponent"

        return None

    if state in ("dot", "fraction"):
        if 48 <= byte <= 57:
            return "fraction"

        if state == "fraction" and byte in (69, 101):
            return "exponent"

        return None

    if state == "exponent":
        if byte in (43, 45):
            return "exponent_sign"

        if 48 <= byte <= 57:
            return "exponent_digits"

        return None

    if state in ("exponent_sign", "exponent_digits"):
        if 48 <= byte <= 57:
            return "exponent_digits"

        return None
    return None


def is_complete_number(state: str) -> bool:
    """Check whether the JSON number can end in its current state."""
    return state in (
        "zero",
        "digits",
        "fraction",
        "exponent_digits",
    )


def build_parameter_grammar(
    definition: FunctionDefinition,
) -> list[GrammarPart]:
    """Build ordered grammar parts for a function's parameters."""
    parts: list[GrammarPart] = [("literal", b"{")]

    for index, (name, schema) in enumerate(definition.parameters.items()):
        if schema.type not in (
            "string", "number", "integer", "boolean", "null"
        ):
            raise ValueError(f"Unsupported parameter type: {schema.type}")

        separator = "" if index == 0 else ", "
        key_json = json.dumps(name, ensure_ascii=False)
        fixed_text = separator + key_json + ": "

        parts.append(("literal", fixed_text.encode("utf-8")))
        parts.append((schema.type, b""))

    parts.append(("literal", b"}"))

    return parts


def initial_part_state(part: GrammarPart) -> PartState:
    """Return the starting state for one grammar part."""
    kind, _ = part

    if kind == "literal":
        return 0

    if kind in ("string", "number", "integer"):
        return "start"

    if kind in ("boolean", "null"):
        return ""

    raise ValueError(f"Unsupported grammar part: {kind}")


def is_part_complete(part: GrammarPart, state: PartState) -> bool:
    """Check whether a grammar part may end in its current state."""
    kind, data = part

    if kind == "literal":
        return isinstance(state, int) and state == len(data)
    if kind == "string":
        return state == "done"
    if kind == "number":
        return isinstance(state, str) and is_complete_number(state)
    if kind == "integer":
        return isinstance(state, str) and is_complete_integer(state)
    if kind == "boolean":
        return state in ("true", "false")
    if kind == "null":
        return state == "null"

    raise ValueError(f"Unsupported grammar part: {kind}")


def part_step(
    part: GrammarPart,
    state: PartState,
    byte: int,
) -> PartState | None:
    """Advance one byte through a grammar part."""
    kind, data = part

    if kind == "literal":
        if not isinstance(state, int):
            raise ValueError("Literal part state must be an integer.")
        return literal_step(data, state, byte)

    if kind == "string":
        if not isinstance(state, str):
            raise ValueError("String state must be a string.")
        return string_step(state, byte)

    if kind == "number":
        if not isinstance(state, str):
            raise ValueError("Number state must be a string.")
        return number_step(state, byte)
    if kind == "integer":
        if not isinstance(state, str):
            raise ValueError("Integer state must be a string.")

        return integer_step(state, byte)

    if kind in ("boolean", "null"):
        if not isinstance(state, str):
            raise ValueError("Keyword state must be a string.")

        choices = ("true", "false") if kind == "boolean" else ("null",)
        return keyword_step(state, byte, choices)

    raise ValueError(f"Unsupported grammar part: {kind}")


def grammar_step(
    parts: list[GrammarPart],
    state: GrammarState,
    byte: int,
) -> GrammarState | None:
    """Consume one byte, moving between complete grammar parts."""
    part_index, part_state = state

    while part_index < len(parts):
        part = parts[part_index]
        next_state = part_step(part, part_state, byte)

        if next_state is not None:
            return (part_index, next_state)

        if not is_part_complete(part, part_state):
            return None

        part_index += 1

        if part_index < len(parts):
            part_state = initial_part_state(parts[part_index])
    return None


def is_grammar_complete(parts: list[GrammarPart], state: GrammarState) -> bool:
    """Check whether the final grammar part has completed."""
    if not parts:
        return False

    part_index, part_state = state

    return (
        part_index == len(parts) - 1
        and is_part_complete(parts[part_index], part_state)
    )


def consume_grammar(
    parts: list[GrammarPart],
    state: GrammarState,
    fragment: bytes,
) -> GrammarState | None:
    """Check every byte of a fragment against the parameter grammar."""
    current_state = state

    for byte in fragment:
        next_state = grammar_step(parts, current_state, byte)
        if next_state is None:
            return None
        current_state = next_state

    return current_state


def allowed_grammar_tokens(
    parts: list[GrammarPart],
    state: GrammarState,
    vocabulary: dict[int, bytes],
) -> list[int]:
    """Find tokens that preserve the parameter grammar."""
    allowed_ids: list[int] = []

    for token_id, fragment in vocabulary.items():
        if not fragment:
            continue

        next_state = consume_grammar(parts, state, fragment)

        if next_state is not None:
            allowed_ids.append(token_id)

    return allowed_ids


def keyword_step(
    state: str,
    byte: int,
    choices: tuple[str, ...],
) -> str | None:
    """Advance one byte through a fixed set of ASCII keywords."""
    candidate = state + chr(byte)

    for choice in choices:
        if choice.startswith(candidate):
            return candidate
    return None


def forced_literal(parts: list[GrammarPart], state: GrammarState) -> bytes:
    """Return fixed bytes that can follow without choosing a scalar value."""
    part_index, part_state = state
    fragments: list[bytes] = []

    while part_index < len(parts):
        part = parts[part_index]
        kind, data = part

        if kind == "literal":
            if not isinstance(part_state, int):
                raise ValueError("Literal state must be an integer.")

            fragments.append(data[part_state:])

        else:
            if kind in ("number", "integer"):
                break

            if not is_part_complete(part, part_state):
                break

        part_index += 1

        if part_index < len(parts):
            part_state = initial_part_state(parts[part_index])

    return b"".join(fragments)
