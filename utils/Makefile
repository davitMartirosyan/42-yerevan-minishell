NAME = minishell
SRC = minishell.c \
	  $(wildcard */*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
CHACHES = ~/Library/Caches

LINKS = -L $(HOME)/readline/lib -lreadline
CC = cc
FLAGS = -Wall -Werror -Wextra
INCLUDES = -I./includes -I $(HOME)/readline/include

%.o: %.c
	@$(CC) $(INCLUDES) -c $< -o $@
#	@$(CC) $(INCLUDES) -fsanitize=address -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@${CC} $(INCLUDES) ${LINKS} -o $(NAME) $(OBJ)
#	@${CC} $(INCLUDES) -fsanitize=address ${LINKS} -o $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(CHACHES)

re: fclean all

.PHONY: all clean fclean re
