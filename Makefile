# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avedrenn <avedrenn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 11:36:57 by nsainton          #+#    #+#              #
#    Updated: 2023/08/07 13:04:10 by nsainton         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL:= all

MK:= mkdir -p

NAME:= minishell

#PROG:= $(NAME).c

SRCS_DIR:= sources

SRCS_SUBDIRS:= $(shell find $(SRCS_DIR) -type d)

SRCS_NAMES:= $(subst $(SRCS_DIR)/,, $(foreach dir, $(SRCS_SUBDIRS), $(wildcard $(dir)/*.c)))

SRCS:= $(addprefix $(SRCS_DIR)/, $(SRCS_NAMES))

OBJS_DIR:= objects

OBJS_NAMES:= $(SRCS_NAMES:.c=.o)

OBJS:= $(addprefix $(OBJS_DIR)/, $(OBJS_NAMES))

INCS_DIR:= includes

INCS:= $(wildcard $(INCS_DIR)/*)

DEPS_DIR:= dependencies

DEPS:= $(patsubst %.c, $(DEPS_DIR)/%.d, $(SRCS_NAMES))# $(PROG))

LIBS_DIR ?= $(addprefix $(shell pwd)/, libs)

LFT_URL := git@github.com:nsainton/libft.git

LFT_DIR:= $(addprefix $(LIBS_DIR)/, libft)

LFT_ABBR:= -lft

LFT:= $(addprefix $(LFT_DIR)/, $(LFT_NAME))

LGC_URL := git@github.com:nsainton/libgc.git

LGC_DIR:= $(addprefix $(LIBS_DIR)/, libgc)

LGC_ABBR:= -lgc

ABBRS:= $(LGC_ABBR) $(LFT_ABBR) -lreadline

CC:= cc

CFLAGS:= -Wall -Wextra -Werror

HEADER_URL := git@github.com:nsainton/42_lazy_header.git

HEADER_SCRIPT_DIR:= $(addprefix $(LIBS_DIR)/, header)

HEADER_EXEC:= lazyheader

HEADER_SCRIPT:= $(addprefix $(HEADER_SCRIPT_DIR)/, $(HEADER_EXEC))

HEADER_NAME:= $(NAME).h

FUNCS_HEADER:= $(addprefix $(INCS_DIR)/, $(HEADER_NAME))

GIT_ADD:= --all

VALGRIND_OPTIONS:= --leak-check=full --show-leak-kinds=all --suppressions=rl_suppressions.supp

export LIBS_DIR
export C_INCLUDE_PATH=$(INCS_DIR):$(LFT_DIR)/$(INCS_DIR):$(LGC_DIR)/$(INCS_DIR)
export LIBRARY_PATH=$(LFT_DIR):$(LGC_DIR)

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
#Font used is Isometric1
define minishell_header
      ___                       ___                       ___           ___           ___           ___       ___
     /\__\          ___        /\__\          ___        /\  \         /\__\         /\  \         /\__\     /\__\\
    /::|  |        /\  \      /::|  |        /\  \      /::\  \       /:/  /        /::\  \       /:/  /    /:/  /
   /:|:|  |        \:\  \    /:|:|  |        \:\  \    /:/\ \  \     /:/__/        /:/\:\  \     /:/  /    /:/  /
  /:/|:|__|__      /::\__\  /:/|:|  |__      /::\__\  _\:\~\ \  \   /::\  \ ___   /::\~\:\  \   /:/  /    /:/  /
 /:/ |::::\__\  __/:/\/__/ /:/ |:| /\__\  __/:/\/__/ /\ \:\ \ \__\ /:/\:\  /\__\ /:/\:\ \:\__\ /:/__/    /:/__/
 \/__/~~/:/  / /\/:/  /    \/__|:|/:/  / /\/:/  /    \:\ \:\ \/__/ \/__\:\/:/  / \:\~\:\ \/__/ \:\  \    \:\  \\
       /:/  /  \::/__/         |:/:/  /  \::/__/      \:\ \:\__\        \::/  /   \:\ \:\__\    \:\  \    \:\  \\
      /:/  /    \:\__\         |::/  /    \:\__\       \:\/:/  /        /:/  /     \:\ \/__/     \:\  \    \:\  \\
     /:/  /      \/__/         /:/  /      \/__/        \::/  /        /:/  /       \:\__\        \:\__\    \:\__\\
     \/__/                     \/__/                     \/__/         \/__/         \/__/         \/__/     \/__/

endef
export minishell_header

.PHONY: all

.SILENT:

all: | $(LFT_DIR) $(LGC_DIR)
	$(MAKE) -C $(LFT_DIR)
	$(MAKE) -C $(LGC_DIR)
	$(MAKE) $(NAME)

$(NAME): $(OBJS) | $(DEPS_DIR)
	$(CC) $(CFLAGS) $(GG) $(OPT) $(PROG) $(OBJS) \
	-MD -MF $(DEPS_DIR)/$(NAME).d $(ABBRS) -o $(NAME)
	echo "$(BEGIN)$(RED)m"
	echo "$$minishell_header"
	echo "$(END)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(LFT_DIR) $(LGC_DIR)
	[ -d $(@D) ] || $(MK) $(@D)
	arg="$$(dirname $(DEPS_DIR)/$*)"; \
	[ -d $$arg ] || $(MK) $$arg
	$(CC) $(CFLAGS) $(GG) $(OPT) -MD -MF $(DEPS_DIR)/$*.d -c $< -o $@

$(DEPS_DIR):
	$(MK) $(DEPS_DIR)

$(LFT_DIR):
	git clone -b rendu --single-branch --depth 1 $(LFT_URL) $@

$(LGC_DIR):
	git clone -b rendu --single-branch --depth 1 $(LGC_URL) $@

$(HEADER_SCRIPT_DIR):
	git clone $(HEADER_URL) $@

.PHONY: clean
clean:
	$(RM) -r $(OBJS_DIR)
	$(RM) -r $(DEPS_DIR)
	echo "$(BEGIN)$(RED)m$(NAME) objects and dependencies have been removed$(END)"

.PHONY: oclean
oclean:
	$(RM) $(NAME)
	echo "$(BEGIN)$(CYAN)m$(NAME) has been removed$(END)"

.PHONY: lclean
lclean:
	$(RM) -r $(LIBS_DIR)
	echo "$(BEGIN)$(PURPLE)m$(notdir $(LIBS_DIR)) have been removed$(END)"

.PHONY: fclean
fclean:
	$(MAKE) clean
	$(MAKE) oclean

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE)

.PHONY: debug
debug:
	$(MAKE) debug -C $(LFT_DIR)
	$(MAKE) debug -C $(LGC_DIR)
	$(MAKE) fclean
	$(MAKE) GG="-g3" OPT=-O0 CC=gcc

.PHONY: leaks
leaks:
	$(MAKE) debug && valgrind $(VALGRIND_OPTIONS) ./$(NAME) $(OPT_ARGS)

minitalk:
	git clone git@github.com:nsainton/minitalk.git

.PHONY: git
git:
	git add $(GIT_ADD)
	git commit
	git push

.PHONY: makedebug
makedebug:
	@echo $(DEPS)
	@echo GIT_ADD : $(GIT_ADD)
	@echo $(OPT_ARGS)

.PHONY: header

ifndef HEADER_SCRIPT
$(error HEADER_SCRIPT is not set)
endif
ifndef FUNCS_HEADER
$(error FUNCS_HEADER is not set)
endif

header: | $(HEADER_SCRIPT_DIR)
	$(MAKE) -C $(HEADER_SCRIPT_DIR)
	$(HEADER_SCRIPT) ./$(SRCS_DIR) $(FUNCS_HEADER) $(NAME)_int.h

-include $(DEPS)
