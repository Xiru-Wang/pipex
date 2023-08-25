NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = pipex.h
SRC = pipex.c \
		utils1.c \
		utils2.c \
		ft_split.c

OBJS = $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re
