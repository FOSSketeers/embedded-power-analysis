# Embedded Power Analysis

In this research project, we examine the energy consumption of variety of subprograms or any other embedded related quirky experiments. We try to log experiment results as much as we can for us to go back and make use of it when needed. For the topics we consider meaningful and feasible to dive deeper, we try to work out a formal research publication. Here in this repository and the organization, everything we do is open to public and will stay that way.

## How To Run?

Working with many experiments and more than one embedded device requires us to have a workflow that would make our lives easier, PlatformIO perfectly fulfills this requirement.

1. Make sure [PlatformIO extension](https://open-vsx.org/vscode/item?itemName=platformio.platformio-ide) is installed in your VS Code.
2. Choose whichever project environment you want to try out.

![PlatformIO Environment](/assets/platformio-tutorial-1.gif)

Debug environment is used to debug the program when the board is connected to the computer. Serial output is open, and certain numerical parameters like `ENVIRONMENT_DELAY` and `ALGORTIHM_DELAY` are greater in the debug mode. Measuring the energy consumption on a loaded debug program is perfectly okay, yet to minimize noise and output size we recommend using meausurement mode.

To see the serial outputs, kindly use the PlatformIO's serial monitor tab.

### Physical Setup

All of the circuit connections are shown at [circuits](/circuits/) directory in both PNG and SVG format. For sake of security, turning off the PPK while loading program from computer to board is highly recommended.

|                                            | Arduino UNO R3               | Arduino UNO R4 Minima        |
| ------------------------------------------ | ---------------------------- | ---------------------------- |
| 5V Digital I/O Semi Supported (deprecated) | [000.png](/circuits/000.png) | [001.png](/circuits/001.png) |
| 5V Digital I/O Supported                   | [002.png](/circuits/002.png) | [003.png](/circuits/003.png) |
| 3.3V Digital I/O Supported                 | [004.png](/circuits/004.png) | [005.png](/circuits/005.png) |

### New Benchmark

Introducing a new benchmark is fairly easy in our workflow. All you have to do is following the 4 steps below:

1. Create a directory under [benchmarks](/benchmarks/).
2. Make sure `void setup()` and `void loop()` functions are defined in your code. You can always take a peek from other benchmarks.
3. Update the list of [benchmarks](/pio-config/02-benchmarks.ini).
4. Run `python pio-config/generate-pio-config.py`.

### How To Measure?

You can either use official [nRF Connect](https://www.nordicsemi.com/Products/Development-tools/nRF-Connect-for-Desktop) application from Nordic, or you can use [our modified version](https://github.com/FOSSketeers/pc-nrfconnect-ppk) of it. We have modified the nRF Connect application in order to automate the measurement flow.

![nRF Connect](/assets/nrf-connect-preview-1.png)

## Experiment Logs

You can find the previous measurements and their setup at [experiment.md](/experiments.md).
