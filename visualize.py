import sys
import time
from contextlib import contextmanager

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

COLS: dict[str, str] = {"Timestamp(ms)": np.float32, "Current(uA)": np.float64, "D0-D7": np.uint8}
# TODO: Auto state discovery - We can put macros on C side and grep them?
STATES: dict[int, str] = {0: "Other", 15: "Done", 1: "Bubble Sort", 2: "Insertion Sort", 3: "Merge Sort", 4: "Quick Sort", 5: "Heap Sort", 6: "Gnome Sort", 7: "Radix Sort", 8: "Shell Sort", 9: "Comb Sort", 10: "Pancake Sort"}


@contextmanager
def benchmark(title: str):
    try:
        start: float = time.time()
        yield
    finally:
        end: float = time.time()
        print(f"Finished section '{title}' in {end - start:.3f}s.")


def main() -> None:
    with benchmark("Load CSV"):
        data = pd.read_csv(sys.argv[1], usecols=COLS.keys(), dtype=COLS, converters={"D0-D7": lambda s: np.uint8(int(s[::-1], 2))})

    data.info()

    with benchmark("Process data"):
        # Skip 0 and 240 for now
        level_group = data.loc[~data["D0-D7"].isin((0, 15))].groupby("D0-D7")
        # We're supplying 5V, every data point is for 0.01ms(10^-5). Current is micro(10^-6)amps. Turning uA -> A, ms -> h, end result -> Wh.
        total_usages = level_group["Current(uA)"].agg("sum").rename(index=STATES) * 5 / 1_000_000 / 100_000 / 3600

    with benchmark("Plot"):
        ax = sns.barplot(x=total_usages.index.rename("States"), y=total_usages.rename("Watt-hours"), hue=total_usages.rename("Watt-hours")).set_title(f"Total Energy Consumption - {sys.argv[1]}")

    plt.ylim(0, 1.5 * 10 ** -5)
    plt.show()


if __name__ == "__main__":
    main()
