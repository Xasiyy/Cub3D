#--------------------------\\\\\___VARIABLES___/////---------------------------#

MAKEFLAGS	+= --no-print-directory

NAME		=	libft.a

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -g3 -I${INC_DIR}
OBJ_DIR		=	objects
SRC_DIR		=	src/is \
				src/to \
				src/mem \
				src/fd \
				src/lst \
				src/str_ops \
				src/ft_printf \
				src/ft_dprintf \
				src/get_next_line 

INC_DIR		=	inc

#---------------------------\\\\\___SOURCES___/////----------------------------#

SRC			=	${IS} ${MEM} ${FD} ${LST} ${STR_OPS} ${TO} ${PRINTF} ${GNL} ${DPRINTF}

IS			=	./src/is/ft_isalpha.c \
				./src/is/ft_isdigit.c \
				./src/is/ft_isalnum.c \
				./src/is/ft_isascii.c \
				./src/is/ft_isprint.c \
				./src/is/ft_isspace.c \
				./src/is/ft_isonlyspace.c

TO			=	./src/to/ft_toupper.c \
				./src/to/ft_tolower.c \
				./src/to/ft_atoi.c \
				./src/to/ft_atol.c \
				./src/to/ft_itoa.c 

MEM			=	./src/mem/ft_calloc.c \
				./src/mem/ft_realloc.c \
				./src/mem/ft_ffa.c \
				./src/mem/ft_freetab.c \
				./src/mem/ft_memchr.c \
				./src/mem/ft_memcmp.c \
				./src/mem/ft_memcpy.c \
				./src/mem/ft_memmove.c \
				./src/mem/ft_memset.c \
				./src/mem/ft_bzero.c \
				./src/mem/ft_secumalloc.c \
				./src/mem/ft_secufree.c

FD			=	./src/fd/ft_putchar_fd.c \
				./src/fd/ft_putstr_fd.c \
				./src/fd/ft_putendl_fd.c \
				./src/fd/ft_putnbr_fd.c

LST			=	./src/lst/ft_lstnew.c \
				./src/lst/ft_lstadd_front.c \
				./src/lst/ft_lstsize.c \
				./src/lst/ft_lstlast.c \
				./src/lst/ft_lstadd_back.c \
				./src/lst/ft_lstdelone.c \
				./src/lst/ft_lstclear.c \
				./src/lst/ft_lstiter.c \
				./src/lst/ft_lstmap.c

STR_OPS		=	./src/str_ops/ft_strlen.c \
				./src/str_ops/ft_strlcpy.c \
				./src/str_ops/ft_strlcat.c \
				./src/str_ops/ft_strchr.c \
				./src/str_ops/ft_strrchr.c \
				./src/str_ops/ft_strncmp.c \
				./src/str_ops/ft_strnstr.c \
				./src/str_ops/ft_strdup.c \
				./src/str_ops/ft_strndup.c \
				./src/str_ops/ft_substr.c \
				./src/str_ops/ft_strjoin.c \
				./src/str_ops/ft_strtrim.c \
				./src/str_ops/ft_split.c \
				./src/str_ops/ft_strmapi.c \
				./src/str_ops/ft_striteri.c \
				./src/str_ops/ft_wcount.c \
				./src/str_ops/ft_filecheck.c

PRINTF		=	./src/ft_printf/ft_printf.c \
				./src/ft_printf/ft_print_pxX.c \
				./src/ft_printf/ft_print_diu.c \
				./src/ft_printf/ft_print_cs%.c

GNL			=	./src/get_next_line/get_next_line.c

DPRINTF		=	./src/ft_dprintf/ft_dprintf.c \
				./src/ft_dprintf/ft_dprint_cs%.c \
				./src/ft_dprintf/ft_dprint_diu.c \
				./src/ft_dprintf/ft_dprint_pxX.c

OBJ			=	$(patsubst %.c,${OBJ_DIR}/%.o,${SRC})

#----------------------------\\\\\___RULES___/////-----------------------------#

all:			${NAME}

${OBJ_DIR}/%.o: %.c | ${OBJ_DIR}
				@mkdir -p $(dir $@)
				@${CC} ${FLAGS} -c $< -o $@

${OBJ_DIR}:
				@mkdir -p ${OBJ_DIR}

${NAME}:		${OBJ}
				@echo "🧠⚡ Compiling libft..."
				@ar rcs ${NAME} ${OBJ}
				@echo "✅🦾 libft is ready for use!"

vpath %.c . ${SRC_DIR}

clean:
				@rm -rf ${OBJ_DIR}

fclean:			clean
				@echo "🚮   Removing libft..."
				@rm -f ${NAME}
				@echo "❌   libft has been removed."

re:				fclean all

.PHONY:			all clean fclean re
