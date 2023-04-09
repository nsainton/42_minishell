# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 21:53:38 by nsainton          #+#    #+#              #
#    Updated: 2023/01/15 01:15:46 by nsainton         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= Minitalk

SERVER= server

S_PROG= $(SERVER).c

CLIENT= client

C_PROG= $(CLIENT).c

LIBFT_DIR= ../Libft

LIBFT_NAME= libft.a

LIBFT_PATH= $(LIBFT_DIR)/$(LIBFT_NAME)

LIBFT_ABBR= -lft

INC_DIR= includes

SRCS_DIR= sources

SRCS_NAMES= $(notdir $(wildcard $(SRCS_DIR)/*))

SRCS= $(addprefix $(SRCS_DIR)/, $(SRCS_NAMES))

OBJS_DIR= objects

OBJS_NAMES= $(SRCS_NAMES:.c=.o)

OBJS= $(addprefix $(OBJS_DIR)/, $(OBJS_NAMES))

CFLAGS= -Wall -Wextra -Werror

CC= cc

export C_INCLUDE_PATH=$(INC_DIR):$(LIBFT_DIR)/$(INC_DIR)
export LIBRARY_PATH=$(LIBFT_DIR)

all:
	$(MAKE) $(NAME)

$(NAME):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) $(SERVER)
	$(MAKE) $(CLIENT)

$(SERVER): $(S_PROG) $(OBJS) $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(GG) $(OPT) $(OBJS) $(S_PROG) $(LIBFT_ABBR) -o $(SERVER)
	@echo "$(BEGIN)$(BOLD);$(RED)m $$server_header $(END)"

$(CLIENT): $(C_PROG) $(OBJS) $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(GG) $(OPT) $(OBJS) $(CLIENT).c $(LIBFT_ABBR) -o $(CLIENT)
	@echo "$(BEGIN)$(BOLD);$(CYAN)m $$client_header $(END)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(wildcard $(INC_DIR)/*) $(LIBFT) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(GG) $(OPT) -c $< $(LIBFT) -o $@

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

debug:
	$(MAKE) fclean
	$(MAKE) GG=-g3 OPT=-O0

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJS_DIR)
	echo "$(BEGIN)$(RED)mObjects have been successfully removed$(END)"

oclean:
	rm -f $(CLIENT) $(SERVER)
	echo "$(BEGIN)$(UNDERLINED);$(RED)m$(SERVER)$(BEGIN)$(NORMAL);$(CYAN)m and \
	$(BEGIN)$(UNDERLINED);$(RED)m$(CLIENT)$(BEGIN)$(NORMAL);$(CYAN)m have been \
	successfully removed$(END)"

fclean: clean
	$(MAKE) oclean -C $(LIBFT_DIR)
	$(MAKE) oclean

rendu:
	norminette $(SRCS_DIR) $(INC_DIR) $(C_PROG) $(S_PROG) && echo "$(BEGIN);$(GREEN)Norminette is good$(END)" || echo\
	"$(BEGIN);$(RED)Can't continue, Norminette is bad\n" && exit(1)
	echo "Don't forget to watch out for wildcards"
	echo "If everything is right, good luck for the push"
	$(MAKE) debug

re: fclean all

git:
	git add --all
	git commit
	git push

.PHONY: $(NAME) debug clean fclean re git
.SILENT:

#Ansi color codes
BEGIN=\033[
BLACK=30
RED=31
GREEN=32
BROWN=33
BLUE=34
PURPLE=35
CYAN=36
NORMAL=0
BOLD=1
UNDERLINED=4
BLINKING=5
REVERSE=7
END=\033[0m

#Font is Modular
define server_header
 ______    _______  _______  ______   __   __    _______  _______    ___      ___   _______  _______  _______  __    _ 
|    _ |  |       ||   _   ||      | |  | |  |  |       ||       |  |   |    |   | |       ||       ||       ||  |  | |
|   | ||  |    ___||  |_|  ||  _    ||  |_|  |  |_     _||   _   |  |   |    |   | |  _____||_     _||    ___||   |_| |
|   |_||_ |   |___ |       || | |   ||       |    |   |  |  | |  |  |   |    |   | | |_____   |   |  |   |___ |       |
|    __  ||    ___||       || |_|   ||_     _|    |   |  |  |_|  |  |   |___ |   | |_____  |  |   |  |    ___||  _    |
|   |  | ||   |___ |   _   ||       |  |   |      |   |  |       |  |       ||   |  _____| |  |   |  |   |___ | | |   |
|___|  |_||_______||__| |__||______|   |___|      |___|  |_______|  |_______||___| |_______|  |___|  |_______||_|  |__|
endef
export server_header

#Font is Big
define client_header
  _____                _         _          _        _ _    
 |  __ \              | |       | |        | |      | | |   
 | |__) |___  __ _  __| |_   _  | |_ ___   | |_ __ _| | | __
 |  _  // _ \/ _` |/ _` | | | | | __/ _ \  | __/ _` | | |/ /
 | | \ \  __/ (_| | (_| | |_| | | || (_) | | || (_| | |   < 
 |_|  \_\___|\__,_|\__,_|\__, |  \__\___/   \__\__,_|_|_|\_\ 
                          __/ |                             
                         |___/                              
endef
export client_header
