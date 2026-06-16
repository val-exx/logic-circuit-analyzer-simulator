# Logic Circuit Analyzer and Simulator

[![Build and Run](https://github.com/val-exx/logic-circuit-analyzer-simulator/actions/workflows/build-and-run.yml/badge.svg)](https://github.com/val-exx/logic-circuit-analyzer-simulator/actions/workflows/build-and-run.yml)

C++ project originally developed for an Algorithms and Computer Architecture course.

The original assignment was not available in the project folder. The description below was reconstructed from the source code and the included example files.

## Reconstructed Assignment

Build a C++ program able to read the textual description of a logic circuit, create an internal tree-based representation, and provide three main features:

1. simulate the circuit on binary input sequences;
2. perform structural analysis of the circuit;
3. compose circuits through a library mode.

The program supports combinational circuits, sequential circuits with flip-flops, and composite circuits built from instantiated modules.

## Features

- Parses circuit files written in a simplified Verilog-like syntax.
- Supports scalar and vector inputs/outputs, for example `a[3]`.
- Supports the logic operators `AND`, `OR`, `NOT`, `NAND`, `NOR`, `XOR`, `XNOR`, and flip-flops `FF`.
- Builds the circuit as a set of trees, one for each output.
- Simulates the circuit over multiple binary input rows.
- Computes total power consumption based on `0 -> 1` and `1 -> 0` transitions of the operators used.
- Performs structural analysis of:
  - minimum path;
  - maximum path;
  - logical cones, meaning the input signals required for each output;
  - minimum and maximum loops in sequential circuits.
- Handles invalid cases such as empty files, inconsistent inputs/outputs, feedback in combinational circuits, and missing operators in the power consumption file.

## Key Concepts and Skills

This project highlights skills relevant to software engineering, embedded systems, electronic design automation (EDA), digital systems, and C++ development roles.

### Core Concepts

- **Tree data structures**: the circuit is represented as a set of logic trees, one for each output.
- **Graphs and logical dependencies**: sub-circuits, flip-flops, and intermediate signals require dependency modeling between nodes.
- **Recursion and tree traversal**: simulation, path computation, and leaf discovery are implemented through recursive traversals.
- **Custom language parsing**: the program interprets a simplified Verilog-like textual syntax.
- **Input validation**: the program detects empty files, inconsistent inputs/outputs, invalid feedback, and missing operators.
- **Discrete simulation**: circuit behavior is evaluated over time-based sequences of binary inputs.
- **Static circuit analysis**: minimum path, maximum path, logical cones, and sequential loops are extracted from the circuit representation.
- **Modularity and reuse**: library mode allows one circuit to be instantiated inside another through explicit signal links.

### Technical Skills Demonstrated

- C++ programming with classes, structs, pointers, `vector`, iterators, and file streams.
- Object-oriented design with dedicated classes for circuit construction, simulation, analysis, composition, and logic gates.
- Manual management of dynamic data structures through nodes and pointers.
- Implementation of tree traversal and analysis algorithms.
- Modeling of combinational and sequential logic gates.
- Reading and writing text files for configuration, input, output, and reports.
- Separation of responsibilities across program components.
- Handling of edge cases and error messages for invalid input.
- Familiarity with Visual Studio and C++ console projects.
- Basic continuous integration setup with GitHub Actions.

### Recruiter-Friendly Summary

University C++ project implementing a simulator and analyzer for logic circuits described through text files. The program parses a custom syntax, builds an internal tree-based representation, simulates combinational and sequential circuits, computes structural metrics, and supports modular circuit composition. The project demonstrates skills in algorithms, data structures, recursion, parsing, object-oriented programming, and complex input handling.

## Project Structure

```text
.
|-- LogicCircuitAnalyzerSimulator.sln
|-- LogicCircuitAnalyzerSimulator/
|   |-- *.cpp, *.h              # C++ source code
|   |-- Circuito_*.txt          # Example circuits
|   |-- Combinatorio_*.txt      # Test/error cases for combinational circuits
|   |-- input*.txt              # Simulation inputs
|   |-- consumo_potenza*.txt    # Operator power consumption files
|   `-- percorso_file.txt       # File used by library mode
`-- README.md
```

## Circuit File Format

A circuit is described with a textual syntax like this:

```text
module NOME_CIRCUITO (
input a[3]
output x[2]
);
assign x[0] = a[2] OR (a[0] AND a[1])
assign x[1] = NOT a[2]
endmodule
```

In sequential circuits, a `clk` line is present and flip-flops are described through assignments without the `assign` keyword:

```text
module circuito (
clk
input a[2]
input c
output x
);
FF1 = a[0] XOR a[1]
FF2 = FF1 XNOR (NOT c)
assign x = FF1 NAND FF2
endmodule
```

Composite circuits use an `instance` line:

```text
Combinatorio_per_composito instance (.a = input1, .b = input2, .c = input3, .x = FF1)
```

## Simulation Files

The input file contains one binary sequence per row:

```text
10000101
00110100
11110010
00010001
```

The power consumption file contains a header followed by one row per operator:

```text
Consumo potenza operatori
FF;0.5;0.25
NOT;0.1;0.34
OR;0.2;0.56
```

Each row follows this format:

```text
OPERATOR;transition_0_to_1_consumption;transition_1_to_0_consumption
```

## How to Run

The project was originally built as a Visual Studio console application.

## Automated Build and Sample Runs

The original project was designed to be compiled locally with Visual Studio. As part of the repository cleanup and modernization, a GitHub Actions workflow was added to provide a basic **continuous integration (CI)** pipeline.

The workflow runs on Ubuntu, compiles the project with `g++`, and executes sample analysis and simulation runs using the included circuit files. This makes the repository self-checking: every push to `main` verifies that the code still builds and that representative examples can run successfully.

The workflow can be found in `.github/workflows/build-and-run.yml`, and its output is visible in the repository's **Actions** tab.

This is CI rather than full CI/CD: the workflow builds and runs the project automatically, but it does not deploy or publish a release artifact.

### With Visual Studio

1. Open `LogicCircuitAnalyzerSimulator.sln`.
2. Build the desired configuration.
3. Run the executable by passing a circuit file as argument.

Example from the terminal, running from the `LogicCircuitAnalyzerSimulator` folder:

```powershell
..\Debug\LogicCircuitAnalyzerSimulator.exe Circuito_Combinatorio.txt
```

### Program Flow

At startup, the program asks for one of the following options:

```text
1. Simulazione circuito
2. Analisi circuito
3. Modalita' Libreria
```

For simulation, the program asks for:

1. the input file name, without the `.txt` extension;
2. the power consumption file name, without the `.txt` extension;
3. whether to print the result to the screen or to a file.

Example answers:

```text
1
input
consumo_potenza
1
```

For analysis, the program directly prints the minimum path, maximum path, logical cones, and sequential loops when present.

For library mode, first run the module to be inserted, then provide a file containing the path to the main/composite circuit. With the included examples:

```powershell
..\Debug\LogicCircuitAnalyzerSimulator.exe Combinatorio_per_composito.txt
```

then choose `3` and enter `percorso_file`.

## Included Examples

- `Circuito_Combinatorio.txt`: combinational circuit with vector inputs and outputs.
- `Circuito_Sequenziale.txt`: sequential circuit with two flip-flops.
- `Circuito_Composito.txt`: circuit that instantiates a combinational module.
- `Combinatorio_per_composito.txt`: module used in the composite example.
- `Combinatorio_con_feedback.txt`: error case for feedback in a combinational circuit.
- `Combinatorio_input_non_corrispondenti.txt`: input mismatch error case.
- `Combinatorio_output_non_corrispondenti.txt`: output mismatch error case.
- `input*.txt`: valid and intentionally invalid input cases.
- `consumo_potenza*.txt`: valid and intentionally incomplete/invalid operator power files.

## Notes

This is a historical university project and keeps its original Visual Studio 2017 (`v141`) structure. The folder has been cleaned from build artifacts to make it suitable for upload to GitHub.
