# NanoTekSpice 
Nanotekspice is a digital electronics circuit simulator of logic gates built in C++ 
## Build 
``` sh
make
```

## Usage
``` sh
./nanotekspice <circuit_file.nts>
```

### Example
``` sh
./nanotekspice nts_single/or.nts 
> display
tick: 0
input(s):
  in_1: U
  in_2: U
output(s):
  out: U
> in_1 = 0
> in_2 = 0
> simulate
> display
tick: 1
input(s):
  in_1: 0
  in_2: 0
output(s):
  out: 0
> in_1 = 1
> simulate
> display
tick: 2
input(s):
  in_1: 1
  in_2: 0
output(s):
  out: 1
> exit

```
## Commands
- simulate: simulate a tick of the circuit.
- display:  prints the current value of all inputs and outputs in the standard output.
- in_=value: changes the value of an input. The value can be 0, 1 and U.
- loop: runs the simulation continuously without displaying a prompt, until SIGINT is received.
- exit:  closes the program.
#  Graphical Circuit
An interactive SFML circuit editor with some visualization and simulation.
## Build
``` sh
make
```
# Usage
``` sh
./nanotekspice_bonus -h
NanoTekSpice - Graphical Circuit Editor
========================================

Usage:
  ./nanotekspice_bonus                  # Start empty editor

Controls:
  [S] - Select mode (drag components)
  [W] - Wire mode (click pins to connect)
  [D] - Delete mode (click to delete)
  [Space] - Simulate one tick
  [R] - Reset circuit
```
## Demo
``` sh
  ./nanotekspice_bonus  
```
https://github.com/user-attachments/assets/49c58f53-6c29-4151-97f9-7cb84796c7eb

## Components
### Special components
- Input
- Output
- Clock
- True
- False
- Logger
### Elementary components
- AND
- OR
- XOR
- NOT
### Gates
- 4001 : Four NOR gates
- 4011 : Four NAND gates
- 4030 : Four XOR gates
- 4069 : six NOT gates
- 4071 : Four OR gates
- 4081 : Four AND gates


