NAME		= cub3D
CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Werror -Wextra -fsanitize=address -g
MLX			= -lmlx -framework OpenGL -framework AppKit
MLXA		= libmlx.a
INCLUDES	= -I includes

CUB3D		= main checks keypress parse
UTILS		= gnl split strings

SRCS 		= $(addsuffix .c, $(addprefix srcs/cub3d/, $(CUB3D))) \
			$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS)))

OBJS = $(SRCS:c=o)

%.o: %.c
	@printf "\033[0;33;1mGenerating cub3d objects... %-33.33s\r" $@
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo "\n"
	@echo "\033[0;32;1mCompiling scub3d..."
	@$(CC) $(CFLAGS) $(MLXA) $(MLX) $(OBJS) -o $(NAME)
	@echo "\n\033[0mDone !"

all: $(NAME)

clean:
	@echo "\033[38;5;160;1m\nRemoving objects..."
	@$(RM) $(OBJS)
	@echo "\033[0m"

fclean: clean
	@echo "\033[38;5;196;1m\nDeleting cub3d..."
	@$(RM) $(NAME)
	@echo "\033[0m"

re: fclean all

test: re
	make clean