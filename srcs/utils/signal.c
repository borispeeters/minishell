#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	This function is executed when a signal is caught.
*/

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("\b\b  ", STDOUT_FILENO);
		write_prompt();
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	}
}

/*
**	This function is executed when a signal is caught
**	while in a blocking executable like cat.
*/

void	signal_exec(int sig)
{
	signal(sig, signal_exec);
}
