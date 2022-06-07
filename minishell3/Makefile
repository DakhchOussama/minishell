NAME = minishell

HEADER = minishell.h

SRC = stock_env.c \
		utils.c \
		checker.c \
		parsing.c \
		error.c \
		main.c\
		ft_splite_and_check.c\
		free.c\

OBJ = $(SRC:.c=.o)

CFLAGS = -Werror -Wall -Wextra
LINKING_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
COMPILE_FLAGS = -I${HOME}/.brew/opt/readline/include

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(CFLAGS) $(LINKING_FLAGS) $(OBJ) -o $(NAME)
	@echo Execute is ready

.c.o: $(SRC) $(HEADER)
	@cc $(CFLAGS) $(COMPILE_FLAGS) -c $< -o $(<:.c=.o)

clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re