NAME = libft.a
CC = clang
CFLAGS = -Wall -Wextra -Werror -Iincludes -g
FILES =		ft_isalpha.c	ft_isdigit.c	ft_isalnum.c	ft_isascii.c	ft_isprint.c	\
			ft_strlen.c		ft_memset.c		ft_bzero.c		ft_memcpy.c		ft_memmove.c	\
			ft_strlcpy.c	ft_strlcat.c	ft_toupper.c	ft_tolower.c	ft_strchr.c		\
			ft_strrchr.c	ft_strncmp.c	ft_memchr.c		ft_memcmp.c		ft_strnstr.c	\
			ft_atoi.c		ft_calloc.c		ft_strdup.c		ft_substr.c		ft_strjoin.c	\
			ft_strtrim.c	ft_split.c		ft_itoa.c		ft_strmapi.c	ft_striteri.c	\
			ft_putchar_fd.c	ft_putstr_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c

VPATH = srcs/\

HEADERS = includes/libft.h\

FILES_O = $(addprefix objs/, $(notdir $(FILES)))
FILES_O_B = $(addprefix objs/, $(notdir $(FILES_B)))
SRCS = $(addprefix srcs/, $(FILES))
OBJS = $(FILES_O:.c=.o)
OBJS_B = $(FILES_O_B:.c=.o)
OBJDIR = objs/

NB = $(words $(FILES))
INDEX = 0

objs/%.o : %.c Makefile $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval PERCENT=$(shell expr $(INDEX) '*' 100 / $(NB)))
	@$(eval PROGRESS=$(shell expr $(INDEX) '*' 30 / $(NB)))
	@printf "\r\033[38;5;11mMAKE LIBFT %2d%%\033[0m \033[48;5;32m%*s\033[0m %s\033[K" $(PERCENT) $(PROGRESS) "" $(notdir $@)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir objs/

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $?
	@printf "\r\033[38;5;10mLIBFT DONE\033[0m\033[K\n"

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJDIR)
	@printf "\033[38;5;192mCLEAN LIBFT\033[0m\n"

fclean : clean
	@rm -rf $(NAME)
	@printf "\033[38;5;190mFULL CLEAN LIBFT\033[0m\n"

re: fclean all
