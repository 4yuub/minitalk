/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 03:04:52 by akarafi           #+#    #+#             */
/*   Updated: 2021/12/01 01:41:38 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int	g_pid = 0;

void	reset(siginfo_t *info, int *n, char *c)
{
	*c = 0;
	*n = 0;
	g_pid = info->si_pid;
}

void	handle_sig(int sig, siginfo_t *info, void *context)
{
	static int	n;
	static char	c;
	static int	sign;

	(void) context;
	if (g_pid != info->si_pid)
		reset(info, &n, &c);
	if (!n && sig == SIGUSR2)
		sign = -1;
	else if (n == 0)
		sign = 1;
	else
		c = c << 1 | sig - SIGUSR1;
	n++;
	if (n == 9)
	{
		if (c == 0)
			kill(info->si_pid, SIGUSR1);
		else
			ft_putchar(c * sign);
		c = 0;
		n = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handle_sig;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "my pid is: ", 11);
	ft_putnbr(getpid());
	ft_putchar('\n');
	while (1)
		sleep(1);
}
