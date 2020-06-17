NAME			= hangman

SRC				=	./main.c\
					./gnl/get_next_line.c\
					./gnl/get_next_line_utils.c\

ROAD_S			= $(SRC)

ROAD_O			= $(OBJ)

FLAGS			= -Wall -Wextra -Werror

OBJ				= $(SRC:.c=.o)

CC				= clang

$(NAME) :		$(OBJ)
				$(CC) $(FLAGS) $(OBJ) -ltermcap -o $(NAME)

all :			$(NAME)

clean :
				rm -f $(ROAD_O)

fclean :
				rm -f $(ROAD_O)
				rm -f $(NAME)

re : 			fclean all

.PHONY: 		all clean fclean re
