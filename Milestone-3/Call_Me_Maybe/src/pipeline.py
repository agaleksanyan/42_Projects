import json

from llm_sdk import Small_LLM_Model
from .llm import generate_choice, generate_parameters
from .models import FunctionCallingRequest, FunctionDefinition
from .prompts import build_argument_prompt, build_selection_prompt
from .validation import validate_parameters
from .vocabulary import load_vocabulary


def run_requests(
    requests: list[FunctionCallingRequest],
    definitions: list[FunctionDefinition],
) -> list[dict[str, object]]:
    """Generate and validate function calls for a complete request batch."""
    functions_by_name: dict[str, FunctionDefinition] = {}

    for definition in definitions:
        if definition.name in functions_by_name:
            raise ValueError(
                f"Duplicate function name: {definition.name!r}"
            )

        functions_by_name[definition.name] = definition

    if not requests:
        return []

    if not definitions:
        raise ValueError("No functions are available for the requests.")

    choices = [
        json.dumps(item.name, ensure_ascii=False).encode("utf-8")
        for item in definitions
    ]

    model = Small_LLM_Model()
    vocabulary = load_vocabulary(model.get_path_to_vocab_file())

    results: list[dict[str, object]] = []

    for index, request in enumerate(requests, start=1):
        try:
            selection_prompt = build_selection_prompt(
                request.prompt, definitions
            )

            name_json = generate_choice(
                model, selection_prompt, vocabulary, choices
            )
            selected_name = json.loads(name_json)
            print(
                f"Request {index}/{len(requests)}: {selected_name}"
            )

            if not isinstance(selected_name, str):
                raise ValueError("Selected function name must be a string.")

            if selected_name not in functions_by_name:
                raise ValueError(f"Unknown function: {selected_name!r}")

            definition = functions_by_name[selected_name]

            argument_prompt = build_argument_prompt(
                request.prompt, definition
            )
            parameters_json = generate_parameters(
                model=model,
                prompt=argument_prompt,
                vocabulary=vocabulary,
                definition=definition,
            )
            parameters = json.loads(parameters_json)
            validate_parameters(parameters, definition)

            results.append({
                "prompt": request.prompt,
                "name": selected_name,
                "parameters": parameters,
            })

        except Exception as error:
            raise ValueError(
                f"Request {index} failed: {error}"
            ) from error

    return results
