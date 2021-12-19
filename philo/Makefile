NAME			=	philo

INC				=	-I./headers

SRC_PATH		=	./

#SRCS			=	./utils/strings.c ./philo.c

SRCS			=	$(addprefix $(SRC_PATH), $(SRC))

PHILO			=	philo.c

UTILS			=	utils/strings.c

SRC				=	$(PHILO) \
					$(UTILS)
#					$()
#					$()
#					$()
#					$()
#					$()
#					$()
#					$()

OBJS			=	$(SRCS:.c=.o)

CC				=	clang

CFLAGS			=	-Wall -Wextra -Werror -pthread #-fsanitize=thread

all : $(NAME) $(MAKEFILE)

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
