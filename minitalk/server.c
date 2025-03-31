/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:59:15 by manon             #+#    #+#             */
/*   Updated: 2025/03/31 20:43:26 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	stock_message(char c, pid_t n, siginfo_t *info)
{
	static char		*str = NULL;
	char			*temp;

	if (c == '\0')
	{
		ft_printf(" 🔸User%d: %s\n", n, str);
		free(str);
		str = NULL;
		kill(info->si_pid, SIGUSR2);
	}
	else
	{
		if (str != NULL)
		{
			temp = ft_strjoin(str, c);
			free(str);
			str = temp;
		}
		else
		{
			str = malloc(2);
			str[0] = c;
			str[1] = 0;
		}
	}
}

void	signal_receive(int signum, siginfo_t *info, void *context)
{
	static char	binary[9];
	static int	i = 0;
	char		c;

	(void)context;
	if (signum == SIGUSR1)
	{
		binary[i] = '0';
		i++;
	}
	else if (signum == SIGUSR2)
	{
		binary[i] = '1';
		i++;
	}
	if (i == 8)
	{
		binary[++i] = 0;
		c = deprint_bits(binary);
		stock_message(c, info->si_pid, info);
		i = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

unsigned char	deprint_bits(char *binary)
{
	int	i;
	int	j;
	int	letter;

	i = 0;
	j = 128;
	letter = 0;
	while (j > 0 && binary[i])
	{
		if (binary[i] == '1')
			letter += j;
		i++;
		j /= 2;
	}
	return (letter);
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;

	(void)argv;
	if (argc != 1)
		return (1);
	ft_printf("🔶 Salon: %d 🔶\n\n 🔹User41004: W31c0m3 0n M!n!t41k🤖\n", getpid());
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = signal_receive;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
