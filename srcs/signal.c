#include <signal.h>
#include <unistd.h>
#include "minishell.h"

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

void	signal_exec(int sig)
{
	signal(sig, signal_exec);
}
