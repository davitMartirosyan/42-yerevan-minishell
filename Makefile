NAME=minishell
CC=gcc
CFLAGS= -Wall -Wextra -Werror
HEADER_FLAGS= -I includes/
MINISHELL_HEADER=includes/minishell_header.h
READLINE=-lreadline
MAIN=minishell.c
LIBFT_ARCHIVE=libft.a
LIBFT=./libft/libft.a
COMPONENTS=$(wildcard env/*.c) $(wildcard errno/*.c) $(wildcard listing/*.c) $(wildcard utils/*.c)
LEXER=$(wildcard lex/*.c)
PARSER=$(wildcard parse/*.c)
BUILTINS=$(wildcard sh-builtin/*.c)

# OBJ_COMPONENTS=$(patsubst %c, %o, $(COMPONENTS))
# LEXER_COMPONENTS=$(patsubst %c, %o, $(LEXER))
# PARSER_COMPONENTS=$(patsubst %c, %o, $(PARSER))
# BUILTINS_COMPONENTS=$(patsubst %c, %o, $(BUILTINS))

OBJECTS=$(patsubst %.c, %.o, $(COMPONENTS), $(LEXER), $(PARSER), $(BUILTINS))

all: $(NAME)

$(NAME) :  $(OBJECTS) $(MINISHELL_HEADER) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) $(READLINE) $(HEADER_FLAGS) \
	$(OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT_ARCHIVE) :
	@cd ./libft && make

%.o : %.c
	@$(CC) $(CFLAGS) $(HEADER_FLAGS) -c $< -o $@