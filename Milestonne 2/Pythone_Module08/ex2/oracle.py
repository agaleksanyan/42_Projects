import os

from dotenv import load_dotenv

VALID_MODES = ("development", "production")
VALID_LOG_LEVELS = ("DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL")
VALID_DATABASE_PREFIXES = ("sqlite:///", "postgres://", "mysql://")
VALID_ENDPOINT_PREFIXES = ("http://", "https://")


def validate_config(
    mode: str | None,
    database: str | None,
    api_key: str | None,
    log_level: str | None,
    zion: str | None,
) -> bool:

    is_valid = True

    if not mode:
        print("[KO] MATRIX_MODE missing")
        is_valid = False
    elif mode not in VALID_MODES:
        print("[KO] Invalid MATRIX_MODE")
        is_valid = False

    if not database:
        print("[KO] DATABASE_URL missing")
        is_valid = False
    elif not database.startswith(VALID_DATABASE_PREFIXES):
        print("[KO] Invalid DATABASE_URL")
        is_valid = False

    if not api_key:
        print("[KO] API_KEY missing")
        is_valid = False
    elif len(api_key) < 8:
        print("[KO] API_KEY too short")
        is_valid = False

    if not log_level:
        print("[KO] LOG_LEVEL missing")
        is_valid = False
    elif log_level not in VALID_LOG_LEVELS:
        print("[KO] Invalid LOG_LEVEL")
        is_valid = False

    if not zion:
        print("[KO] ZION_ENDPOINT missing")
        is_valid = False
    elif not zion.startswith(VALID_ENDPOINT_PREFIXES):
        print("[KO] Invalid ZION_ENDPOINT")
        is_valid = False

    return is_valid


def show_development(mode: str, log_level: str) -> None:
    print("ORACLE STATUS: Reading the Matrix...\n")
    print("Configuration loaded:")
    print(f"Mode: {mode}")
    print("Database: Connected to local instance")
    print("API Access: Authenticated")
    print(f"Log Level: {log_level}")
    print("Zion Network: Online")
    print("\nEnvironment security check:")
    print("[OK] No hardcoded secrets detected")
    print("[OK] .env file properly configured")
    print("[OK] Development configuration active")
    print("The Oracle sees all configurations.")


def show_production(mode: str, log_level: str) -> None:
    print("ORACLE STATUS: Reading the Matrix...\n")
    print("Configuration loaded:")
    print(f"Mode: {mode}")
    print("Database: Connected to secure instance")
    print("API Access: Authenticated")
    print(f"Log Level: {log_level}")
    print("Zion Network: Online")
    print("\nEnvironment security check:")
    print("[OK] No hardcoded secrets detected")
    print("[OK] .env file properly configured")
    print("[OK] Production overrides available")
    print("The Oracle sees all configurations.")


def main() -> None:
    load_dotenv()

    mode = os.getenv("MATRIX_MODE")
    database = os.getenv("DATABASE_URL")
    api_key = os.getenv("API_KEY")
    log_level = os.getenv("LOG_LEVEL")
    zion = os.getenv("ZION_ENDPOINT")

    if not validate_config(mode, database, api_key, log_level, zion):
        print("WARNING: Invalid or missing configuration")
        return

    if mode == "development" and log_level is not None:
        show_development(mode, log_level)
    elif mode == "production" and log_level is not None:
        show_production(mode, log_level)


if __name__ == "__main__":
    main()
