
# Minishell-$
## The story of little shell



![Logo](https://repository-images.githubusercontent.com/237800104/dfc69080-46fb-11eb-9413-0f02ce8f5532)


## Authors

- [@sabazyan](https://github.com/sabazyan)
- [@davitmartirosyan](https://github.com/davitmartirosyan)


# Introduction
This project is all about recreating your very own bash [Bourne Again Shell](https://en.wikipedia.org/wiki/Bash_(Unix_shell)).

I was honored to do this project with [Sirush Abazyan](https://github.com/sabazyan).

### What is the shell?

Likewise, the shell we are implementing works as a command interpreter communicating with the OS kernel in a secure way, and allows us to perform a number tasks from a command line, namely execute commands, create or delete files or directories, or read and write content of files, among (many) other things

### Implementation of Minishell
The general idea for this shell is reading a string of commands in a prompt using readline. 
Before anything, it is highly recommended to take a deep dive into the [bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)), as it goes over every detail we had to have in mind when doing this project. 
Minishell involves heavy parsing of the string read by readline, 
thus it is crucial to divide the code of the project into different parts: `lexer`, `parser`, lastly the `executor`

[**Lexer**](https://en.wikipedia.org/wiki/Lexical_analysis) -  lexical analysis, lexing or tokenization is the process of converting a sequence of characters.

[**Parser**](https://en.wikipedia.org/wiki/Parsing) - The parser is in charge of storing the tokenized string and save it in a useful manner for the executor to use later. Our data structure is managed as follows.

[**Executer**](https://www.cs.uleth.ca/~holzmann/C/system/shell_commands.html) - With all our data properly on our structs, the executer has all the necessary information to execute commands. For this part we use separate processess to execute either our builtins or other commands inside child processes that redirect **`stdin`** and **`stdout`**.
## 🛠 Skills
C, C++, Rigor Thinking, Algorithms

