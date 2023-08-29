SRCS = fill_struct.c get_elf_file_info.c gets.c

OBJS = ${SRCS:.c=.o}

NAME = libft_elf.a

CC = gcc

INCLUDES = includes/

CFLAGS = -Wall -Wextra -Werror

%.o : %.c libft.h
	@${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	@ar rc ${NAME} ${OBJS}
	@ranlib ${NAME}

all: ${NAME}

clean:
	@${RM} ${OBJS} ${OBJS2}

fclean: clean
	@${RM} ${NAME}

re:	fclean all