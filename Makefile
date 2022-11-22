NAME=minishell
CC=gcc
CFLAGS= -Wall -Wextra -Werror

<<<<<<< HEAD

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) 
=======
LINKS = -lreadline
CC = cc
FLAGS = -Wall -Werror -Wextra
INCLUDES = -I./includes

%.o: %.c
	@$(CC) $(INCLUDES) -fsanitize=address -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@${CC} $(INCLUDES) -fsanitize=address ${LINKS} -o $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(CHACHES)

re: fclean all


.PHONY: all clean fclean re

>>>>>>> 7325c1f35339612c6dc4e302bd1f51c1b89138d2
