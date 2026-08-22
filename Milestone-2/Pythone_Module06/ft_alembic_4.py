import alchemy

print("=== Alembic 4 ===")
print("Accessing the alchemy module using 'import alchemy'")

print(f"Testing create_air : {alchemy.create_air()}")

try:
    earth = alchemy.create_earth()  # type: ignore[attr-defined]
    print(f"Testing create_earth : {earth}")
except ValueError as e:
    print(f"{e}")
