NAME		= cub3D
CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Werror -Wextra -pthread
MLX			= -lmlx -framework OpenGL -framework AppKit
# MLX			= -lmlx -framework OpenGL -framework AppKit -L.
MLXA		= libmlx.a
INCLUDES	= -I includes

CHECKS		= checks flood parse queue color
HOOKS		= keypress mouse vertical horizontal
INTERACTION	= door audio boom
UTILS		= free gnl split strings stringss stringsss stringssss utils ft_strtok
RENDER		= main pp render load_textures textures raycast


SRCS 		= $(addsuffix .c, $(addprefix srcs/checks/, $(CHECKS))) \
			$(addsuffix .c, $(addprefix srcs/hooks/, $(HOOKS))) \
			$(addsuffix .c, $(addprefix srcs/interaction/, $(INTERACTION))) \
			$(addsuffix .c, $(addprefix srcs/render/, $(RENDER))) \
			$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS)))	\
			$(addsuffix .c, $(addprefix srcs/seele/, $(SEELE)))

# SRCS = test.c

OBJS_DIR	= objs/
OBJS		= $(addprefix $(OBJS_DIR), $(SRCS:c=o))

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@printf "\033[0;33;1mGenerating cub3D objects... %-33.33s\r" $@
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo "\n\n\033[0;32;1mCompiling cub3D..."
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX) $(MLXA)
	@echo "\n\033[0mDone !"

all: $(NAME)

clean:
	@echo "\033[38;5;160;1mRemoving objects..."
	@$(RM) $(OBJS_DIR)
	@echo "\033[0m"

fclean: clean
	@echo "\033[38;5;196;1mDeleting cub3D..."
	@$(RM) $(NAME)
	@echo "\033[0m"

re: fclean all

run: re
	@make clean