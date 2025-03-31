/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:59:26 by manon             #+#    #+#             */
/*   Updated: 2025/03/31 22:17:24 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t	g_confirmed = 0;

static void	confirmation_handler(int signum)
{
	if (signum == SIGUSR1)
		g_confirmed = 1;
	else if (signum == SIGUSR2)
	{
		ft_printf(" [Message envoyé]\n");
		exit(0);
	}
}

int	signal_sent(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (((c >> i) & 1) == 0)
			kill(pid, SIGUSR1);
		if (((c >> i) & 1) == 1)
			kill(pid, SIGUSR2);
		g_confirmed = 0;
		while (!g_confirmed)
			usleep(100);
		i--;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;
	int	server_pid;

	if (argc != 3)
		return (1);
	server_pid = ft_atoi(argv[1]);
	if (server_pid < 1)
		return (ft_printf(" [PID invalide]\n"));
	ft_printf("🔸Logged in as: User%d \n", getpid());
	signal(SIGUSR1, confirmation_handler);
	signal(SIGUSR2, confirmation_handler);
	i = 0;
	while (argv[2][i])
	{
		if (signal_sent(server_pid, argv[2][i]) == -1)
			return (ft_printf(" [PID invalide]\n"));
		i++;
	}
	signal_sent(server_pid, 0);
	g_confirmed = 0;
	while (!g_confirmed)
		pause();
	return (EXIT_SUCCESS);
}
