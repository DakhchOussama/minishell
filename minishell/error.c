#include "minishell.h"

int	print_error(void)
{
	printf("minishell: syntax error near unexpected token `|'\n");
	return (0);
}