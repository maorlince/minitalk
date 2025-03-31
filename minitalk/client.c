/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:59:26 by manon             #+#    #+#             */
/*   Updated: 2025/03/31 16:55:28 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t	confirmed = 0;

static void	confirmation_handler(int signum)
{
	if (signum == SIGUSR1)
		confirmed = 1;
	else if (signum == SIGUSR2)
	{
		ft_printf("[Message sent]");
		exit(0);
	}
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

int	signal_send(int pid, char c)
{
	// int	i;
// 
	// i = 0;
	// while (binary[i])
	// {
		// if (binary[i] == '0')
		// {
			// if (kill(pid, SIGUSR1) == -1)
				// return (-1);
		// }
		// else if (binary[i] == '1')
		// {
			// if (kill(pid, SIGUSR2) == -1)
				// return (-1);
		// }
		// else
			// return (-1);
		// i++;
		// confirmed = 0;
		// while (!confirmed)
			// usleep(10);
	// }
	//  return (0);
	int    i;

    i = 7;
    while (i >= 0)
    {
        if (((c >> i) & 1) == 0)
        {
            kill(pid, SIGUSR1);
        }
        if (((c >> i) & 1) == 1)
        {
            kill(pid, SIGUSR2);
        }
        confirmed = 0;
        while (!confirmed)
        {
            usleep(50);
        }
        i--;
    }
	return 0;
}

int	main(int argc, char **argv)
{
	int		i;
	// char	*binary;
	int		server_pid;

	if (argc != 3)
		return (1);
	ft_printf("🔸Logged in as: User%d \n", getpid());
	server_pid = ft_atoi(argv[1]);
	signal(SIGUSR1, confirmation_handler);
	signal(SIGUSR2, confirmation_handler);

	i = 0;
	while (argv[2][i])
	{
		// binary = print_bits(argv[2][i]);
		// if (!binary)
			// return (1);
		if (signal_send(server_pid, argv[2][i]) == -1)
			return (ft_printf("[Mauvais PID]\n"));
	//confirmed = 0;
		// free(binary);
	//while (!confirmed)
	//usleep(100);
		i++;
	}
	// binary = print_bits('\0');
	signal_send(server_pid, 0);
	// free(binary);
	confirmed = 0;
	while (!confirmed)
		pause();
	ft_printf("[Message recu]\n");
	return (EXIT_SUCCESS);
}
