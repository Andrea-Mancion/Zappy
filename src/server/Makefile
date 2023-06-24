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
	$(SRC_DIR)game/ai_commands/ai_commands_table.c	\
	$(SRC_DIR)game/ai_commands/ai_commands_movement.c	\
	$(SRC_DIR)game/ai_commands/ai_commands_object.c	\
	$(SRC_DIR)game/ai_commands/ai_commands_check.c	\
	$(SRC_DIR)game/graphic_commands/input/graphic_commands_table.c	\
	$(SRC_DIR)game/graphic_commands/input/graphic_commands_player.c	\
	$(SRC_DIR)game/graphic_commands/input/graphic_commands_map.c	\
	$(SRC_DIR)game/graphic_commands/output/graphic_notifications_map.c	\
	$(SRC_DIR)game/graphic_commands/output/graphic_notifications_player.c	\
	$(SRC_DIR)game/graphic_commands/output/graphic_notifications_player2.c	\
	$(SRC_DIR)game/graphic_commands/output/graphic_notifications_error.c	\
	$(SRC_DIR)game/graphic_commands/output/graphic_notifications_table.c	\
	$(SRC_DIR)game/events/events_table.c	\
	$(SRC_DIR)game/events/events_command.c	\
	$(SRC_DIR)game/events/events_automatic.c	\
	$(SRC_DIR)game/server/server_class.c	\
	$(SRC_DIR)game/server/server_methods.c	\
	$(SRC_DIR)game/server/server_select.c	\
	$(SRC_DIR)game/server/server_client.c	\
	$(SRC_DIR)game/client/client_class.c	\
	$(SRC_DIR)game/client/client_methods.c	\
	$(SRC_DIR)game/map/map_class.c	\
	$(SRC_DIR)game/map/map_methods.c	\
	$(SRC_DIR)game/tile/tile_class.c	\
	$(SRC_DIR)game/game_class.c	\
	$(SRC_DIR)game/game_methods.c	\
	$(SRC_DIR)game/game_client.c	\
	$(SRC_DIR)game/game_run.c	\
	$(SRC_DIR)game/game_event.c	\
	$(SRC_DIR)program/params/params_class.c	\
	$(SRC_DIR)program/params/params_methods.c	\
	$(SRC_DIR)misc/list/list_class.c	\
	$(SRC_DIR)misc/list/list_methods.c	\
	$(SRC_DIR)misc/map/map_class.c	\
	$(SRC_DIR)misc/map/map_methods.c	\

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
