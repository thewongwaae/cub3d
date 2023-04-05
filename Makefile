NAME		= cub3D
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -fsanitize=address -g
MLX			= -L. -lmlx -framework OpenGL -framework AppKit
INCLUDES	= -I includes -I mlx

CUB3D		= main checks
PARSE		= keypress parse
UTILS		= gnl split strings

SRCS 		= $(addsuffix .c, $(addprefix srcs/cub3d/, $(GAME))) \
			$(addsuffix .c, $(addprefix srcs/parse/, $(PARSE))) \
			$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS)))

OBJS = $(SRCS:c=o)

%.o: %.c
	@printf "\033[0;33;1mGenerating cub3d objects... %-33.33s\r" $@
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo "\n"
	@echo "\033[0;32;1mCompiling scub3d..."
	@$(CC) $(CFLAGS) $(MLX) $(OBJS) -o $(NAME) libmlx.a
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