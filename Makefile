NONE='\033[0m'
GREEN='\033[3;32m'
GRAY='\033[2;37m'
RED="\033[1;31m"
YELLOW="\033[1;33m"


NAME = minishell

PREFIX = $(shell find ${HOME} -name readline-dmartiro 2>/dev/null)

CC = cc -I includes/

RM = rm -rf

FLAGS =   #-fsanitize=address -g #-Wall -Wextra -Werror

MKDIR = mkdir -p

OBJS_DIR = OBJS

SRCS = $(wildcard *.c) $(wildcard env/*.c)  $(wildcard execute/*.c)  \
$(wildcard lex/*.c)  $(wildcard libft/*.c)  $(wildcard parse/*.c) $(wildcard resources/*.c ) \
$(wildcard signals/*.c) $(wildcard syntax/*.c) $(wildcard sh-builtin/*.c) $(wildcard utils/*.c)

_OBJS = $(patsubst %.c, %.o, $(SRCS))

OBJS = $(patsubst %.o, $(OBJS_DIR)/%.o, $(_OBJS))

INCLUDES = -I./readline-dmartiro/include

LINKERS	= -L./readline-dmartiro/lib -lreadline

$(OBJS_DIR)/%.o: %.c
	@ $(MKDIR) $(OBJS_DIR)/env
	@ $(MKDIR) $(OBJS_DIR)/execute
	@ $(MKDIR) $(OBJS_DIR)/lex
	@ $(MKDIR) $(OBJS_DIR)/libft
	@ $(MKDIR) $(OBJS_DIR)/signals
	@ $(MKDIR) $(OBJS_DIR)/parse
	@ $(MKDIR) $(OBJS_DIR)/resources
	@ $(MKDIR) $(OBJS_DIR)/syntax
	@ $(MKDIR) $(OBJS_DIR)/sh-builtin
	@ $(MKDIR) $(OBJS_DIR)/utils
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(NONE)$(YELLOW) "- Compiling $(NAME)..." $(NONE)
	@$(CC) $(FLAGS) $(OBJS) $(LINKERS) $(INCLUDES) -o $(NAME)
	@echo $(NONE)$(GREEN)" - Compiled  $(NAME)\n"$(NONE)

clean:
	@echo $(RED) "- Removing  object files..." $(NONE)
	@ $(RM) $(OBJS_DIR)

fclean: clean
	@echo $(RED) "- Removing  $(NAME)..." $(NONE)
	@ $(RM) $(NAME)

re: fclean all

readline:
	cd readline-master && make clean && ./configure --prefix=$(PREFIX) && make && make install

norm:
	clear
	norminette $(SRCS)

wc:
	clear
	wc -l $(SRCS)

.PHONY: all clean fclean re readline norm wc
