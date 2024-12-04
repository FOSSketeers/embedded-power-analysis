import argparse
import time
from concurrent.futures import ThreadPoolExecutor
from contextlib import contextmanager
from functools import partial

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
from enum import Enum

COLS: dict[str, type] = {"Timestamp(ms)": np.float32, "Current(uA)": np.float64, "D0-D7": np.uint8}
# TODO: Auto state discovery - We can put macros on C side and grep them?
#STATES: dict[int, str] = {0: "Other", 15: "Done", 1: "Bubble Sort", 2: "Insertion Sort", 3: "Merge Sort", 4: "Quick Sort", 5: "Heap Sort", 6: "Gnome Sort", 7: "Radix Sort", 8: "Shell Sort", 9: "Comb Sort", 10: "Pancake Sort"}

class Boards(Enum):
    UNO_R3 = 0
    UNO_R4 = 1

class Benchmarks(Enum):
    # Good old normal sort for numba 0?
    LLMSORT = 1
    CRYPTO = 2

# State numbers and state titles are tied to each other based on their indices, so the order matters here!
STATE_NUMBERS: dict[Boards, list[int]] = {
    Boards.UNO_R3: [0b11111111, 0b00000000, 0b10000000, 0b01000000, 0b11000000, 0b00100000, 0b10100000, 0b01100000, 0b11100000, 0b00010000, 0b10010000, 0b01010000, 0b11010000, 0b00110000, 0b10110000, 0b01110000, 0b11110000, 0b00001000, 0b10001000, 0b01001000, 0b11001000, 0b00101000, 0b10101000, 0b01101000, 0b11101000, 0b00011000, 0b10011000, 0b01011000, 0b11011000, 0b00111000, 0b10111000, 0b01111000, 0b11111000, 0b00000100, 0b10000100, 0b01000100, 0b11000100, 0b00100100, 0b10100100, 0b01100100, 0b11100100, 0b00010100, 0b10010100, 0b01010100, 0b11010100, 0b00110100, 0b10110100, 0b01110100, 0b11110100, 0b00001100, 0b10001100, 0b01001100, 0b11001100, 0b00101100, 0b10101100, 0b01101100, 0b11101100, 0b00011100, 0b10011100, 0b01011100, 0b11011100, 0b00111100, 0b10111100, 0b01111100, 0b11111100, 0b00000010, 0b10000010, 0b01000010, 0b11000010, 0b00100010, 0b10100010, 0b01100010, 0b11100010, 0b00010010, 0b10010010, 0b01010010, 0b11010010, 0b00110010, 0b10110010, 0b01110010, 0b11110010, 0b00001010, 0b10001010, 0b01001010, 0b11001010, 0b00101010, 0b10101010, 0b01101010, 0b11101010, 0b00011010, 0b10011010, 0b01011010, 0b11011010, 0b00111010, 0b10111010, 0b01111010, 0b11111010, 0b00000110, 0b10000110, 0b01000110, 0b11000110, 0b00100110, 0b10100110, 0b01100110, 0b11100110, 0b00010110, 0b10010110, 0b01010110, 0b11010110, 0b00110110, 0b10110110, 0b01110110, 0b11110110, 0b00001110, 0b10001110, 0b01001110, 0b11001110, 0b00101110, 0b10101110, 0b01101110, 0b11101110, 0b00011110, 0b10011110, 0b01011110, 0b11011110, 0b00111110, 0b10111110, 0b01111110, 0b11111110, 0b00000001, 0b10000001, 0b01000001, 0b11000001, 0b00100001, 0b10100001, 0b01100001, 0b11100001, 0b00010001, 0b10010001, 0b01010001, 0b11010001, 0b00110001, 0b10110001, 0b01110001, 0b11110001, 0b00001001, 0b10001001, 0b01001001, 0b11001001, 0b00101001, 0b10101001, 0b01101001, 0b11101001, 0b00011001, 0b10011001, 0b01011001, 0b11011001, 0b00111001, 0b10111001, 0b01111001, 0b11111001, 0b00000101, 0b10000101, 0b01000101, 0b11000101, 0b00100101, 0b10100101, 0b01100101, 0b11100101, 0b00010101, 0b10010101, 0b01010101, 0b11010101, 0b00110101, 0b10110101, 0b01110101, 0b11110101, 0b00001101, 0b10001101, 0b01001101, 0b11001101, 0b00101101, 0b10101101, 0b01101101, 0b11101101, 0b00011101, 0b10011101, 0b01011101, 0b11011101, 0b00111101, 0b10111101, 0b01111101, 0b11111101, 0b00000011, 0b10000011, 0b01000011, 0b11000011, 0b00100011, 0b10100011, 0b01100011, 0b11100011, 0b00010011, 0b10010011, 0b01010011, 0b11010011, 0b00110011, 0b10110011, 0b01110011, 0b11110011, 0b00001011, 0b10001011, 0b01001011, 0b11001011, 0b00101011, 0b10101011, 0b01101011, 0b11101011, 0b00011011, 0b10011011, 0b01011011, 0b11011011, 0b00111011, 0b10111011, 0b01111011, 0b11111011, 0b00000111, 0b10000111, 0b01000111, 0b11000111, 0b00100111, 0b10100111, 0b01100111, 0b11100111, 0b00010111, 0b10010111, 0b01010111, 0b11010111, 0b00110111, 0b10110111, 0b01110111, 0b11110111, 0b00001111, 0b10001111, 0b01001111, 0b11001111, 0b00101111, 0b10101111, 0b01101111, 0b11101111, 0b00011111, 0b10011111, 0b01011111, 0b11011111, 0b00111111, 0b10111111, 0b01111111],
    Boards.UNO_R4: [0b11111111, 0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00010000, 0b00010001, 0b00010010, 0b00010011, 0b00100000, 0b00100001, 0b00100010, 0b00100011, 0b00110000, 0b00110001, 0b00110010, 0b00110011, 0b01000000, 0b01000001, 0b01000010, 0b01000011, 0b01010000, 0b01010001, 0b01010010, 0b01010011, 0b01100000, 0b01100001, 0b01100010, 0b01100011, 0b01110000, 0b01110001, 0b01110010, 0b01110011, 0b10000000, 0b10000001, 0b10000010, 0b10000011, 0b10010000, 0b10010001, 0b10010010, 0b10010011, 0b10100000, 0b10100001, 0b10100010, 0b10100011, 0b10110000, 0b10110001, 0b10110010, 0b10110011, 0b11000000, 0b11000001, 0b11000010, 0b11000011, 0b11010000, 0b11010001, 0b11010010, 0b11010011, 0b11100000, 0b11100001, 0b11100010, 0b11100011, 0b11110000, 0b11110001, 0b11110010, 0b11110011, 0b00001000, 0b00001001, 0b00001010, 0b00001011, 0b00011000, 0b00011001, 0b00011010, 0b00011011, 0b00101000, 0b00101001, 0b00101010, 0b00101011, 0b00111000, 0b00111001, 0b00111010, 0b00111011, 0b01001000, 0b01001001, 0b01001010, 0b01001011, 0b01011000, 0b01011001, 0b01011010, 0b01011011, 0b01101000, 0b01101001, 0b01101010, 0b01101011, 0b01111000, 0b01111001, 0b01111010, 0b01111011, 0b10001000, 0b10001001, 0b10001010, 0b10001011, 0b10011000, 0b10011001, 0b10011010, 0b10011011, 0b10101000, 0b10101001, 0b10101010, 0b10101011, 0b10111000, 0b10111001, 0b10111010, 0b10111011, 0b11001000, 0b11001001, 0b11001010, 0b11001011, 0b11011000, 0b11011001, 0b11011010, 0b11011011, 0b11101000, 0b11101001, 0b11101010, 0b11101011, 0b11111000, 0b11111001, 0b11111010, 0b11111011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00010100, 0b00010101, 0b00010110, 0b00010111, 0b00100100, 0b00100101, 0b00100110, 0b00100111, 0b00110100, 0b00110101, 0b00110110, 0b00110111, 0b01000100, 0b01000101, 0b01000110, 0b01000111, 0b01010100, 0b01010101, 0b01010110, 0b01010111, 0b01100100, 0b01100101, 0b01100110, 0b01100111, 0b01110100, 0b01110101, 0b01110110, 0b01110111, 0b10000100, 0b10000101, 0b10000110, 0b10000111, 0b10010100, 0b10010101, 0b10010110, 0b10010111, 0b10100100, 0b10100101, 0b10100110, 0b10100111, 0b10110100, 0b10110101, 0b10110110, 0b10110111, 0b11000100, 0b11000101, 0b11000110, 0b11000111, 0b11010100, 0b11010101, 0b11010110, 0b11010111, 0b11100100, 0b11100101, 0b11100110, 0b11100111, 0b11110100, 0b11110101, 0b11110110, 0b11110111, 0b00001100, 0b00001101, 0b00001110, 0b00001111, 0b00011100, 0b00011101, 0b00011110, 0b00011111, 0b00101100, 0b00101101, 0b00101110, 0b00101111, 0b00111100, 0b00111101, 0b00111110, 0b00111111, 0b01001100, 0b01001101, 0b01001110, 0b01001111, 0b01011100, 0b01011101, 0b01011110, 0b01011111, 0b01101100, 0b01101101, 0b01101110, 0b01101111, 0b01111100, 0b01111101, 0b01111110, 0b01111111, 0b10001100, 0b10001101, 0b10001110, 0b10001111, 0b10011100, 0b10011101, 0b10011110, 0b10011111, 0b10101100, 0b10101101, 0b10101110, 0b10101111, 0b10111100, 0b10111101, 0b10111110, 0b10111111, 0b11001100, 0b11001101, 0b11001110, 0b11001111, 0b11011100, 0b11011101, 0b11011110, 0b11011111, 0b11101100, 0b11101101, 0b11101110, 0b11101111, 0b11111100, 0b11111101, 0b11111110]
}
STATE_TITLES: dict[Benchmarks, list[str]] = {
    Benchmarks.LLMSORT: ["Done", "Other", "gpt_bubble", "cld_bubble", "gem_bubble", "gpt_insert", "cld_insert", "gem_insert", "gpt_merge", "cld_merge", "gem_merge", "gpt_quick", "cld_quick", "gem_quick", "gpt_heap", "cld_heap", "gem_heap", "gpt_gnome", "cld_gnome", "gem_gnome", "gpt_radix", "cld_radix", "gem_radix", "gpt_shell", "cld_shell", "gem_shell", "gpt_comb", "cld_comb", "gem_comb", "gpt_pancake", "cld_pancake", "gem_pancake"],
    Benchmarks.CRYPTO: ["Done", "Other", "chacha8", "chacha12", "chacha20", "aes128", "aes192", "aes256", "chacha20poly1305", "aes128-gcm", "aes192-gcm", "aes256-gcm", "acorn128", "ascon128"]
}

