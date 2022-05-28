#include "minishell.h"

t_nodes **parsing (void)
{
    t_nodes **nodes;

    add_history(g_data.line);
    nodes = malloc(sizeof(t_nodes *));
    if (!nodes)
		  return (perror("Error"), exit (EXIT_FAILURE), NULL);

    if (check_pipes() == 0 || check_pipes() == 0)
        return (NULL);

    return (nodes);
}