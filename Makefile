
#==========COLOURS=============================================================#

# Basic Colors

BLACK       = \033[0;30m
RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
MAGENTA     = \033[0;35m
CYAN        = \033[0;36m
WHITE       = \033[0;37m

# Bright Colors

BOLD_BLACK  = \033[1;30m
BOLD_RED    = \033[1;31m
BOLD_GREEN  = \033[1;32m
BOLD_YELLOW = \033[1;33m
BOLD_BLUE   = \033[1;34m
BOLD_MAGENTA= \033[1;35m
BOLD_CYAN   = \033[1;36m
BOLD_WHITE  = \033[1;37m

# Extended Colors (256 colors)
ORANGE      = \033[38;5;208m
WINE        = \033[38;5;88m
LIME        = \033[38;5;190m
TURQUOISE   = \033[38;5;38m
LIGHT_PINK  = \033[38;5;13m
DARK_GRAY   = \033[38;5;235m
LIGHT_RED   = \033[38;5;203m
LIGHT_BLUE  = \033[38;5;75m

BRIGHT_BLUE = \033[38;5;27m
BRIGHT_GREEN= \033[38;5;46m
BRIGHT_YELLOW=\033[38;5;226m
BRIGHT_CYAN = \033[38;5;51m
BRIGHT_WHITE= \033[38;5;231m

# Reseteo de color
NO_COLOR    = \033[0m
DEF_COLOR   = \033[0;39m
CLEAR_LINE  = \033[2K
MOVE_UP     = \033[1A


#==========DIRECTORIES=======================================================#

INC 			:= inc/
SRC_DIR 		:= src/
OBJ_DIR 		:= obj/

PHILO_DIR		:= $(SRC_DIR)philo/
PHILO_BONUS_DIR	:= $(SRC_DIR)philo_bonus/

#==========NAMES===============================================================#

NAME		:= philo
BONUS_NAME	:= philo_bonus

#==========COMMANDS============================================================#

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -g3 -fsanitize=undefined -pthread
RM			:= rm -rf
AR			:= ar rcs
LIB			:= ranlib
MKDIR 		:= mkdir -p
IFLAGS		:= -I$(INC)

#==========RULES==============================================================#

all: $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME):
	$(MAKE) -sC $(PHILO_BONUS_DIR)
	cp $(PHILO_BONUS_DIR)$(BONUS_NAME) .

$(NAME):
	$(MAKE) -sC $(PHILO_DIR)
	cp $(PHILO_DIR)$(NAME) .

clean:
	$(MAKE) clean -sC $(PHILO_DIR)
	$(MAKE) clean -sC $(PHILO_BONUS_DIR)
	@echo "$(CYAN)[$(NAME)]:\tobject files $(GREEN) => Cleaned!$(DEF_COLOR)"

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)
	$(MAKE) fclean -sC $(PHILO_DIR)
	$(MAKE) fclean -sC $(PHILO_BONUS_DIR)
	$(RM) $(OBJ_DIR)
	@echo "$(CYAN)[$(NAME)]:\texec. files $(GREEN) => Cleaned!$(DEF_COLOR)"
	

re: fclean all

-include $(DEPS) $(DEPS_BONUS)

.SILENT: all clean fclean
.PHONY: all clean fclean re bonus
