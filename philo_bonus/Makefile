# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dparada <dparada@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 11:04:19 by dparada           #+#    #+#              #
#    Updated: 2024/07/30 11:54:30 by dparada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		= gcc
NAME 	= philo_bonus
USER 	= dparada
CFLAGS 	= -Wall -Wextra -Werror -g -pthread -fsanitize=thread
SRC_DIR = src/
OBJ_DIR = obj/
PHILO_H = ./$(NAME).h

MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
WHITE   = \033[37;1m
RESET   = \033[0m
GRAY 	= \033[0;90m
BLUE    = \033[34;1m
CYAN    = \033[37;1m
BOLD	= \033[1m
RED		= \033[31;1m

SRC_FILES = main \

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o,$(SRC_FILES)))

OBJF = .cache_exists

all: $(NAME)

$(NAME): compiling $(OBJ)
		@echo
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo "$(MAGENTA)Philosopher bonus compiled!$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(PHILO_H)| $(OBJF)
		@mkdir -p $(dir $@)
		@echo "$(GREEN)Compiling: $(RESET)$(notdir $<)"
		@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
		@mkdir -p $(OBJ_DIR)


compiling:
		@echo "$(YELLOW)Compiling Philosopher Bonus: $(RESET)"

clean:
		@rm -rf $(OBJ_DIR)
		@echo "$(RED)Cleaning Philosopher Bonus objects. $(RESET)"
		@echo

fclean:
		@rm -rf $(OBJ_DIR)
		@rm -rf $(NAME)
		@echo "$(RED)Cleaning Philosopher Bonus executables.$(RESET)"

re: fclean all

.PHONY: all clean fclean re compiling