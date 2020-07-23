#include <stdlib.h>
#include "libft.h"

char    **init_env(char **envp)
{
    char    **env;
    int     length;
    int     i;

    env = NULL;
    length = 0;
    i = 0;
    while (envp[length])
        ++length;
    env = malloc(sizeof(*env) * (length + 1));
    while (i < length)
    {
        env[i] = ft_strdup(envp[i]);
        ++i;
    }
    env[length] = NULL;
    return (env);
}

char	**free_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        free(env[i]);
        env[i] = NULL;
        ++i;
    }
    free(env);
    env = NULL;
    return (env);
}
