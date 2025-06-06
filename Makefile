# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: halnuma <halnuma@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 23:20:17 by val               #+#    #+#              #
#    Updated: 2025/06/06 10:51:03 by halnuma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	ANSI COLORS
BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m

BG_BLACK = \033[40m
BG_RED = \033[41m
BG_GREEN = \033[42m
BG_YELLOW = \033[43m
BG_BLUE = \033[44m
BG_MAGENTA = \033[45m
BG_CYAN = \033[46m
BG_WHITE = \033[47m

BOLD = \033[1m
DIM = \033[2m
ITALIC = \033[3m
UNDERLINE = \033[4m
BLINK = \033[5m
REVERSE = \033[7m
HIDDEN = \033[8m
RESET = \033[0m

# Verbose control
VERBOSE = 0
ifeq ($(VERBOSE),1)
	SILENT =
	DUMP_OUT =
else
	SILENT = @
	DUMP_OUT = > /dev/null 2>&1
endif

# Project
NAME = cub3d
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBS_DIR = libs

# Source files
SRC_FILES = \
	main.c \
	init_game.c \
	end_game.c \
	keys_buffer.c \
	keys_handlers.c \
	map_utils.c \
	time_utils.c \
	parsing.c \
	minimap.c \
	tiles_testing.c

HEADERS = \
	cub3d.h

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libs
LIBS_DIRS := $(shell find $(LIBS_DIR) -maxdepth 1 -mindepth 1 -type d)
LIBS = $(foreach dir, $(LIBS_DIRS), $(dir)/$(shell basename $(dir) | sed 's/^lib//g' | sed 's/^/lib/').a)
LIBS_NO_LIB = $(foreach dir, $(LIBS_DIRS), $(patsubst lib%, %, $(notdir $(dir))))

# Compiler & flags
CC = cc
CFLAGS = -Werror -Wextra -Wall
INC_FLAGS = -I$(INC_DIR) $(addprefix -I,$(LIBS_DIRS))
LDFLAGS = $(addprefix -L,$(LIBS_DIRS)) $(addprefix -l,$(LIBS_NO_LIB)) -lmlx -lXext -lX11 -lm -lbsd

# Targets
.PHONY: all clean fclean re fcleanlibs

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(SILENT) $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "$(BG_GREEN)>>> Program $(NAME) compiled!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	$(SILENT) mkdir -p $(dir $@)
	@echo "$(BLUE)>>> Compiling $<...$(RESET)"
	$(SILENT) $(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(LIBS): %.a:
	$(SILENT) \
	if [ -f "$(@D)/configure" ]; then \
		echo "$(CYAN)>>> Found configure in $(notdir $(@D)), running it...$(RESET)"; \
		cd "$(@D)" && ./configure $(DUMP_OUT); \
		if [ $$? -ne 0 ]; then \
			echo "$(RED)>>> ./configure failed in $(notdir $(@D)) – aborting.$(RESET)"; \
			exit 1; \
		else \
			exit 0; \
		fi; \
	fi; \
	echo "$(MAGENTA)>>> Compiling library $(notdir $@)...$(RESET)"; \
	$(MAKE) -C $(dir $@) > /dev/null 2> make_errors.log || { \
		echo "$(RED)>>> Error compiling $(notdir $@):$(RESET)"; \
		cat make_errors.log; rm -f make_errors.log; exit 1; }; \
	rm -f make_errors.log; \
	if $(MAKE) -C $(dir $@) -n bonus $(DUMP_OUT); then \
		echo "$(DIM)$(MAGENTA)>>> Bonus rule exists, compiling...$(RESET)"; \
		$(MAKE) -C $(dir $@) bonus > /dev/null 2> make_errors.log || { \
			echo "$(RED)>>> Error compiling bonus for $(notdir $@):$(RESET)"; \
			cat make_errors.log; rm -f make_errors.log; exit 1; }; \
		rm -f make_errors.log; \
	fi; \
	echo "$(BG_BLUE)$(GREEN)>>> Compilation of $(notdir $@) completed!$(RESET)"

clean:
	@echo "$(YELLOW)>>> Cleaning objects$(RESET)"
	$(SILENT) rm -rf $(OBJ_DIR)

fcleanlibs:
	$(SILENT) for dir in $(LIBS_DIRS); do \
		$(MAKE) -C $$dir clean $(DUMP_OUT); \
		$(MAKE) -C $$dir fclean $(DUMP_OUT); \
		echo "$(GREEN)>>> Cleaned all in $$dir$(RESET)"; \
	done

fclean: clean fcleanlibs
	@echo "$(YELLOW)>>> Cleaning executable...$(RESET)"
	$(SILENT) rm -f $(NAME)

re: fclean all
