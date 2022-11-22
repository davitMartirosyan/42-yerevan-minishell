NAME=minishell
CC=gcc
CFLAGS= -Wall -Wextra -Werror
OBJECTS=objs/
COMPONENTS=$(wildcard env/*.c) $(wildcard errno/*.c) $(wildcard listing/*.c) $(wildcard utils/*.c)
LEXER=$(wildcard lex/*.c)
PARSER=$(wildcard parse/*.c)
BUILTINS=$(wildcard sh-builtin/*.c)

OBJ_COMPONENTS=$(patsubst $(OBJECTS)=%.o)


all: 
	@echo $(OBJ_COMPONENTS)

