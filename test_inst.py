#!/usr/bin/env python3

import argparse
import subprocess
from tempfile import NamedTemporaryFile

def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--instruction', required=True)
    parser.add_argument('-c', '--count', type=int, default=1000)
    parser.add_argument('-p', '--part', default="atmega328p")
    parser.add_argument('-P', '--port', default="/dev/ttyUSB0")
    parser.add_argument('-k', '--keep', default=False, action='store_true')
    args = parser.parse_args()

    c_lines: list[str] = [
        "void main() {",
        "    while (1)",
        "    __asm__ volatile ("
    ]

    for _ in range(args.count):
        c_lines.append(f"        \"{args.instruction}\\n\\t\"")

    c_lines.extend([
        "    );",
        "}"
    ])

    with (
        NamedTemporaryFile(mode='w', suffix='.c', delete=not args.keep) as c_source,
        NamedTemporaryFile(suffix='.elf', delete=not args.keep) as elf_file,
        NamedTemporaryFile(suffix='.hex', delete=not args.keep) as hex_out
    ):
        c_source.write("\n".join(c_lines))
        c_source.flush()
        print(f"C source file: {c_source.name}")

        subprocess.check_call(['avr-gcc', '-O0', f'-mmcu={args.part}', '-o', elf_file.name, c_source.name])
        print(f"ELF file: {elf_file.name}")

        subprocess.check_call(['avr-objcopy', '-O', 'ihex', elf_file.name, hex_out.name])
        print(f"Hex out file: {hex_out.name}")

        subprocess.check_call(['avrdude', '-c', 'arduino', '-p', args.part, "-P", args.port, '-U', f'flash:w:{hex_out.name}:i'])


if __name__ == "__main__":
    main()
