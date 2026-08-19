import sys

print("=== Inventory System Analysis ===")

inventory: dict[str, int] = {}

for arg in sys.argv[1:]:
    if ":" not in arg:
        print(f"Error - invalid parameter '{arg}'")
        continue

    name, quantity_str = arg.split(":", 1)

    if name in inventory:
        print(f"Redundant item '{name}' - discarding")
        continue

    try:
        quantity = int(quantity_str)
    except ValueError as e:
        print(f"Quantity error for '{name}': {e}")
        continue

    inventory[name] = quantity

print(f"Got inventory: {inventory}")

items = list(inventory.keys())
print(f"Item list: {items}")

total = sum(inventory.values())
print(f"Total quantity of the {len(items)} items: {total}")

for name in items:
    percent = (inventory[name] / total) * 100 if total else 0
    print(f"Item {name} represents {round(percent, 1)}%")

most_item = None
least_item = None

for name in items:
    if most_item is None or inventory[name] > inventory[most_item]:
        most_item = name
    if least_item is None or inventory[name] < inventory[least_item]:
        least_item = name

if most_item:
    print(
        f"Item most abundant: "
        f"{most_item} "
        "with quantity "
        f"{inventory[most_item]}"
    )
if least_item:
    print(
        f"Item least abundant: "
        f"{least_item} "
        "with quantity "
        f"{inventory[least_item]}"
    )

inventory.update({"magic_item": 1})
print(f"Updated inventory: {inventory}")
