from __future__ import annotations

from parser.tokenizer import Token, TokenType
from utils.exceptions import ValidationError


class Validator:
    """Performs semantic validation on a sequence of tokens."""

    _ZONE_TOKENS = {
        TokenType.START_HUB,
        TokenType.END_HUB,
        TokenType.HUB,
    }
    _ZONE_METADATA = {"zone", "color", "max_drones"}
    _CONNECTION_METADATA = {"max_link_capacity"}
    _ZONE_TYPES = {"normal", "blocked", "restricted", "priority"}

    def validate(self, tokens: list[Token]) -> None:
        """Validate token sequence and raise on errors."""
        self._validate_first_declaration(tokens)
        self._validate_nb_drones(tokens)
        self._validate_hub_counts(tokens)
        self._validate_graph_declarations(tokens)

    def _validate_first_declaration(self, tokens: list[Token]) -> None:
        """Require the first declaration to define the drone count."""
        if not tokens:
            raise ValidationError("Map file is empty.")
        if tokens[0].type is not TokenType.NB_DRONES:
            raise ValidationError(
                f"Line {tokens[0].line}: First declaration must be nb_drones."
            )

    def _validate_nb_drones(self, tokens: list[Token]) -> None:
        """Ensure exactly one nb_drones definition exists."""
        nb_tokens = [t for t in tokens if t.type is TokenType.NB_DRONES]
        if len(nb_tokens) != 1:
            raise ValidationError(
                "Expected exactly one"
                f" nb_drones definition, found {len(nb_tokens)}."
            )
        if len(nb_tokens[0].values) != 1:
            raise ValidationError("nb_drones must have exactly one value.")
        try:
            val = int(nb_tokens[0].values[0])
        except ValueError:
            raise ValidationError(
                "nb_drones must be a positive integer."
                ) from None
        if val <= 0:
            raise ValidationError("nb_drones must be positive.")

    def _validate_hub_counts(self, tokens: list[Token]) -> None:
        """Require exactly one start hub and one end hub."""
        for token_type, description in (
            (TokenType.START_HUB, "start_hub"),
            (TokenType.END_HUB, "end_hub"),
        ):
            count = sum(token.type is token_type for token in tokens)
            if count != 1:
                raise ValidationError(
                    f"Expected exactly one {description}, found {count}."
                )

    def _validate_graph_declarations(self, tokens: list[Token]) -> None:
        """Validate zone syntax, metadata, and connection ordering."""
        seen: set[str] = set()
        connections: set[frozenset[str]] = set()

        for token in tokens:
            if token.type in self._ZONE_TOKENS:
                self._validate_zone(token, seen)
            elif token.type is TokenType.CONNECTION:
                self._validate_connection(token, seen, connections)

    def _validate_zone(self, token: Token, seen: set[str]) -> None:
        """Validate one zone declaration and register its name."""
        if len(token.values) != 3:
            raise ValidationError(
                f"Line {token.line}: Zone requires name and two coordinates."
            )

        name = token.values[0]
        if "-" in name:
            raise ValidationError(
                f"Line {token.line}: Zone name '{name}' cannot contain '-'."
            )
        if name in seen:
            raise ValidationError(
                f"Line {token.line}: Duplicate zone name '{name}'."
            )

        for coordinate in token.values[1:]:
            try:
                int(coordinate)
            except ValueError:
                raise ValidationError(
                    f"Line {token.line}: Zone coordinates must be integers."
                ) from None

        unknown = set(token.metadata) - self._ZONE_METADATA
        if unknown:
            key = sorted(unknown)[0]
            raise ValidationError(
                f"Line {token.line}: Unknown zone metadata '{key}'."
            )
        if "zone" in token.metadata:
            zone_type = token.metadata["zone"]
            if zone_type not in self._ZONE_TYPES:
                raise ValidationError(
                    f"Line {token.line}: Unknown zone type '{zone_type}'."
                )
        if token.type is TokenType.HUB:
            self._validate_positive_metadata(token, "max_drones")
        seen.add(name)

    def _validate_connection(
        self,
        token: Token,
        zones: set[str],
        connections: set[frozenset[str]],
    ) -> None:
        """Validate one connection and ensure both zones already exist."""
        if len(token.values) != 1 or token.values[0].count("-") != 1:
            raise ValidationError(
                f"Line {token.line}: Invalid connection format."
            )

        first, second = token.values[0].split("-", 1)
        if not first or not second:
            raise ValidationError(
                f"Line {token.line}: Invalid connection format."
            )
        if first not in zones or second not in zones:
            raise ValidationError(
                f"Line {token.line}: "
                "Connections require previously defined zones."
            )

        unknown = set(token.metadata) - self._CONNECTION_METADATA
        if unknown:
            key = sorted(unknown)[0]
            raise ValidationError(
                f"Line {token.line}: Unknown connection metadata '{key}'."
            )
        self._validate_positive_metadata(token, "max_link_capacity")

        connection = frozenset({first, second})
        if connection in connections:
            raise ValidationError(
                f"Line {token.line}: Duplicate connection '{first}-{second}'."
            )
        connections.add(connection)

    @staticmethod
    def _validate_positive_metadata(token: Token, key: str) -> None:
        """Ensure optional capacity metadata is a positive integer."""
        if key not in token.metadata:
            return
        try:
            value = int(token.metadata[key])
        except ValueError:
            raise ValidationError(
                f"Line {token.line}: {key} must be a positive integer."
            ) from None
        if value <= 0:
            raise ValidationError(
                f"Line {token.line}: {key} must be a positive integer."
            )
