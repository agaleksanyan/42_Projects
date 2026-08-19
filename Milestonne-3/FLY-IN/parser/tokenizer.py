from __future__ import annotations

from dataclasses import dataclass, field
from enum import Enum, auto

from utils.exceptions import ParserError


class TokenType(Enum):
    """Supported token types."""

    NB_DRONES = auto()
    START_HUB = auto()
    END_HUB = auto()
    HUB = auto()
    CONNECTION = auto()


@dataclass(slots=True)
class Token:
    """Single token extracted from one input line."""

    type: TokenType
    line: int
    values: list[str]
    metadata: dict[str, str] = field(default_factory=dict)


class Tokenizer:
    """Convert map file text into a sequence of tokens."""

    _PREFIXES: dict[str, TokenType] = {
        "nb_drones": TokenType.NB_DRONES,
        "start_hub": TokenType.START_HUB,
        "end_hub": TokenType.END_HUB,
        "hub": TokenType.HUB,
        "connection": TokenType.CONNECTION,
    }

    def tokenize(self, text: str) -> list[Token]:
        """Tokenize the entire input file."""
        tokens: list[Token] = []

        for line_number, line in enumerate(text.splitlines(), start=1):
            line = self._strip_comment(line)

            if not line:
                continue

            tokens.append(self._tokenize_line(line, line_number))

        return tokens

    def _tokenize_line(self, line: str, line_number: int) -> Token:
        """Convert one line into a Token."""
        prefix, body = self._split_prefix(line, line_number)

        metadata = self._parse_metadata(body, line_number)

        body = self._remove_metadata(body)

        values = body.split()

        return Token(
            type=self._PREFIXES[prefix],
            line=line_number,
            values=values,
            metadata=metadata,
        )

    @staticmethod
    def _strip_comment(line: str) -> str:
        """Remove comments and surrounding whitespace."""
        return line.split("#", 1)[0].strip()

    @staticmethod
    def _split_prefix(line: str, line_number: int) -> tuple[str, str]:
        """Split 'hub: ...' into ('hub', '...')."""
        if ":" not in line:
            raise ParserError(
                f"Line {line_number}: Missing declaration separator ':'."
            )

        prefix, body = line.split(":", 1)
        prefix = prefix.strip()

        if prefix not in Tokenizer._PREFIXES:
            raise ParserError(
                f"Line {line_number}: Unknown declaration '{prefix}'."
            )

        return prefix, body.strip()

    @staticmethod
    def _remove_metadata(body: str) -> str:
        """Remove metadata block from a line."""
        start = body.find("[")
        if start == -1:
            return body.strip()
        return body[:start].strip()

    @staticmethod
    def _parse_metadata(body: str, line_number: int) -> dict[str, str]:
        """Parse metadata block."""
        start = body.find("[")
        end = body.find("]")

        if start == -1 or end == -1:
            if start != end:
                raise ParserError(
                    f"Line {line_number}: Unclosed metadata block."
                )
            return {}

        if (
            start != body.rfind("[")
            or end != body.rfind("]")
            or end < start
            or body[end + 1:].strip()
        ):
            raise ParserError(
                f"Line {line_number}: Invalid metadata block syntax."
            )

        metadata: dict[str, str] = {}
        content = body[start + 1:end]

        for item in content.split():
            if item.count("=") != 1:
                raise ParserError(
                    f"Line {line_number}: Invalid metadata item '{item}'."
                )
            key, value = item.split("=", 1)

            if not key or not value:
                raise ParserError(
                    f"Line {line_number}: Invalid metadata item '{item}'."
                )
            if key in metadata:
                raise ParserError(
                    f"Line {line_number}: Duplicate metadata key '{key}'."
                )

            metadata[key] = value

        return metadata
