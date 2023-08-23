# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 06:01:21 by nsainton          #+#    #+#              #
#    Updated: 2023/08/07 20:38:54 by nsainton         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS_DIR = sources

SRCS_NAMES= address.c allocation.c ascii1.c ascii2.c atoi_errors.c atoi_until.c \
			base.c colors_print.c count_equal.c decimal.c flush.c ft_atoi.c \
			ft_bzero.c ft_itoa.c ft_printf.c ft_split.c ft_sprintf.c \
			ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
			ft_strlcpy.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_strtrim.c ft_substr.c get_next_line.c helpers.c \
			hexadecimal.c init.c length.c lst_access.c lst_addelem.c \
			lst_delelem.c lst_functions.c memfuncs.c minimum.c parsing.c \
			pbuffer.c percent.c print_fd.c printing.c putnbr_tab.c strfuncs.c \
			strings.c strtoll_errors.c tstr_add.c tstr_alloc.c tstr_del.c \
			tstr_init.c tstr_print.c

SHELL = /bin/sh #To avoid troubles on system where SHELL variable is inherited
				#From the environment

.SUFFIXES: #To clear the suffix list
.SUFFIXES: .c .o .a #To specify only the suffixes we need in this particular Makefile

SRCS_NAMES = $(subst $(SRCS_DIR)/,, $(wildcard $(SRCS_DIR)/*))

SRCS = $(addprefix $(SRCS_DIR)/,$(SRCS_NAMES))

OBJS_NAMES = $(SRCS_NAMES:.c=.o)

STABLE_OBJS_DIR = objects

DEBUG_OBJS_DIR = objects_debug

STABLE_OBJS = $(addprefix $(STABLE_OBJS_DIR)/, $(OBJS_NAMES))

DEBUG_OBJS = $(addprefix $(DEBUG_OBJS_DIR)/, $(OBJS_NAMES))

OBJS := $(STABLE_OBJS)

INC_DIR = includes

INC_NAMES= ansicolorcodes.h libft.h libft_int.h

INC_PATHS := $(addprefix $(INC_DIR)/, $(INC_NAMES))

CC = cc

CFLAGS = -Wall -Wextra -Werror

AR = ar -rc

LIBS := libs

LIBS_DIR ?= $(shell pwd)/libs

export LIBS_DIR
export C_INCLUDE_PATH=$(INC_DIR)

#Color codes for pretty printing
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

#Here is the definition of an ascii code
#double backslash at the end of lines to ensure that it is not interpreted
#as line continuation. One could also have added a space after the backslash
#The export directive makes the header available to each submake
#Font used is Sub-Zero
define libft_header
    __         __     ______     ______   ______  
   /\ \       /\ \   /\  == \   /\  ___\ /\__  _\\
   \ \ \____  \ \ \  \ \  __<   \ \  __\ \/_/\ \/ 
    \ \_____\  \ \_\  \ \_____\  \ \_\      \ \_\\
     \/_____/   \/_/   \/_____/   \/_/       \/_/ 
endef
export libft_header

define compiled_header
  ______  ______  __    __  ______  __  __      ______  _____    
 /\  ___\/\  __ \/\ "-./  \/\  == \/\ \/\ \    /\  ___\/\  __-.  
 \ \ \___\ \ \/\ \ \ \-./\ \ \  _-/\ \ \ \ \___\ \  __\\ \ \/\ \ 
  \ \_____\ \_____\ \_\ \ \_\ \_\   \ \_\ \_____\ \_____\ \____- 
   \/_____/\/_____/\/_/  \/_/\/_/    \/_/\/_____/\/_____/\/____/ 
endef
export compiled_header

.DEFAULT_GOAL := stable

all : stable

$(NAME) : $(OBJS)
	$(AR) $(NAME) $(OBJS)
	echo "$(BEGIN)$(GREEN)m"
	echo "$$libft_header"
	echo "$$compiled_header"
	echo "$(END)"

$(STABLE_OBJS_DIR)/%.o : $(SRCS_DIR)/%.c $(INC_PATHS) | $(STABLE_OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(DEBUG_OBJS_DIR)/%.o : $(SRCS_DIR)/%.c $(INC_PATHS) | $(DEBUG_OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(STABLE_OBJS_DIR) :
	mkdir -p $(STABLE_OBJS_DIR)

$(DEBUG_OBJS_DIR) :
	mkdir -p $(DEBUG_OBJS_DIR)

stable : OBJS = $(STABLE_OBJS)
stable : $(STABLE_OBJS) $(NAME)

debug : OBJS := $(DEBUG_OBJS)
debug : CFLAGS += -g3 -O0
debug : CC := gcc
debug : $(DEBUG_OBJS) $(NAME)

clean :
	rm -rf $(STABLE_OBJS_DIR)
	rm -rf $(DEBUG_OBJS_DIR)
	echo "$(BEGIN)$(RED)mObjects have been successfully removed$(END)"

oclean :
	rm -f $(NAME)
	echo "$(BEGIN)$(RED);$(UNDERLINED)m$(NAME)\
	$(BEGIN)$(NORMAL);$(CYAN)m has been successfully removed$(END)"

fclean : clean oclean

re : fclean all

git :
	git add --all
	git commit
	git push origin dev

maketest :
	echo $(LIBS_DIR)

getsrcs:
	echo $(SRCS_NAMES)
	echo $(wildcard $(INC_DIR)/*.h)

.PHONY : all stable debug clean fclean re git
.SILENT :
