##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC	=	map.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	sfml_window

CFLAGS	+=	-Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system -Iinc/


all:	$(NAME)

$(NAME):	$(OBJ)
		g++ -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:	fclean all
