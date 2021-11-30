/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarafi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:44:23 by akarafi           #+#    #+#             */
/*   Updated: 2021/11/30 22:01:27 by akarafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

char	*get_bin(char byte)
{
	char	*bin;
	int		i;

	bin = malloc(9);
	if (!bin)
	{
		write(1, "allocation failed", 17);
		exit(1);
	}
	bin[8] = '\0';
	i = 7;
	while (i >= 0)
	{
		bin[i] = (byte % 2) + '0';
		byte /= 2;
		i--;
	}
	return (bin);
}

void	send_byte(char byte, int pid)
{
	char	*bin;
	int		i;

	usleep(500);
	if (byte < 0)
	{
		kill(pid, SIGUSR2);
		byte *= -1;
	}
	else
		kill(pid, SIGUSR1);
	bin = get_bin(byte);
	i = 0;
	while (i < 8)
	{
		usleep(500);
		if (bin[i] == '0')
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
	}
	free(bin);
}

void	handler(int sig)
{
	static int	i;

	if (sig == SIGUSR1)
	{
		write(1, "\nServer: done!\n", 15);
		exit(0);
	}
	else
	{
		write(1, "\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r", 35);
		write(1, "Server: signal received ", 24);
		ft_putnbr(++i);
	}
}

int	main(int ac, char *av[])
{
	int		pid;
	char	*s;
	int		i;

	if (ac != 3)
	{
		write(1, "args error", 10);
		exit(1);
	}
	pid = ft_atoi(av[1]);
	s = av[2];
	i = 0;
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (s[i])
		send_byte(s[i++], pid);
	send_byte(0, pid);
	pause();
}
