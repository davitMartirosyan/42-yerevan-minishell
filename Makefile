NAME=minishell
CC=gcc
CFLAGS= -Wall -Wextra -Werror
HEADER_FLAGS= -I includes/
MINISHELL_HEADER=includes/minishell_header.h
READLINE=-lreadline
LIBFT_ARCHIVE=libft.a
LIBFT=./libft/libft.a
MINI=./minishell.c
COMPONENTS=$(wildcard env/*.c) $(wildcard errno/*.c) $(wildcard listing/*.c) $(wildcard utils/*.c)
LEXER=$(wildcard lex/*.c)
PARSER=$(wildcard parse/*.c)
BUILTINS=$(wildcard sh-builtin/*.c)

# OBJ_COMPONENTS=$(patsubst %c, %o, $(COMPONENTS))
# LEXER_COMPONENTS=$(patsubst %c, %o, $(LEXER))
# PARSER_COMPONENTS=$(patsubst %c, %o, $(PARSER))
# BUILTINS_COMPONENTS=$(patsubst %c, %o, $(BUILTINS))

OBJECTS=$(patsubst %.c, %.o, $(COMPONENTS), $(LEXER), $(PARSER), $(BUILTINS), $(MINI))

all: 
	gcc -I includes/ */*.c minishell.c -lreadline -o minishell

re:
	cd libft/ && make re
	cd ../
	gcc -I includes/ */*.c minishell.c -lreadline -o minishell
# $(NAME) : $(OBJECTS)
# 	$(CC) $(LIBFT) $(OBJECTS) -o $(NAME)

# $(OBJECTS) : $(COMPONENTS) $(LEXER) $(PARSER) $(BUILTINS)
# 	$(CC) $(CFLAGS) $(HEADER_FLAGS) $< -o $@


# gcc -Wall -Wextra -Werror -I includes/ */*.c -lreadline -o */*.o 