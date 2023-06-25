##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

INC_DIR	=	./inc/
SRC_DIR	=	./src/

SRC	=	$(SRC_DIR)map.cpp		\
		$(SRC_DIR)gui.cpp		\
		$(SRC_DIR)inventory.cpp	\
		$(SRC_DIR)player.cpp	\
		$(SRC_DIR)commands.cpp	\
		$(SRC_DIR)server.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	zappy_gui

CFLAGS	+=	-Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system

MAKEFLAGS += -j$(shell grep -c 'processor' /proc/cpuinfo)

all:	$(NAME)

$(NAME):	$(OBJ)
		g++ -o $(NAME) $(OBJ) $(CFLAGS)
		rm -f $(OBJ)
		mv -f $(NAME) ../../

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f ../../$(NAME)

re:	fclean all

debug: CFLAGS += -g
debug: re