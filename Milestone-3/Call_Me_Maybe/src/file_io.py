import json
import os
import tempfile
from pathlib import Path
from typing import Any


def read_json(path: str) -> Any:
    """Read and decode a UTF-8 JSON file."""
    with Path(path).open(encoding="utf-8") as file:
        return json.load(file)


def write_json(path: str, data: Any) -> None:
    """Write JSON through a temporary file, then replace the destination."""
    text = json.dumps(
        data,
        ensure_ascii=False,
        allow_nan=False, indent=2
    ) + "\n"

    destination = Path(path)
    destination.parent.mkdir(parents=True, exist_ok=True)
    temporary_path: Path | None = None

    try:
        with tempfile.NamedTemporaryFile(
            mode="w", encoding="utf-8", dir=destination.parent, delete=False
        ) as file:
            temporary_path = Path(file.name)
            file.write(text)
        os.replace(temporary_path, destination)

    finally:
        if temporary_path is not None:
            temporary_path.unlink(missing_ok=True)
