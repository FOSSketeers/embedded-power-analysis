#!/usr/bin/env python3

from pathlib import Path
from configparser import ConfigParser
import shutil


def main() -> None:
    repo_root: Path = Path(__file__).resolve().parent.parent
    pio_config_dir: Path = repo_root / "pio-config"
    base_ini_file = pio_config_dir / "00-base.ini"
    output_file: Path = repo_root / "platformio.ini"

    base_config = ConfigParser()
    base_config.read(base_ini_file)

    # Read the list of extra configs
    extra_config_files: list[Path] = [
        repo_root / line.strip()
        for line in base_config.get("platformio", "extra_configs").strip().splitlines()
    ]

    # Save the [section] names in the extra configs to a dict
    config_keywords: dict[str, list[str]] = dict()
    for cfg_file in extra_config_files:
        cfg_reader = ConfigParser()
        cfg_reader.read(cfg_file)
        cfg_name = cfg_file.name.split("-")[1].removesuffix(".ini")
        config_keywords[cfg_name] = cfg_reader.sections()

    # Copy the base ini file to the destination and generate the rest
    shutil.copy(base_ini_file, output_file)
    with open(output_file, mode="a") as file:
        for benchmark in config_keywords["benchmarks"]:
            file.write(
                f"\n; =========== Experiment: {benchmark.replace('-', ' ').title().replace('Llm', 'LLM')} ===========\n"
            )

            for buildmode in config_keywords["buildmodes"]:
                for board in config_keywords["boards"]:
                    file.write(f"[env:{board}-{benchmark}-{buildmode}]\n")
                    file.write(f"extends = {board}, {benchmark}, {buildmode}\n\n")

    print("done")


if __name__ == "__main__":
    main()
