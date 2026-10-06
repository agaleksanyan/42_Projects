from typing import Literal

from pydantic import BaseModel, ConfigDict


class FunctionCallingRequest(BaseModel):
    """A natural-language request to convert into a function call."""

    model_config = ConfigDict(strict=True, extra="forbid")

    prompt: str


class TypeDefinition(BaseModel):
    """Describe a supported JSON value type."""

    model_config = ConfigDict(strict=True, extra="forbid")

    type: Literal["string", "number", "integer", "boolean", "null"]


class FunctionDefinition(BaseModel):
    """Describe an available function and its parameters."""

    model_config = ConfigDict(strict=True, extra="forbid")

    name: str
    description: str
    parameters: dict[str, TypeDefinition]
    returns: TypeDefinition
