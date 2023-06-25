##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

D_SRC = ./ClientAI/src/

NAME = zappy_ai

# $(NAME)	:
# 			cp $(D_SRC)ai.py ./
# 			mv ai.py zappy_ai
# 			chmod +x zappy_ai

$(NAME)	:
# pip3 install -r $(D_SRC)requirements.txt
			ln -s $(D_SRC)ai2.py ../$(NAME)
			chmod +x ../$(NAME)

all	:	$(NAME)

clean:
		rm -rf ../zappy_ai

fclean:	clean

re	:	fclean all

.PHONY: all clean fclean re
