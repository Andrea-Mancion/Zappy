##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

INC_DIR	=	./inc/
SRC_DIR	=	./src/

SRC	=	$(SRC_DIR)map.cpp	\
		$(SRC_DIR)gui.cpp	\

OBJ	=	$(SRC:.cpp=.o)

NAME	=	gui

CFLAGS	+=	-Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system

all:	$(NAME)

$(NAME):	$(OBJ)
		g++ -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:	fclean all
