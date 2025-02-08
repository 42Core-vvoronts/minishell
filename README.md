# Minishell

Minishell is a minimalistic shell implementation for Unix-based systems.

## Features

- Basic command execution
- Input/output redirection
- Pipe handling
- Environment variable management

## Installation

Clone the repository and compile the source code:

```sh
git clone https://github.com/vicxptrv/42Core/minishell.git
cd minishell
make
```

## Usage

Compile the shell:
```sh
make
```

Run the shell:
```sh
./minishell
```

Run statement:
```sh
( < f2 ls / | cat | grep a && ls ) > f1
```

Target tree:
![alt text](wiki/target_tree_v1.png)

Result tree:
![alt text](wiki/result_tree_v1.png)

## License

This project is licensed under the MIT License.