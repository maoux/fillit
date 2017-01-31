#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agermain <agermain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/05 01:56:18 by agermain          #+#    #+#              #
#    Updated: 2017/01/31 17:48:34 by agermain         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

#Compiler options#
CC=gcc
CFLAGS=-Werror -Wall -Wextra
LIBS=libft/libft.a
NAME=fillit
#MODE=LIB
MODE=EXEC
MAIN_FILE=main.c

#paths#
SRC_PREFIX=
OBJ_PREFIX=obj
INCLUDES=.
SUB_MAKEABLE=./libft/

#code#
SRC=algo.c \
board_operation.c \
board_size.c \
check_env.c \
output.c \
piece_operation.c \
place_piece.c \
read_file.c
#Set here your explicit list of files



ifdef OBJ_PREFIX
ifdef SRC_PREFIX
OBJ=$(patsubst $(SRC_PREFIX)/%.c, $(OBJ_PREFIX)/%.o, $(SRC))
else
OBJ=$(patsubst %.c, $(OBJ_PREFIX)/%.o, $(SRC))
endif
else
ifdef SRC_PREFIX
OBJ=$(patsubst $(SRC_PREFIX)/%.c, %.o, $(SRC))
else
OBJ=$(patsubst %.c, %.o, $(SRC))
endif
endif




init:
	@echo "Building $(NAME), checking for sub makefiles"

all: init sublibs $(NAME)

$(NAME): $(OBJ)
	@echo "==>Objects successfully buildt. Building " $(NAME)
ifeq ($(MODE),LIB)
	@ar rc $@ $^
	@echo "Archive build. Executing ranlib"
	@ranlib $@
else
	@$(CC) -o $@ $(MAIN_FILE) $^ -I$(INCLUDES) $(CFLAGS) $(LIBS)
endif
	@echo "==>Done!" $(NAME) "successfully compiled"

ifdef OBJ_PREFIX
ifdef SRC_PREFIX
$(OBJ_PREFIX)/%.o: $(SRC_PREFIX)/%.c
else
$(OBJ_PREFIX)/%.o: %.c
endif
else
ifdef SRC_PREFIX
%.o: $(SRC_PREFIX)/%.c
else
%.o: %.c
endif
endif
	@if ! [ -z "$(OBJ_PREFIX)" ]; then\
		mkdir -p $(OBJ_PREFIX);\
	fi;
	@echo "Building " $< " to " $@
	@$(CC) -o $@ -c $< -I$(INCLUDES) $(CFLAGS)

clean:
	@echo "Making clean..."
	@if [ -z "$(OBJ_PREFIX)" ]; then\
		rm -rf *.o;\
	else\
		rm -rf "$(OBJ_PREFIX)";\
	fi
	@echo "==>Done!"

fclean: clean
	@echo "Removing lib..."
	@rm -rf $(NAME)
	@echo "==>Done!"

re: fclean all

sublibs: $(addsuffix .submake,$(SUB_MAKEABLE))

%.submake: $(basename ./%)
	@echo "==>Making with args '$(MAKECMDGOALS)' for $< $@"
	@make $(MAKECMDGOALS) -C $<
	@echo "==>Making for $< OK"
