# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/12 12:05:38 by ismherna          #+#    #+#              #
#    Updated: 2024/10/12 13:19:57 by ismherna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

G = \033[1;32m
Y = \033[1;33m
R = \033[0;31m
NC = \033[0m

NAME = philosophers

# Rutas de los archivos fuente
VPATH = src/utils/:src/

# Archivos fuente
SRC = \
    src/utils/allocate.c \
    src/utils/checker_dead.c \
    src/utils/cleanup.c \
    src/utils/ft_atoi.c \
    src/utils/ft_isdigit.c \
    src/utils/ft_usleep.c \
    src/utils/get_time.c \
    src/init.c \
    src/main.c \
    src/output.c \
    src/procedure.c \
    src/protect_procedure.c \
    src/thread.c 

OBJ_DIR = objects

# Genera la lista de archivos objeto
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

# Regla para construir el objetivo final
all: $(NAME)
	@echo "															"	
	@echo "$(GREEN)██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗$(RESET)	"
	@echo "$(GREEN)██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝$(RESET)	"
	@echo "$(GREEN)██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗$(RESET)	"
	@echo "$(GREEN)██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║$(RESET)	"
	@echo "$(GREEN)██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║$(RESET)	"
	@echo "$(GREEN)╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝$(RESET)	"
	@echo "            		 2024/05/25 - ismherna@student.42.fr - 42 Madrid - Ismael Hernández						"


$(NAME): $(OBJ_DIR) $(OBJ)
	@echo "$(Y)--------------------------------------- Compiling Philosophers ---------------------------------------$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(G)----------------------------------- Philosophers Finished Compiling -----------------------------------$(NC)\n"
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(G)---------------------------------------- Philosophers Are Ready --------------------------------------$(NC)"
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)\n"

$(OBJ_DIR):
	@echo "$(R)---------------------------------- Object Directory Doesn't Exist ----------------------------------$(NC)"
	@echo "$(Y)------------------------------------ Creating Objects Directory ------------------------------------$(NC)"
	@mkdir -p $(OBJ_DIR)
	@echo "$(G)-------------------------------------- Objects Directory Done --------------------------------------$(NC)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)  # Esto garantiza que el directorio exista
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf "%-200s\r" ">Philosophers compiling: ""$(CC) $(CFLAGS) -c -o $@ $<"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(R)----------------------------------------- Objects  Cleaned -----------------------------------------$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(R)---------------------------------------- Philosophers Is Clean -------------------------------------\n$(NC)"

re: fclean all

.DEFAULT_GOAL: all

.PHONY: all clean fclean re
