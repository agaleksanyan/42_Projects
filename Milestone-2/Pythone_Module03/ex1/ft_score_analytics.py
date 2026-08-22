import sys
from typing import List


def parse_scores(args: List[str]) -> List[int]:
    scores: List[int] = []

    for arg in args:
        try:
            value = int(arg)
            scores.append(value)
        except ValueError:
            print(f"Invalid parameter: '{arg}'")

    return scores


def print_stats(scores: List[int]) -> None:
    total = sum(scores)
    count = len(scores)
    average = total / count
    high = max(scores)
    low = min(scores)
    score_range = high - low

    print("=== Player Score Analytics ===")
    print(f"Scores processed: {scores}")
    print(f"Total players: {count}")
    print(f"Total score: {total}")
    print(f"Average score: {average}")
    print(f"High score: {high}")
    print(f"Low score: {low}")
    print(f"Score range: {score_range}")


def main() -> None:
    args = sys.argv[1:]

    if len(args) == 0:
        print("=== Player Score Analytics ===")
        print("No scores provided. Usage: "
              "python3 ft_score_analytics.py <score1> <score2> ...")
        return

    scores = parse_scores(args)

    if len(scores) == 0:
        print("=== Player Score Analytics ===")
        print("No scores provided. Usage: "
              "python3 ft_score_analytics.py <score1> <score2> ...")
        return

    print_stats(scores)


if __name__ == "__main__":
    main()
