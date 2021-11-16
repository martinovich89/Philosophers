NAME			=	philosophers

INC				=	-I./headers

SRCS			=	$(addprefix $(SRC_PATH), $(SRC))

PHILO			=	philosophers.c

SRC				=	$(PHILO) \
#					$()
#					$()
#					$()
#					$()
#					$()
#					$()
#					$()
#					$()

OBJS			=	$(SRCS:.c=.o)

CC				=	clang

CFLAGS			=	-Wall -Wextra -Werror -fsanitize=address -g3

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJS) $(LIB)

%o : %c
		$(CC) $(CFLAGS) $(INC) -o $a -c $<

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
