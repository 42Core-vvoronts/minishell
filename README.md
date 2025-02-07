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
git clone https://github.com/vicxptrv/42Core/Minishell.git
cd Minishell
make
```

## Usage

Compile the shell:
```sh
make
```

Run the shell:
```sh
./Minishell
```

Run statement:
```sh
<< EOF cat | ls $VAR1 / >> file2.txt | echo $ENV2 | cat | cat
```
Run statement:
```sh
( < f2 ls / | cat | grep a && ls ) > f1
```

Result:
![alt text](wiki/target_tree_v1.png)

## License

This project is licensed under the MIT License.