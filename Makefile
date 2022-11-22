NAME=minishell
CC=gcc
CFLAGS= -Wall -Wextra -Werror
OBJECTS=obj/
SRC=$(wildcard */*.c)

all: 
	@echo $(SRC)

