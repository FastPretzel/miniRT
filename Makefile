NAME = minirt
NAME_B = minirt_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g -fsanitize=address#-Ofast
FILES = main.c	vec_utils.c	mlx_utils.c\
	camera.c	utils.c\
	lst_utils.c	sphere.c	light.c\
	color_utils.c	temp_utils.c	plane.c\
	cylinder.c	cone.c		keys.c\
	translate.c	rotate.c	render.c\
	rotate_utils.c	get_next_line.c		get_next_line_utils.c	ft_split_new.c		ft_strjoin3.c	\
	common_funcs0.c		common_funcs1.c			common_funcs2.c		common_funcs3.c	\
	parse_scene00.c		parse_scene01.c			parse_scene02.c		parse_scene03.c	\
	parse_scene04.c		parse_scene05.c			parse_scene06.c		parse_scene07.c	\
	parse_scene08.c		parse_scene09.c			parse_scene10.c		parse_scene11.c	\
	scene_converter00.c	parser_free_scene01.c

#FILES_B

VPATH = srcs/\
		srcs_bonus/

LIBFT_DIR := libft
LIBFT_LIB := $(LIBFT_DIR)/libft.a

HEADERS = includes/minirt.h\
	includes/get_next_line.h

FILES_O = $(addprefix objs/, $(notdir $(FILES)))
FILES_O_B = $(addprefix objs/, $(notdir $(FILES_B)))
SRCS = $(addprefix srcs/, $(FILES))
OBJS = $(FILES_O:.c=.o)
OBJS_B = $(FILES_O_B:.c=.o)
OBJDIR = objs/

NB = $(words $(FILES))
INDEX = 0

objs/%.o : %.c Makefile $(HEADERS)
	@$(CC) $(CFLAGS) -Imlx -I$(LIBFT_DIR) -c $< -o $@
	@$(eval PERCENT=$(shell expr $(INDEX) '*' 100 / $(NB)))
	@$(eval PROGRESS=$(shell expr $(INDEX) '*' 30 / $(NB)))
	@printf "\r\033[38;5;87mMAKE MINIRT %2d%%\033[0m \033[48;5;32m%*s\033[0m %s\033[K" $(PERCENT) $(PROGRESS) "" $(notdir $@)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir objs/

bonus: $(OBJDIR) $(NAME_B)

$(NAME) : $(LIBFT_LIB) $(OBJS)
	@$(CC) $(CFLAGS) -L$(LIBFT_DIR) -lft -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS)
	@printf "\r\033[38;5;82mMINIRT DONE\033[0m\033[K\n"

$(NAME_B) : $(OBJS_B)
	@$(CC) $(CFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME_B) $(OBJS_B)
	@printf "\r\033[38;5;82mMINIRT BONUS DONE\033[0m\033[K\n"

$(LIBFT_LIB): libft1

libft1:
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJDIR)
	@make clean -C libft
	@printf "\033[38;5;85mCLEAN\033[0m\n"

fclean : clean
	@rm -rf $(NAME) $(NAME_B)
	@make fclean -C libft
	@printf "\033[38;5;84mFULL CLEAN\033[0m\n"

re: fclean all
