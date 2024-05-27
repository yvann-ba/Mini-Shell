#include "../minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	handle_sigint_here_doc(int sig)
{
	(void)sig;
	g_exit_signal = 1;
	return ;
}

void	init_signal_handlers(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