@contextmanager
def benchmark(title: str):
    try:
        start: float = time.time()
        yield
    finally:
        end: float = time.time()
        print(f"Finished section '{title}' in {end - start:.3f}s.")


def load_data(file: str) -> pd.DataFrame:
    board = Boards.UNO_R3 if "r3" in file.lower() else Boards.UNO_R4
    # maps state numbers of the board to indices
    index_mappings = dict(zip(STATE_NUMBERS[board], range(256)))
    return pd.read_csv(file, usecols=COLS.keys(), dtype=COLS, converters={"D0-D7": lambda s: index_mappings[np.uint8(int(s, 2))]}) # type: ignore


def process_data(data: pd.DataFrame, benchmark_type: Benchmarks) -> tuple[pd.Series, pd.Series, pd.Series]:
    # maps indices to titles
    benchmark_mappings = dict(zip(range(256), STATE_TITLES[benchmark_type])) # why didn't I use enumerate() here? whatevs, it's almost 4 AM

    # Skip 0 and 255 for now (indices 0 and 1)
    level_group = data.loc[~data["D0-D7"].isin((0, 1))].groupby("D0-D7")

    # We're supplying 5V, every data point is for 0.01ms(10^-5). Current is micro(10^-6)amps. Turning uA -> A, ms -> h, end result -> Wh.
    total_usages = level_group["Current(uA)"].agg("sum").rename(index=benchmark_mappings) * 5 / 1_000_000 / 100_000 / 3600

    # Each row is 0.01ms.
    timings = level_group["Timestamp(ms)"].count().rename(index=benchmark_mappings) * 0.01

    # Watt / ms?
    efficiency = (total_usages / timings).rename(index=benchmark_mappings)

    return total_usages, timings, efficiency


