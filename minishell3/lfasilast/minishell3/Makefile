NAME = minishell

HEADER = minishell.h

SRC = stock_env.c \
		utils/utils.c \
		utils/utils2.c\
		checker.c \
		parsing.c \
		error.c \
		main.c\
		ft_splite_and_check.c\
		free.c\
		execut.c\
		check_env_var.c\
		ft_itoa.c\
		ft_split.c\
		fill_name.c\
		ft_echo.c\
		ft_env1.c\
		ft_pwd.c\
		execut1.c\
		execute_other.c\
		exect2.c\

OBJ = $(SRC:.c=.o)

CFLAGS = -Werror -Wall -Wextra
LINKING_FLAGS = -lreadline -L${HOME}/homebrew/opt/readline/lib
COMPILE_FLAGS = -I${HOME}/homebrew/opt/readline/include

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(CFLAGS) $(LINKING_FLAGS) $(OBJ) -o $(NAME)
	@echo Execute is ready

.c.o: $(SRC) $(HEADER)
	@cc $(CFLAGS) $(COMPILE_FLAGS) -c $< -o $(<:.c=.o)

clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re