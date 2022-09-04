NAME = minirt
NAME_B = minirt_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g #-Ofast
FILES = main.c	vec_utils.c	mlx_utils.c\
	camera.c	objects.c	utils.c\
	lst_utils.c	sphere.c	light.c\
	color_utils.c

#FILES_B

VPATH = srcs/\
		srcs_bonus/

HEADERS = includes/minirt.h\

FILES_O = $(addprefix objs/, $(notdir $(FILES)))
FILES_O_B = $(addprefix objs/, $(notdir $(FILES_B)))
SRCS = $(addprefix srcs/, $(FILES))
OBJS = $(FILES_O:.c=.o)
OBJS_B = $(FILES_O_B:.c=.o)
OBJDIR = objs/

NB = $(words $(FILES))
INDEX = 0

objs/%.o : %.c Makefile $(HEADERS)
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@
	@$(eval PERCENT=$(shell expr $(INDEX) '*' 100 / $(NB)))
	@$(eval PROGRESS=$(shell expr $(INDEX) '*' 30 / $(NB)))
	@printf "\r\033[38;5;87mMAKE MINIRT %2d%%\033[0m \033[48;5;32m%*s\033[0m %s\033[K" $(PERCENT) $(PROGRESS) "" $(notdir $@)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir objs/

bonus: $(OBJDIR) $(NAME_B)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJS)
	@printf "\r\033[38;5;82mMINIRT DONE\033[0m\033[K\n"

$(NAME_B) : $(OBJS_B)
	@$(CC) $(CFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME_B) $(OBJS_B)
	@printf "\r\033[38;5;82mMINIRT BONUS DONE\033[0m\033[K\n"

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJDIR)
	@printf "\033[38;5;85mCLEAN\033[0m\n"

fclean : clean
	@rm -rf $(NAME) $(NAME_B)
	@printf "\033[38;5;84mFULL CLEAN\033[0m\n"

re: fclean all
