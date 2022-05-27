NAME = minishell

HEADER = minishell.h

SRC = main.c \
		stock_env.c \
		utils.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Werror -Wall -Wextra
LINKING_FLAGS = -lreadline -L${HOME}/homebrew/opt/readline/lib
COMPILE_FLAGS = -I${HOME}/homebrew/opt/readline/include

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