/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:59:26 by manon             #+#    #+#             */
/*   Updated: 2025/02/27 13:40:03 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	confirmed = 0;

static void	confirmation_handler(int signum)
{
	(void)signum;
	confirmed = 1;
}

int	ft_atoi(char *c)
{
	int	i;
	int	j;
	int	sign;

	i = 0;
	j = 0;
	sign = 1;
	if (c[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (c[i] && c[i] >= '0' && c[i] <= '9')
	{
		j *= 10;
		j += (c[i] - 48);
		i++;
	}
	return (j * sign);
}

char	*print_bits(unsigned char letter)
{
	int		i;
	int		j;
	int		byte;
	char	*binary;

	i = 128;
	j = 0;
	byte = 0;
	binary = malloc(9);
	if (!binary)
		exit(EXIT_FAILURE);
	while (i > 0)
	{
		if (letter - byte >= i)
		{
			binary[j] = '1';
			byte += i;
		}
		else
			binary[j] = '0';
		i /= 2;
		j++;
	}
	binary[j] = 0;
	return (binary);
}

int	signal_send(int pid, char *binary)
{
	int	i;

	i = 0;
	while (binary[i])
	{
		if (binary[i] == '0')
		{
			if (kill(pid, SIGUSR1) == -1)
				return (-1);
		}
		else if (binary[i] == '1')
		{
			if (kill(pid, SIGUSR2) == -1)
				return (-1);
		}
		else
			return (-1);
		i++;
		usleep(500);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	char	*binary;
	int		server_pid;

	if (argc != 3)
		return (1);
	//ft_printf("🔸Generation of profil: User%d \n", getpid());
	server_pid = ft_atoi(argv[1]);
	signal(SIGUSR1, confirmation_handler);
	i = 0;
	while (argv[2][i])
	{
		binary = print_bits(argv[2][i]);
		if (!binary)
		{
			return (1);
		}
		if (signal_send(server_pid, binary) == -1)
		{
			free(binary);
			ft_printf("[Mauvais PID]\n");
			return (1);
		}
		confirmed = 0;
		free(binary);
		ft_printf("wait");
		while (!confirmed)
			pause();
		ft_printf("[Signal recu]\n");
		i++;
	}
	binary = print_bits('\0');
	if (signal_send(server_pid, binary) == -1)
	{
		free(binary);
		return (1);
	}
	free(binary);
	confirmed = 0;
	while (!confirmed)
		usleep(200);
	ft_printf("[Message recu]\n");
	return (EXIT_SUCCESS);
}
