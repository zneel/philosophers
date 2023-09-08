<div align="center">
<h1 align="center">
<img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" width="100" />
<br>philosophers
</h1>
<h3>◦ Connecting minds. Unleashing ideas.</h3>
<h3>◦ Developed with the software and tools listed below.</h3>

<p align="center">
<img src="https://img.shields.io/badge/C-A8B9CC.svg?style&logo=C&logoColor=black" alt="C" />
</p>
<img src="https://img.shields.io/github/languages/top/zneel/philosophers?style&color=5D6D7E" alt="GitHub top language" />
<img src="https://img.shields.io/github/languages/code-size/zneel/philosophers?style&color=5D6D7E" alt="GitHub code size in bytes" />
<img src="https://img.shields.io/github/commit-activity/m/zneel/philosophers?style&color=5D6D7E" alt="GitHub commit activity" />
<img src="https://img.shields.io/github/license/zneel/philosophers?style&color=5D6D7E" alt="GitHub license" />
</div>

---

## 📒 Table of Contents
- [📒 Table of Contents](#-table-of-contents)
- [📍 Overview](#-overview)
- [⚙️ Features](#-features)
- [📂 Project Structure](#project-structure)
- [🧩 Modules](#modules)
- [🚀 Getting Started](#-getting-started)
- [🗺 Roadmap](#-roadmap)
- [🤝 Contributing](#-contributing)
- [📄 License](#-license)
- [👏 Acknowledgments](#-acknowledgments)

---


## 📍 Overview

This project is a program that simulates the "dining philosophers" problem. It allows for the control of philosopher behavior and their interactions with forks, as well as time management. The code provides functionalities such as initialization of the simulation, allocating memory for philosophers and forks, executing the simulation, and checking for cases like deadlocks or if philosophers have eaten enough. The project's value proposition lies in its ability to provide a realistic simulation of the dining philosophers problem and evaluate different strategies to address it.

---

## ⚙️ Features

| Feature                | Description                           |
| ---------------------- | ------------------------------------- |
| **⚙️ Architecture**     | The codebase follows a multithreaded design using the POSIX threads (pthreads) library. Each philosopher is represented as a thread, and the interactions and synchronization between philosophers are accomplished using mutex locks for fork access. |
| **📖 Documentation**   | The codebase is well-documented with detailed explanations of each file, function, and data structure. The documentation clarifies the purpose and functionality of different components. |
| **🔗 Dependencies**    | The codebase relies on the external library "libft" for additional functionalities. This library is not included in the repository and needs to be separately obtained and compiled. |
| **🧩 Modularity**      | The codebase is organized into separate files that define specific components of the program, such as philosophers, forks, time management, utilities, actions, and the main module. Each file has a clear purpose and consolidates related functions and data structures. |
| **✔️ Testing**          | The codebase lacks explicit testing mechanisms. However, the structure of the code, the separation of concerns, and the usage of mutex locks indicate a potential for unit testing of individual components. |
| **⚡️ Performance**      | The emphasis of the codebase is on simulation rather than performance optimization. Resource usage may not be highly optimized due to the workload of managing multiple threads. |
| **🔐 Security**        | The codebase does not deal with sensitive data, and there are no specific security measures implemented. However, careful use of mutex locks ensures thread safety and prevents race conditions. |
| **🔀 Version Control** | The codebase is version controlled using Git. The repository provides a detailed history of commits, allowing for easy tracking of changes and collaboration among developers. |
| **🔌 Integrations**    | The codebase does not include explicit integrations with other systems or services. However, it can be integrated into larger applications as a module for simulating the dining philosopher problem. |
| **📶 Scalability**     | The codebase is designed to handle scalability by representing each philosopher as a separate thread. Adding or removing philosophers can be easily achieved by extending or reducing the size of data structures and launching or terminating threads accordingly.

---


## 📂 Project Structure




---

## 🧩 Modules

<details closed><summary>Philo</summary>

| File                                                                       | Summary                                                                                                                                                                                                                                                                                                                                                                    |
| ---                                                                        | ---                                                                                                                                                                                                                                                                                                                                                                        |
| [Makefile](https://github.com/zneel/philosophers/blob/main/philo/Makefile) | This code is a program that simulates the "dining philosophers" problem. It includes functionalities to control the behavior of the philosophers and their interactions with forks, as well as time management and various utility functions. The code can be compiled with additional flags for debugging and sanitizing. It depends on a separate library called "libft. |

</details>

<details closed><summary>Src</summary>

| File                                                                                       | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| ---                                                                                        | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| [philosophers.c](https://github.com/zneel/philosophers/blob/main/philo/src/philosophers.c) | The code creates a simulation of philosophers dining at a table. It initializes and assigns properties to philosophers, allocates memory, starts threads for each philosopher's routine, and checks for cases such as deadlocks or if they have eaten enough.                                                                                                                                                                                                                                           |
| [time.c](https://github.com/zneel/philosophers/blob/main/philo/src/time.c)                 | This code provides functionality for measuring, calculating, and managing time-related operations. It includes functions to convert time to milliseconds, get the current time, calculate the time difference, and induce a delay in milliseconds.                                                                                                                                                                                                                                                      |
| [helpers.c](https://github.com/zneel/philosophers/blob/main/philo/src/helpers.c)           | The code includes a function called print_usage() that prints out a specific usage message for a program called "./philo". It takes in five arguments and displays them as part of the message.                                                                                                                                                                                                                                                                                                         |
| [checker.c](https://github.com/zneel/philosophers/blob/main/philo/src/checker.c)           | The "checker.c" code contains the core functionalities of the checker thread in a philosopher simulation program. It includes functions to check if a philosopher is dead, if a particular philosopher has reached the desired number of meals, and if all philosophers have reached the desired number of meals. It also includes a function to periodically check for dead philosophers and end the simulation if necessary. The code is multi-threaded and uses mutex locks to ensure thread safety. |
| [utils.c](https://github.com/zneel/philosophers/blob/main/philo/src/utils.c)               | The code in utils.c includes utility functions for the "philo" program.-ft_swap(): Swaps two integers.-print_dead(): Prints the time of death for a philosopher.-sim_print(): Prints the current action of a philosopher if the simulation is not over.-sim_end(): Checks if the simulation has ended.                                                                                                                                                                                                  |
| [actions.c](https://github.com/zneel/philosophers/blob/main/philo/src/actions.c)           | This code defines three core actions for the philosopher simulation. The p_eat() function handles the logic for a philosopher to eat by acquiring two forks, updating their stats, and releasing the forks. The p_think() function prints a message indicating the philosopher is thinking. The p_sleep() function prints a message indicating the philosopher is sleeping for a specified duration.                                                                                                    |
| [main.c](https://github.com/zneel/philosophers/blob/main/philo/src/main.c)                 | This code parses command line arguments, initializes a simulation, and runs it based on the given parameters. It also performs basic validation of the arguments and implements error handling.                                                                                                                                                                                                                                                                                                         |
| [simulation.c](https://github.com/zneel/philosophers/blob/main/philo/src/simulation.c)     | The code is for a simulation of a dining philosopher problem. It initializes the simulation, allocates memory for philosophers and forks, initializes forks and philosophers, executes the simulation, and finally, destroys the simulation. It also waits for all the threads to finish before destroying the simulation.                                                                                                                                                                              |
| [routine.c](https://github.com/zneel/philosophers/blob/main/philo/src/routine.c)           | The code is part of a simulation program for a dining philosophers problem. It includes functions to check if a philosopher has eaten enough, check if the simulation should stop, and the routine function for each philosopher's thread. The routine function simulates the actions of a philosopher, such as eating, sleeping, and thinking, based on certain conditions.                                                                                                                            |
| [forks.c](https://github.com/zneel/philosophers/blob/main/philo/src/forks.c)               | The code initializes and allocates mutex locks for forks in a dining philosophers simulation. It also includes functions to initialize and destroy the mutex locks.                                                                                                                                                                                                                                                                                                                                     |

</details>

<details closed><summary>Include</summary>

| File                                                                             | Summary                                                                                                                                                                                                                                                                                                                                |
| ---                                                                              | ---                                                                                                                                                                                                                                                                                                                                    |
| [philo.h](https://github.com/zneel/philosophers/blob/main/philo/include/philo.h) | The code consists of a simulation of a dining philosophers problem with multiple functions and structs. It handles the allocation and initialization of philosophers and forks, simulation control, printing, time calculations, and the main thread for checking if philosophers have finished eating their required number of times. |

</details>

---

## 🚀 Getting Started

### ✔️ Prerequisites

Before you begin, ensure that you have the following prerequisites installed:
> - `ℹ️ Requirement 1`
> - `ℹ️ Requirement 2`
> - `ℹ️ ...`

### 📦 Installation

1. Clone the philosophers repository:
```sh
git clone https://github.com/zneel/philosophers
```

2. Change to the project directory:
```sh
cd philosophers
```

3. Install the dependencies:
```sh
gcc -o myapp main.c
```

### 🎮 Using philosophers

```sh
./myapp
```

### 🧪 Running Tests
```sh
/* No common unit test framework in C */
```

---


## 🗺 Roadmap

> - [X] `ℹ️  Task 1: Implement X`
> - [ ] `ℹ️  Task 2: Refactor Y`
> - [ ] `ℹ️ ...`


---

## 🤝 Contributing

Contributions are always welcome! Please follow these steps:
1. Fork the project repository. This creates a copy of the project on your account that you can modify without affecting the original project.
2. Clone the forked repository to your local machine using a Git client like Git or GitHub Desktop.
3. Create a new branch with a descriptive name (e.g., `new-feature-branch` or `bugfix-issue-123`).
```sh
git checkout -b new-feature-branch
```
4. Make changes to the project's codebase.
5. Commit your changes to your local branch with a clear commit message that explains the changes you've made.
```sh
git commit -m 'Implemented new feature.'
```
6. Push your changes to your forked repository on GitHub using the following command
```sh
git push origin new-feature-branch
```
7. Create a new pull request to the original project repository. In the pull request, describe the changes you've made and why they're necessary.
The project maintainers will review your changes and provide feedback or merge them into the main branch.

---

## 📄 License

This project is licensed under the `ℹ️  INSERT-LICENSE-TYPE` License. See the [LICENSE](https://docs.github.com/en/communities/setting-up-your-project-for-healthy-contributions/adding-a-license-to-a-repository) file for additional info.

---

## 👏 Acknowledgments

> - `ℹ️  List any resources, contributors, inspiration, etc.`

---
