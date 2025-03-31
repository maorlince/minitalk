/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:59:15 by manon             #+#    #+#             */
/*   Updated: 2025/03/31 16:30:53 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	stock_message(char c, pid_t n, siginfo_t *info)
{
	static char		*str = NULL;
	int				j;
	char			*temp;

	j = 0;
	if (c == '\0')
	{
		j = 0;
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
			j++;
		}
		else
		{
			str = malloc(2);
			str[j] = c;
			j++;
			str[j] = 0;
		}
	}
}

//void	stock_message(char c, pid_t n, siginfo_t *info)
//{
//	static char		*str;
//	static int		j;
//	char			*temp;
//	char			c_2[2];
//
//	str = NULL;
//	j = 0;
//	// str[j] = c;
//	write(1, "ok", 2);
//	if (c == '\0')
//	{
//		ft_printf("ok1\n");
//		j = 0;
//		ft_printf(" 🔸User%d: %s\n", n, str);
//		free(str);
//		kill(info->si_pid, SIGUSR2);
//	}
//	else
//	{
//		ft_printf("ok2\n");
//		if (!str)
//		{
//			c_2[0] = c;
//			c_2[1] = 0;
//			str = ft_strdup(c_2);
//		}
//		else
//		{
//			temp = ft_strjoin(str, c);
//			free(str);
//			str = temp;
//		}
//		j++;
//	}
//}

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
	//ft_printf("[Signal entrant]\n");
	sig.sa_sigaction = signal_receive;
	//ft_printf("[Reception de signal]\n");
	sigemptyset(&sig.sa_mask);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	//ft_printf("[En pause]\n");
	while (1)
		pause();
	ft_printf("[Reception du message..]\n");
	return (EXIT_SUCCESS);
}
