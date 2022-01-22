NAME			=	philo

INC				=	-I./headers

SRC_PATH		=	./

SRCS			=	./utils/strings.c ./philo.c

#SRCS			=	$(addprefix $(SRC_PATH), $(SRC))

philo			=	philo.c

UTILS			=	utils/strings.c

SRC				=	$(philo) \
					$(UTILS)
#					$()
#					$()
#					$()
#					$()
#					$()
#					$()
#					$()

OBJS			=	$(SRCS:.c=.o)

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -pthread #-fsanitize=thread -g3

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(INC) $(OBJS)

%.o : %.c Makefile
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
