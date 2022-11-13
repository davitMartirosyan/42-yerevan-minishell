NAME = minishell
SRC = minishell.c \
	  $(wildcard */*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
CHACHES = ~/Library/Caches

LINKS = -lreadline
CC = cc
FLAGS = -Wall -Werror -Wextra

%.o: %.c
	@$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@${CC} -I includes/ ${LINKS} -o $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(CHACHES)

re: fclean all 

.PHONY: all clean fclean re
