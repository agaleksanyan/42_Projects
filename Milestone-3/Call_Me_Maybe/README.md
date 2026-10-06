*This project has been created as part of the 42 curriculum by agaleksa.*

# Call Me Maybe

## Description

Convert natural-language requests into structured function calls with
Qwen/Qwen3-0.6B and the provided `llm_sdk`. The program chooses a function
and extracts its input arguments. It does not execute the function.

The output is a JSON array. Each entry has exactly `prompt`, `name`, and
`parameters`. Function names, parameter names, and parameter types come
from the supplied definitions, rather than hardcoded examples.

## Instructions

Use Python 3.10 or later, uv, and a terminal. The Makefile uses Unix tools
and can be run on Linux or in WSL. Keep the supplied `llm_sdk` directory
beside `src`.

```sh
uv sync
uv run python -m src
```

The first model run needs internet access to download the model and its
tokenizer from Hugging Face. Later runs reuse the downloaded files.
Downloading the model is separate from processing requests.

Default paths:

- Functions: `data/input/functions_definition.json`
- Requests: `data/input/function_calling_tests.json`
- Results: `data/output/function_calling_results.json`

Custom paths:

```sh
uv run python -m src \
  --functions_definition data/input/functions_definition.json \
  --input data/input/function_calling_tests.json \
  --output data/output/results.json
```

For example, `What is the sum of 2 and 3?` should produce:

```json
{
  "prompt": "What is the sum of 2 and 3?",
  "name": "fn_add_numbers",
  "parameters": {"a": 2, "b": 3}
}
```

### Makefile

| Command | Purpose |
| --- | --- |
| `make install` | Install runtime and development dependencies |
| `make run` | Run the program with default paths |
| `make debug` | Run under Python's `pdb` debugger |
| `make lint` | Run flake8 and the required mypy checks |
| `make lint-strict` | Run flake8 and strict mypy |
| `make clean` | Remove bytecode, checking caches, and `data/output` |
| `make fclean` | Also remove `.venv`; restore it with `make install` |

`make clean` deletes generated results. Copy any results you want to keep
before running it. Neither clean command removes the Hugging Face model
cache, so reinstalling the environment does not require downloading the
model again.

Arguments can be passed to run or debug:

```sh
make run ARGS="--input questions.json --output results.json"
```

The checking configuration excludes the supplied SDK, virtual environment,
and static SDK interface declarations. All application files in `src` are
checked. `typings/llm_sdk/__init__.pyi` describes the SDK interface to mypy;
it does not replace the SDK at runtime. Keep this folder in the submission.

## Algorithm explanation

1. Read both JSON files and validate them with strict Pydantic models.
2. Load the model once and read its vocabulary through the public SDK.
3. Convert vocabulary spellings to byte sequences. For example, the
   vocabulary symbol `Ġ` represents a space byte, not that printed symbol.
4. Ask the model to choose a function name. Only token continuations that
   remain prefixes of an available JSON-encoded name are allowed. After
   each generated token, filter the candidate names. When exactly one
   remains, return that full name without generating its fixed suffix.
5. Build a parameter grammar from the chosen definition. Fixed parts
   contain punctuation and keys; value parts describe scalar types.
6. For each candidate token, feed all its bytes into a copy of the grammar
   state. A token may cross multiple parts. Reject it if any byte fails.
7. Set forbidden token scores to negative infinity and select the highest
   finite allowed logit. Append that token and advance the grammar state.
8. Stop only when the whole parameter object is complete. Parse the JSON
   and independently validate the exact keys, types, and finite numbers.
9. Write all results to a temporary file and replace the output only after
   the complete batch succeeds.

The grammar supports flat objects containing strings, numbers, integers,
booleans, and null, including functions with no arguments. Integer syntax
does not allow decimal points or exponents. Number syntax does.

Strings use ASCII bytes with JSON escapes for quotes, backslashes, control
characters, and `\uXXXX`. Raw multibyte UTF-8 string values are not generated;
non-ASCII values must be represented by JSON escapes. This keeps the
grammar small without a separate UTF-8 state machine. Correct extraction
of arbitrary non-ASCII text is not established by the English sample tests.
JSON files and vocabulary files are still read and written as UTF-8.
Nested objects and arrays are outside the supported parameter schema.

For example, the prefix `"fn_g` is still ambiguous between `fn_greet`
and `fn_get_square_root`. The prefix `"fn_gr` identifies `fn_greet`
uniquely. Completing the remaining name at that point does not introduce
a heuristic choice: the model has already selected the distinguishing
prefix, and the candidate list comes from the input definitions.

## Design decisions

- Separate function selection from parameter extraction to give the small
  model a focused task at each stage.
- Keep full function names: experiments with short letter labels and a
  prefilled common name prefix reduced selection accuracy.
- Keep prompts concise and distinguish input arguments from results.
- Insert known grammar literals to avoid unnecessary model calls. Leave
  their final encoded token for constrained generation at the boundary,
  validate inserted bytes, and re-encode the resulting context. Never
  insert a guessed function choice or argument value.
- Default OpenMP and MKL thread counts to two before importing the SDK.
  Explicit environment settings take precedence.
