"""Constrained generation using only the public model SDK."""

import math

from llm_sdk import Small_LLM_Model

from .constraints import (
    GrammarState,
    allowed_choice_tokens,
    allowed_grammar_tokens,
    build_parameter_grammar,
    consume_grammar,
    forced_literal,
    initial_part_state,
    is_grammar_complete,
)
from .models import FunctionDefinition


def select_token(logits: list[float], allowed_ids: list[int]) -> int:
    """Mask forbidden tokens and select the best finite allowed score."""
    masked = [float("-inf")] * len(logits)
    for token_id in allowed_ids:
        if not 0 <= token_id < len(logits):
            raise ValueError("Vocabulary ID is outside the logits array.")
        if math.isfinite(logits[token_id]):
            masked[token_id] = logits[token_id]
    if not any(math.isfinite(score) for score in masked):
        raise ValueError("No allowed token has a usable score.")
    return max(range(len(masked)), key=lambda token_id: masked[token_id])


def generate_choice(
    model: Small_LLM_Model,
    prompt: str,
    vocabulary: dict[int, bytes],
    choices: list[bytes],
    max_tokens: int = 128,
) -> str:
    """Generate a JSON function name from the schema's allowed choices."""
    if not choices or any(not choice for choice in choices):
        raise ValueError("Choices must contain nonempty byte sequences.")
    token_ids = model.encode(prompt).tolist()[0]
    generated = b""
    for _ in range(max_tokens):
        logits = model.get_logits_from_input_ids(token_ids)
        allowed = allowed_choice_tokens(generated, vocabulary, choices)
        next_id = select_token(logits, allowed)
        token_ids.append(next_id)
        generated += vocabulary[next_id]
        remaining = [
            choice
            for choice in choices
            if choice.startswith(generated)
        ]

        if len(remaining) == 1:
            return remaining[0].decode("utf-8")
    raise ValueError(
        f"Function selection did not finish within {max_tokens} tokens."
    )


def generate_parameters(
    model: Small_LLM_Model,
    prompt: str,
    vocabulary: dict[int, bytes],
    definition: FunctionDefinition,
    max_tokens: int = 256,
) -> str:
    """Generate schema-constrained arguments, inserting fixed syntax."""
    parts = build_parameter_grammar(definition)
    state: GrammarState = (0, initial_part_state(parts[0]))
    token_ids = model.encode(prompt).tolist()[0]
    generated = b""
    used_tokens = 0

    while used_tokens < max_tokens:
        fixed = forced_literal(parts, state)
        fixed_ids: list[int] = []
        if fixed:
            try:
                fixed_text = fixed.decode("utf-8")
            except UnicodeDecodeError:
                pass
            else:
                # Leave the last token to the model at the value boundary.
                fixed_ids = model.encode(fixed_text).tolist()[0][:-1]

        if fixed_ids:
            inserted = b"".join(vocabulary[item] for item in fixed_ids)
            if not inserted or not fixed.startswith(inserted):
                raise ValueError("Fixed text does not match vocabulary.")
            if used_tokens + len(fixed_ids) > max_tokens:
                break
            candidate = generated + inserted
            try:
                candidate_text = candidate.decode("utf-8")
            except UnicodeDecodeError:
                fixed_ids = []
            if fixed_ids:
                next_state = consume_grammar(parts, state, inserted)
                if next_state is None:
                    raise ValueError("Fixed text violates the grammar.")
                token_ids = model.encode(prompt + candidate_text).tolist()[0]
                generated = candidate
                state = next_state
                used_tokens += len(fixed_ids)
                if is_grammar_complete(parts, state):
                    return generated.decode("utf-8")
                continue

        logits = model.get_logits_from_input_ids(token_ids)
        allowed = allowed_grammar_tokens(parts, state, vocabulary)
        next_id = select_token(logits, allowed)
        fragment = vocabulary[next_id]
        next_state = consume_grammar(parts, state, fragment)
        if next_state is None:
            raise ValueError("Selected token violates the parameter grammar.")
        token_ids.append(next_id)
        generated += fragment
        state = next_state
        used_tokens += 1
        if is_grammar_complete(parts, state):
            return generated.decode("utf-8")

    raise ValueError(
        f"Parameter generation did not finish within {max_tokens} tokens."
    )
