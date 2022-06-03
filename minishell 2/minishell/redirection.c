#include "minishell.h"

int valid_redirect(char *str, int nbr)
{
    if (ft_strncmp(str, ">", nbr) == 0 || ft_strncmp(str, ">>", nbr) == 0
        || ft_strncmp(str, "<", nbr) == 0 || ft_strncmp(str, "<<", nbr) == 0)
            return (1);
    else
        return (0);
}

int check_redirection_error(char *str, int start, int nbr)
{
    char *tmp;

    tmp = ft_substr(str, start, nbr);
    if (!valid_redirect(tmp, nbr))
    {
        free(tmp);
        return (-1);
    }
    free(tmp);
    return (0);
}

int check_redirection(char *str)
{
    int i;
    int start;
    int red_nbr;

    if (!(check_syntax(str)))
        return (0);
    i = 0;
    while (str[i])
    {
        red_nbr = 0;
        start = i;
        i = skip_quotes(str, i);
        while (str[i] && (str[i] == '>' || str[i] == '<'))
        {
            red_nbr++;
            i++;
        }
        if (start != -1 && check_redirection_error(str, start, red_nbr) == -1)
            return (-1);
        i++;
    }
    return (0);
}

int check_syntax_2(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '<' && str[i] != '"' && str[i] != '\'')
        i++;
    i = skip_quotes(str, i);
    if (str[i])
    {
        i++;
        if (str[i] == '<')
            i++;
        while (str[i] == ' ')
            i++;
        if (str[i] == '<')
        {
            printf("syntax error near unexpected token `<'\n");
            return (0);
        }
    }
    return (1);
}

int check_syntax(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '>' && str[i] != '"' && str[i] != '\'')
        i++;
    i = skip_quotes(str, i);
    if (str[i])
    {
        i++;
        if (str[i] == '>')
            i++;
        while (str[i] == ' ')
            i++;
        if (str[i] == '>')
        {
            printf("syntax error near unexpected token `>'\n");
            return (0);
        }
    }
    if (!(check_syntax_2(str)))
        return (0);
    return (1);
}