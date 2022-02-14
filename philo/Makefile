NAME			=	philo

INC				=	-I./headers

SRC_PATH		=	./

PHILO			=	philo.c

MEM				=	mem.c

TIME			=	time.c

PHASE			=	phase.c

INITS			=	inits.c

EDIT			=	philo_edit.c

PRINT			=	print.c

CLEAR			=	clear.c

CHECKS			=	checks.c

UTILS			=	utils/strings.c utils/utils.c utils/utils2.c

SRC				=	$(PHILO) \
					$(UTILS) \
					$(PRINT) \
					$(MEM) \
					$(TIME) \
					$(INITS) \
					$(CHECKS) \
					$(EDIT) \
					$(CLEAR) \
					$(PHASE)

OBJS			=	$(SRC:.c=.o)

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -pthread #-fsanitize=thread

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME)

%.o : %.c Makefile
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
