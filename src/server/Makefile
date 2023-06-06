##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Server Makefile
##

# Variables

INC_DIR	=	./inc/

SRC_DIR	=	./src/

SRC	=	\
	$(SRC_DIR)zappy_main.c	\
	$(SRC_DIR)game/server/commands_table.c	\
	$(SRC_DIR)game/server/server_class.c	\
	$(SRC_DIR)game/server/server_accept_client.c	\
	$(SRC_DIR)game/server/server_read_client.c	\
	$(SRC_DIR)game/client/client_class.c	\
	$(SRC_DIR)game/map/map_class.c	\
	$(SRC_DIR)game/map/map_methods.c	\
	$(SRC_DIR)game/tile/tile_class.c	\
	$(SRC_DIR)program/params/params_class.c	\
	$(SRC_DIR)program/params/params_methods.c	\
	$(SRC_DIR)misc/list/list_class.c	\
	$(SRC_DIR)misc/list/list_methods.c	\
	$(SRC_DIR)misc/timer/timer_class.c	\
	$(SRC_DIR)misc/timer/timer_methods.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	zappy_server

CFLAGS	=	\
	-W	\
	-Wall	\
	-Wextra	\
	-Werror	\
	-I$(INC_DIR)	\

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
