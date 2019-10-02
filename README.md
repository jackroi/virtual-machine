<!--
<p align="center">
  <a href="" rel="noopener">
 <img width=200px height=200px src="https://i.imgur.com/6wj0hh6.jpg" alt="Project logo"></a>
</p>
-->

<h3 align="center">Simple virtual machine</h3>

<div align="center">

  [![Status](https://img.shields.io/badge/status-active-success.svg)]()
  [![GitHub Issues](https://img.shields.io/github/issues/jackroi/virtual-machine.svg)](https://github.com/jackroi/virtual-machine/issues)
  [![GitHub Pull Requests](https://img.shields.io/github/issues-pr/jackroi/virtual-machine.svg)](https://github.com/jackroi/virtual-machine/pulls)
  [![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)

</div>

---

<p align="center">
  A simple virtual machine, with register file and stack, able to execute simple machine code (proprietary machine code).
  <br>
</p>

## 📝 Table of Contents
- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)
- [Built Using](#built_using)
- [TODO](./todo.md)
- [Authors](#authors)
- [Acknowledgments](#acknowledgement)

## 🧐 About <a name="about"></a>
A simple virtual machine, with register file and stack, able to execute simple machine code (proprietary machine code).
<br>
Documentation (italian language):
- [Supported instructions](./docs/instructions.pdf)
- [Project specifications](./docs/project-specifications.pdf)

This project was realized for the C programming course of Ca' Foscari University of Venice.

### Note
The code is abundantly commented as required by the project specifications, and for future reference.

## 🏁 Getting Started <a name="getting_started"></a>
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
A Unix based distrubution with these software installed is needed (WSL supported, too):
- [GCC](https://gcc.gnu.org/)
- [GNU Make](https://www.gnu.org/software/make/)

### Building
Clone/Download the repository.

```bash
git clone https://github.com/jackroi/virtual-machine.git
```

Enter into virtual-machine folder and run `make` command to compile the source code.

```bash
cd virtual-machine
make
```

If all went well, you should see `vm.out` file into the project directory.

## 🎈 Usage <a name="usage"></a>
The virtual machine supports 2 commands:
- run: execute a virtual machine program
- print: print the source code of a program

### Run a program
```bash
./vm.out run machine-code.cvm
```
Executes `machine-code.cvm`.

### Print a program
```bash
./vm.out print machine-code.cvm
```
Prints the source code of `machine-code.cvm`.

### Test programs
Under `test/all` folder you can find simple test programs (file `.cvm`).

## ⛏️ Built Using <a name = "built_using"></a>
- [C](https://en.wikipedia.org/wiki/C_(programming_language)) - Programming language
- [GNU Make](https://www.gnu.org/software/make/) - Compiling the project

## ✍️ Authors <a name="authors"></a>
- [@jackroi](https://github.com/jackroi) - Architecture and implementation

<!--
See also the list of [contributors](https://github.com/jackroi/virtual-machine/contributors) who participated in this project.
-->

## 🎉 Acknowledgements <a name="acknowledgement"></a>
- Laboratory professors and course tutors for the project idea and specifications.
