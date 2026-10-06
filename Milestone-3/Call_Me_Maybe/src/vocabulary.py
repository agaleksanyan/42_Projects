from .file_io import read_json


def build_byte_alphabet() -> dict[str, int]:
    """Map Qwen byte-alphabet characters back to original byte values."""
    direct_bytes = (
        list(range(33, 127))
        + list(range(161, 173))
        + list(range(174, 256))
    )

    alphabet: dict[str, int] = {}

    for byte_value in direct_bytes:
        character = chr(byte_value)
        alphabet[character] = byte_value

    next_codepoint = 256

    for byte_value in range(256):
        if byte_value not in direct_bytes:
            character = chr(next_codepoint)
            alphabet[character] = byte_value
            next_codepoint += 1

    return alphabet


def token_to_bytes(stored_token: str, alphabet: dict[str, int]) -> bytes:
    """Convert a vocabulary token representation to its original bytes."""
    values: list[int] = []

    for character in stored_token:
        byte_value = alphabet[character]
        values.append(byte_value)

    return bytes(values)


def load_vocabulary(path: str) -> dict[int, bytes]:
    """Load vocabulary entries as token IDs mapped to byte sequences."""
    raw_vocabulary = read_json(path)

    if not isinstance(raw_vocabulary, dict) or not raw_vocabulary:
        raise ValueError("Vocabulary must be a nonempty JSON object.")

    alphabet = build_byte_alphabet()
    vocabulary: dict[int, bytes] = {}

    for stored_token, token_id in raw_vocabulary.items():
        if not isinstance(stored_token, str):
            raise ValueError("Vocabulary token must be a string.")

        if type(token_id) is not int or token_id < 0:
            raise ValueError("Vocabulary ID must be a nonnegative integer.")

        if stored_token.startswith("<|") and stored_token.endswith("|>"):
            continue

        if token_id in vocabulary:
            raise ValueError(f"Duplicate vocabulary ID: {token_id}")

        try:
            fragment = token_to_bytes(stored_token, alphabet)
        except KeyError as error:
            raise ValueError(
                f"Unsupported character in token {stored_token!r}"
            ) from error

        if not fragment:
            raise ValueError(f"Empty vocabulary token: {token_id}")

        vocabulary[token_id] = fragment

    if not vocabulary:
        raise ValueError("Vocabulary contains no ordinary tokens.")

    return vocabulary
