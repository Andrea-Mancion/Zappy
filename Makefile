##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Root Makefile
##

# Variables

SERVER_NAME = zappy_server

CLIENT_NAME = zappy_ai

GUI_NAME = zappy_gui

# Rules

$(SERVER_NAME):
	@make -C src/server

$(CLIENT_NAME):
	@make -C ClientAI

$(GUI_NAME):
	@make -C src/gui

all: $(GUI_NAME) $(CLIENT_NAME) $(SERVER_NAME)

clean:
	@make clean -C src/server
	@make clean -C ClientAI
	@make clean -C src/gui

fclean: clean
	@make fclean -C src/server
	@make fclean -C ClientAI
	@make fclean -C src/gui

re: fclean all

.PHONY: all clean fclean re
