#Param
MAKEFLAGS += --no-print-directory

CC			= cc
FLAGS		= -Wall -Werror -Wextra -Iinc
NAME		= philo
OBJ_DIR		= .obj

# Sources et obj main Makefile
SRCS		= \
			src/main.c \
			src/init.c \
			src/launch_threads.c \
			src/life.c \
			src/monitor.c \
			src/print.c \
			src/time_utils.c \
			src/utils.c \
			src/utils_libft.c
		
OBJS		= ${SRCS:.c=.o}
OBJS		:= ${addprefix ${OBJ_DIR}/,${notdir ${OBJS}}}

#Regles
all:		${NAME}

${OBJ_DIR}/%.o:	src/%.c
				@mkdir -p ${OBJ_DIR}
				@${CC} ${FLAGS} -c $< -o $@

${NAME}:	${OBJS}
			@${CC} ${FLAGS} ${OBJS} -o ${NAME}
			@echo "✅ ${NAME} Compiling done !\n"

clean:
			@rm -rf ${OBJ_DIR}
			@echo "✅ (clean) Objects deleted !"

fclean:		clean
			@rm -f ${NAME}
			@echo "✅ (fclean) Program deleted !"

re:			fclean all

norm:
			@norminette $(SRCS) inc | grep -v "OK!" | grep -v "GLOBAL_VAR_DETECTED"|| echo "✅ Norminette: No errors found!"

.PHONY:		all clean fclean re norm