/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:59:15 by manon             #+#    #+#             */
/*   Updated: 2025/02/27 13:34:58 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_stc
{
	char	binary[9];
	int		i;
}	t_stc;
static t_stc	g_stc = {.binary = {0}, .i = 0};


void	signal_receive(int signum, siginfo_t *info, void *context)
{
	char	c;
	(void)context;
	//ft_printf("🔸User%d :", info->si_pid);
	if (signum == SIGUSR1)
	{
		g_stc.binary[g_stc.i] = '0';
		g_stc.i++;
	}
	else if (signum == SIGUSR2)
	{
		g_stc.binary[g_stc.i] = '1';
		g_stc.i++;
	}
	if (g_stc.i == 8)
	{
		g_stc.binary[g_stc.i] = 0;
		ft_printf("%c", deprint_bits((char *)g_stc.binary));
		c = deprint_bits((char *)g_stc.binary);
		if(c == '\0')
			ft_printf("\n");
		g_stc.i = 0;
		usleep(500);
		if (kill(info->si_pid, SIGUSR1) == -1)
		{
			ft_printf("ERROOR");
			exit (EXIT_FAILURE);
		}
	}
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
		{
			letter += j;
		}
		i++;
		j /= 2;
	}
	return (letter);
}

int	main(void)
{
	struct sigaction	sa_usr1;
	struct sigaction	sa_usr2;

	ft_printf("🔶 Salon: %d 🔶\n\n 🔹User41004: B!3nv3nu3 5ur M!n!t4|k🤖\n", getpid());
	sa_usr1.sa_flags = SA_SIGINFO;
	sa_usr1.sa_sigaction = signal_receive;
	sigemptyset(&sa_usr1.sa_mask);
	if (sigaction(SIGUSR1, &sa_usr1, NULL) == -1)
	{
		ft_printf("Erreur avec SIGUSR1\n");
		return (1);
	}
	sa_usr2.sa_flags = SA_SIGINFO;
	sa_usr2.sa_sigaction = signal_receive;
	sigemptyset(&sa_usr2.sa_mask);
	if (sigaction(SIGUSR2, &sa_usr2, NULL) == -1)
	{
		ft_printf("Erreur avec SIGUSR2\n");
		return (1);
	}
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
