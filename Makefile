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

# $(SERVER_NAME):
#	@make -C server

# $(CLIENT_NAME):
#	@make -C client

# $(GUI_NAME):
#	@make -C gui

all: # $(SERVER_NAME) $(CLIENT_NAME) $(GUI_NAME)

clean:
#	@make clean -C server
#	@make clean -C client
#	@make clean -C gui

fclean: clean
#	@make fclean -C server
#	@make fclean -C client
#	@make fclean -C gui

re: fclean all

.PHONY: all clean fclean re
