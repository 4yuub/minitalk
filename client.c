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

void handler(int sig)
{
	(void) sig;
	write(1, "Server: done!\n", 14);
	exit(0);
}

int main(int ac, char *av[])
{
	int 	pid;
	char 	*s;
	int 	i;

	if (ac != 3)
	{
		write(1, "args error", 10);
		exit(1);
	}
	pid = ft_atoi(av[1]);
	s = av[2];
	i = 0;
	signal(SIGUSR1, handler);
	while (s[i])
		send_byte(s[i++], pid);
	send_byte(0, pid);
	pause();
}
