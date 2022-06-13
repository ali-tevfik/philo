# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: adoner <adoner@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/01 13:16:02 by adoner        #+#    #+#                  #
#    Updated: 2022/06/13 17:35:46 by adoner        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN = \033[38;5;2m
NORMAL = \033[38;5;255m
RED = \033[38;5;1m
BLUE = \033[38;5;4m
YELLOW = \033[1;33m

# Compiler settings
GCC = gcc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
# FLAGS   = -Wall -Wextra -Werror -pthread
DBG_FLAGS = -g -fsanitize=address

# Source, tests, header and object files
SRC_FILES = philo.c \
			utils.c \
			init_data.c \
			routine.c \
			check_data.c \
			died.c

HEADER_FILES = 	philo.h

OBJ_DIR = obj
OBJ = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)


# Program name
NAME = philo

# Build release
all: $(OBJ_DIR) $(NAME)

# Build normal
$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(OBJ)
	$(GCC) $(FLAGS) $^ -o $@
	@echo "$(GREEN) Created minishell executable.$(NORMAL)"

$(OBJ): $(OBJ_DIR)/%.o : %.c $(HEADER_FILES)
	@mkdir -p $(@D)
	@$(GCC) $(FLAGS) -c $< -o $@

clean:
	@rm -rdf $(OBJ_DIR)
	@echo "$(RED) Deleted all object files.$(NORMAL)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED) Deleted all executables.$(NORMAL)"

re: clean fclean all

.PHONY: clean fclean re
