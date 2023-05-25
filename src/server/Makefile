##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Server Makefile
##

# Variables

SRC_DIR	=	./src/

SRC	=	\
	$(SRC_DIR)server_main.c	\
	$(SRC_DIR)classes/server/server_class.c	\
	$(SRC_DIR)classes/server/server_execution.c	\
	$(SRC_DIR)classes/server/server_interaction.c	\
	$(SRC_DIR)classes/params/params_class.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	zappy_server

CFLAGS	=	\
	-W	\
	-Wall	\
	-Wextra	\
	-Werror	\
	-I./inc/	\

CC	=	gcc

# Rules

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Extra rules

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re
