# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lspiteri <lspiteri@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 14:50:49 by lspiteri          #+#    #+#              #
#    Updated: 2025/06/18 20:19:56 by lspiteri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ======================================================================= #
# 					              Makefile
# ======================================================================= #
# Compiler and Flags
CC		:= cc
CFLAGS	=	-Wall -Wextra -Werror -lpthread -I$(HEADER_DIR) \
			-g3 -O2 -fsanitize=address -fsanitize=undefined
RM		:= rm -rf
AR		:= ar rcs

# Directories
SRC_DIR   	:= srcs
HEADER_DIR	:= includes
SUBDIRS		:= 
OBJ_DIR  	:= objs

# Files
NAME	 	 	:= philo
SRC_FILES		:=	main.c \
					philo_data.c \
					philo_behaviour.c \
					utils.c \
					actions.c
					
OBJ_FILES		:= $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

# Macro to run target in all subdirs
define run_on_subdirs
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $(1) --no-print-directory \
		|| echo "> No rule '$(1)' in $$dir (ignored)"; \
	done
endef

# Main rules
all:		$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJ_FILES)
			$(call run_on_subdirs,all)
			@echo "Creating $(NAME)\n"
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)

# Compilation of source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
			@mkdir -p $(dir $@)
			@echo "Compiling $<"
			@$(CC) $(CFLAGS) -c $< -o $@

# Creating necessary directories
$(OBJ_DIR):
			@echo "Creating object directory $(OBJ_DIR)"
			@mkdir -p $(OBJ_DIR)

# Clean rules
clean:
			$(RM) $(OBJ_DIR)
			$(call run_on_subdirs,clean)

fclean:		
			$(RM) $(OBJ_DIR)
			$(RM) $(NAME)
			$(call run_on_subdirs,fclean)

re:			fclean all

# Phony targets
.PHONY:		all clean fclean re
