.DEFAULT_GOAL := run

ARGS ?=

.PHONY: install run debug lint lint-strict clean fclean

install:
	uv sync --group dev

run:
	uv run python -m src $(ARGS)

debug:
	uv run python -m pdb -m src $(ARGS)

lint:
	uv run flake8 .
	uv run mypy . --warn-return-any --warn-unused-ignores \
		--ignore-missing-imports --disallow-untyped-defs --check-untyped-defs

lint-strict:
	uv run flake8 .
	uv run mypy . --strict

clean:
	find src -type d -name __pycache__ -prune -exec rm -rf {} +
	find src -type f \( -name '*.pyc' -o -name '*.pyo' \) -delete
	rm -rf .mypy_cache .pytest_cache .ruff_cache
	rm -rf data/output

fclean: clean
	rm -rf .venv
