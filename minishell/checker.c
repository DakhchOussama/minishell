#include "minishell.h"

int check_first_last(void)
{
    char *str;

    str = ft_strtrim(g_data.line, " ");
    if (str[0] == '|')
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        g_data.exit_code = 258;
        return (0);
    }
    if (str[ft_strlen(str) - 1] == '|')
    {
        printf("minishell: syntax error: unexpected end of file\n");
		g_data.exit_code = 258;
		return (0);
    }
    free(str);
    str = NULL;
    return (1);

}

int check_pipes_two(char *str)
{
    int i;

    i = 0;
    if (check_first_last() == 0)
        return (0);
    str++;
	while ((*str) == ' ')
		str++;
	if ((*str) == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (g_data.exit_code = 258, 0);
	}
    return (1);
}

int check_pipes(void)
{
    char *str;

    str = ft_strchr(g_data.line, '|');
    if (!str)
        return (1);
    if (!check_pipes_two(str))
        return (0);
    str = ft_strchr(str, '|');
    if (!str)
        return (1);
    str++;
    while (*str)
	{
		while ((*str) == ' ')
			str++;
		if ((*str) == '|')
			return (g_data.exit_code = 258, print_error(), 0);
		str = ft_strchr(str, '|');
		if (!str)
			break ;
		str++;
	}
    free (str);
    return (1);
}

int check_quotes(void)
{
    return (1);
}