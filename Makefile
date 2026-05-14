#******************************************************************************#

#--------------------------\\\\\___VARIABLES___/////---------------------------#

MAKEFLAGS	+= --no-print-directory

NAME		=	cub3D

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 -I${INC} #-fsanitize=address

OBJ_DIR		=	obj
SRC_DIR		=	src/main/ \
				src/parser/ \
				src/graphics/

#---------------------------\\\\\___SOURCES___/////----------------------------#

SRC			=	${MAIN} ${PARSER} ${GRAPHICS} ${GC}

MAIN		=	${M}cb_main.c \
				${M}cb_initialization.c \
				${M}cb_free.c \
				${M}cb_utils.c \
				${M}cb_initialization_player.c \
				${M}cb_libutils.c

GRAPHICS    =   ${G}init_graphics.c \
				${G}minimap.c \
				${G}draw_minimap_mm.c \
				${G}control.c \
				${G}collisions.c \
				${G}player.c \
				${G}render_map.c \
				${G}raycasting/raycasting.c \
				${G}raycasting/intersections.c \
				${G}raycasting/rendu_3D.c \
				${G}raycasting/utils_raycasting.c \
				${G}raycasting/draw_view.c \
				${G}raycasting/init_textures.c

PARSER		=	${P}cb_parser.c \
				${P}cb_pars_sfile.c \
				${P}cb_pars_pc_checkduplicate.c \
				${P}cb_pars_pc_extractors.c \
				${P}cb_pars_map.c

GC          =	./src/gc/gc.c \
				./src/gc/gc_utils.c

INC			=	./inc/
M			=	./src/main/
P			=	./src/parser/
G			=	./src/graphics/

LIBFT		=	./libft/libft.a

OBJ			=	$(patsubst %.c,${OBJ_DIR}/%.o,${SRC})

#----------------------------\\\\\___MLX___/////-----------------------------#

MLX_DIR		=	minilibx-linux
MLX_LIB		=	$(MLX_DIR)/libmlx.a
MLX_FLAGS	=	-L$(MLX_DIR) -lmlx -lXext -lX11
INCLUDES	=	-I$(INC) -I$(MLX_DIR)

#----------------------------\\\\\___RULES___/////-----------------------------#

all:			${NAME}

${OBJ_DIR}/%.o: %.c | ${OBJ_DIR}
				@mkdir -p $(dir $@)
				@${CC} ${CFLAGS} -c $< -o $@

${OBJ_DIR}:
				@mkdir -p ${OBJ_DIR}

${MLX_LIB}:
				@echo "📦   Compiling MLX..."
				@make -C $(MLX_DIR)

vpath %.c . ${SRC_DIR}

${NAME}:		${MLX_LIB} ${OBJ}
				@make -C ./libft
				@echo "🧠⚡ Compiling ${NAME}..."
				@${CC} ${CFLAGS} ${OBJ} ${LIBFT} ${MLX_LIB} -o ${NAME} ${MLX_FLAGS} -lreadline -lm
				@echo "✅🦾 ${NAME} is ready!"

norm:
				@norminette -R CheckForbiddenSourceHeader | grep "Error" \
				|| echo "✅ No norm error, directory clean."

val:
				@echo "==============================="
				@echo "🛠️  Valgrind checking for leaks"
				@echo "==============================="
				@valgrind --leak-check=full --show-leak-kinds=all \
				--track-fds=yes --suppressions=mlx.supp\
				./${NAME} ${ARG}; STATUS=$$?;

clean:
				@echo "🚮   Removing project files..."
				@rm -rf ${OBJ_DIR}
				@make clean -C ./libft

fclean:			clean
				@echo "🚮   Removing project..."
				@rm -f ${NAME}
				@make fclean -C ./libft
				@echo "❌   ${NAME} has been removed."

re:				fclean all

relib:			fclean libft

.PHONY:			all clean fclean re libft norm val relib

#******************************************************************************#