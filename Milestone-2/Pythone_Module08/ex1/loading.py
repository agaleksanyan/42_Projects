import importlib
from types import ModuleType


def check_package(package_name: str, message: str) -> ModuleType | None:
    try:
        module = importlib.import_module(package_name)
        version = getattr(module, "__version__", "unknown")
        print(f"[OK] {package_name} ({version}) - {message}")
        return module
    except ModuleNotFoundError:
        print(f"[KO] {package_name} - package is missing")
        return None


def main() -> None:

    print("LOADING STATUS: Loading programs...\n")
    print("Checking dependencies:")
    pandas = check_package("pandas", "Data manipulation ready")
    numpy = check_package("numpy", "Numerical computation ready")
    matplotlib = check_package("matplotlib", "Visualization ready")

    if not pandas or not numpy or not matplotlib:
        print("\nInstall dependencies with:")
        print("pip install -r requirements.txt")
        print("or")
        print("poetry install")
        return

    print("\nAnalyzing Matrix data...")

    matrix_data = numpy.random.random(1000)

    print(f"Processing {len(matrix_data)} data points...")

    data_frame = pandas.DataFrame(
        matrix_data,
        columns=["Matrix Signal"],
    )

    average_signal = data_frame["Matrix Signal"].mean()
    max_signal = data_frame["Matrix Signal"].max()
    min_signal = data_frame["Matrix Signal"].min()

    print("\nAnalysis:")
    print(f"Average signal: {average_signal:.4f}")
    print(f"Max signal: {max_signal:.4f}")
    print(f"Min signal: {min_signal:.4f}")

    pyplot = importlib.import_module("matplotlib.pyplot")

    print("\nGenerating visualization...")

    pyplot.plot(data_frame["Matrix Signal"])
    pyplot.title("Matrix Signal Analysis")
    pyplot.xlabel("Data Point")
    pyplot.ylabel("Signal Strength")
    pyplot.savefig("matrix_analysis.png")
    pyplot.close()

    print("Analysis complete!")
    print("Results saved to: matrix_analysis.png")


if __name__ == "__main__":
    main()
