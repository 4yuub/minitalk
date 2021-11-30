/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 03:04:52 by akarafi           #+#    #+#             */
/*   Updated: 2021/11/30 18:18:04 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	handle_sig(int sig, siginfo_t *info, void *context)
{
	static	int	n;
	static	char c;
	static 	int sign;

	(void) context;
	if (!n && sig == SIGUSR2)
		sign = -1;
	else if (n == 0)
		sign = 1;
	else
		c = c << 1 | sig - 30;
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
	struct sigaction sa;

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
