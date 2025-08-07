CC = cc

FLAGS = -Wall -Werror -Wextra

SRCS = main.c utils.c philo_routine.c threads.c monitor.c

OBJS =$(SRCS:.c=.o)

NAME = philo

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean: 
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re