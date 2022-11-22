NAME=minishell
CC=gcc
CFLAGS= -Wall -Wextra -Werror


all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) 