- Use only public SDK methods. There is no custom model implementation,
  private SDK access, KV-cache modification, or function execution.
- Keep generation bounded: at most 128 selection steps and a 256-token
  parameter-generation budget. Failure produces an error, not partial JSON.

### Source layout

| File | Responsibility |
| --- | --- |
| `__main__.py` | Configure threads and start the application |
| `main.py` | Parse CLI options, load inputs, report errors, save results |
| `models.py` | Validate requests and function definitions |
| `file_io.py` | Read JSON and replace output files atomically |
| `pipeline.py` | Coordinate selection and argument extraction |
| `prompts.py` | Build the two model prompts |
| `llm.py` | Mask logits and generate constrained answers |
| `constraints.py` | Validate token bytes against the grammar |
| `vocabulary.py` | Map vocabulary IDs to byte fragments |
| `validation.py` | Check completed arguments against the schema |

## Performance analysis

The optimized version was measured on the supplied eleven English requests
in the development WSL environment, using Python 3.11.16, the default
Qwen/Qwen3-0.6B model, and two OpenMP/MKL threads.

| Run | Reported elapsed time |
| --- | ---: |
| After unique-candidate completion was added | 144.21 seconds |
| After `make fclean`, `make install`, and `make run` | 146.13 seconds |

Both runs finished below the subject's five-minute target. The second run's
JSON was inspected: all eleven function selections and argument objects
were correct for these examples, including the regex parameters. The
output was valid JSON, and `make lint` passed on all eleven source files.
This is a small demonstration set, not a guarantee of 90% accuracy on
unseen requests or of the same runtime on other hardware.

The reported application timer includes input loading, model initialization,
generation, validation, and output writing. It starts after Python imports;
it does not include dependency installation. The model files were already
cached in both runs. `fclean` removed the virtual environment and results,
but did not clear the downloaded model cache.

Before the unique-candidate optimization, a diagnostic run took 246.74
seconds for the batch, with a further 10.15 seconds for imports. Its
breakdown was:

| Operation | Time | Calls |
| --- | ---: | ---: |
| Model logits | 219.49 seconds | 162 |
| Allowed-token checks | 15.97 seconds | 162 |
| Model initialization | 8.85 seconds | 1 |
| Masking and greedy selection | 1.34 seconds | 162 |
| Vocabulary path lookup and loading | 0.80 seconds | 2 |
| Tokenization | 0.04 seconds | 79 |

These measurements identify model inference as the main cost: about 89%
of that diagnostic batch. There were 66 model calls for function selection
and 96 for parameters. Those counts describe the version before early
completion, not the optimized version. Other earlier runs were slower,
so the entire timing difference cannot be attributed to a single change.

The implementation reduces inference work through concise prompts, fixed
syntax insertion, and completion of uniquely identified function names.
It does not modify the SDK or implement KV caching. CPU load, thread count,
hardware, and cache state can affect the observed runtime.

Constraints enforce accepted structure and schema, not the meaning of
argument values. No output is replaced when generation or validation
fails. Extremely large floating-point exponents can parse as infinity and
are then rejected by final validation.

## Challenges faced

- Token IDs are not characters. Tokens can include whitespace, several
  characters, or multiple grammar boundaries, so constraints inspect bytes.
- A valid JSON string may still contain the wrong argument, such as a
  reversed result. Focused prompts tell the model to extract input values.
- JSON `\b` decodes to a backspace; a regex word boundary needs an actual
  backslash followed by `b`. Regex behavior must be checked, not just its
  JSON validity. The sample digits pattern can also use `[0-9]+`.
- Numbers can be complete and still accept more digits. The decoder tries
  to continue the number before advancing to the following punctuation.
- The SDK's runtime imports were not sufficient for static checking.
  Separate type declarations describe its public API without editing it.

## Testing strategy

Development checks cover scalar grammars, invalid and incomplete tokens,
tokens crossing field boundaries, empty objects, finite logits, token
limits, updated generation context, exact parameter keys and types, and
preserving existing output on write failure. Scripted model tests exercise
generation without downloading a model; real-model runs check semantics.

CLI checks include missing files, malformed JSON, invalid request types,
empty input arrays, and output preservation on failure. Additional function
definitions exercise boolean, integer, and empty argument lists.

Run `make lint` and `make lint-strict`, then run the default batch and inspect
the resulting JSON. Check extracted values as well as parseability. For
regex calls, independently apply the generated pattern to the source in a
test program. Test programs are development tools, separate from the
submission, as specified by the subject. Do not commit generated output.

## Resources

- The supplied Call Me Maybe subject and `llm_sdk` public method docstrings.
- [Python JSON documentation](https://docs.python.org/3/library/json.html)
- [Python typing](https://docs.python.org/3/library/typing.html)
- [Pydantic documentation](https://docs.pydantic.dev/latest/)
- [Qwen3-0.6B model card](https://huggingface.co/Qwen/Qwen3-0.6B)

AI assistance was used to explain tokenization and constrained decoding,
develop and debug grammar functions and generation loops, investigate
performance, prepare tests, correct formatting and type hints, remove
unused learning code, and draft this documentation. The author must review
the code and be able to explain and modify it during evaluation.