def main() -> None:
    datas: list[pd.DataFrame] = []
    processed_datas: list[tuple[pd.Series, pd.Series, pd.Series]] = []

    parser = argparse.ArgumentParser()
    parser.add_argument('files', action='extend', nargs='+')
    args = parser.parse_args()

    # assuming the files are from the same benchmark type
    benchmark_type = Benchmarks.LLMSORT if "llmsort" in args.files[0] else Benchmarks.CRYPTO

    with ThreadPoolExecutor() as executor:
        with benchmark("Load CSV"):
            datas.extend(executor.map(load_data, args.files))

        with benchmark("Process data"):
            processed_datas.extend(executor.map(partial(process_data, benchmark_type=benchmark_type), datas))

    with benchmark("Plot"):
        fig, axs = plt.subplots(nrows=3, ncols=len(args.files), squeeze=False, sharex="all", sharey="row")

        for (column, file), processed_data in zip(enumerate(args.files), processed_datas):
            total_usages, timings, efficiency = processed_data

            print("######### {file} #########")
            datas[column].info()
            print("===== ENERGY USAGES =====")
            print(total_usages.sort_values())
            print("===== TIMINGS =====")
            print(timings.sort_values())
            print("===== ENERGY EFFICIENCY =====")
            print(efficiency.sort_values())

            consumption_plot = sns.barplot(x=total_usages.index.rename("States"), y=total_usages.rename("Watt-hours"), hue=total_usages.rename("Watt-hours"), ax=axs[0, column])
            consumption_plot.set_ylim(0, 0.1 * 10 ** -5)
            consumption_plot.set_title(f"Total Energy Consumption - {file}")
            consumption_plot.tick_params(axis='x', rotation=75)

            time_plot = sns.barplot(x=timings.index.rename("States"), y=timings.rename("Microseconds"), hue=timings.rename("Microseconds"), ax=axs[1, column])
            time_plot.set_ylim(0, 30)
            time_plot.set_title(f"Total Time Spent - {file}")
            time_plot.tick_params(axis='x', rotation=75)

            efficiency_plot = sns.barplot(x=efficiency.index.rename("States"), y=efficiency.rename("Watt-hour per ms"), hue=efficiency.rename("Watt-hour per ms"), ax=axs[2, column])
            efficiency_plot.set_title(f"Efficiency - {file}")
            efficiency_plot.tick_params(axis='x', rotation=75)

    print("batashow")
    plt.show()


if __name__ == "__main__":
    main()
