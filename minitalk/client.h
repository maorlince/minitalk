/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemerci <mlemerci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:37:39 by manon             #+#    #+#             */
/*   Updated: 2025/03/31 18:32:01 by mlemerci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
// basique
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// printf
# include <stdarg.h>
// minitalk
# include <signal.h>
# include <sys/types.h>

// printf
int				ft_printf(const char *format, ...);
int				ft_putadress(void *ptr);
int				ft_puthexadrr(unsigned long long n);
int				ft_format(va_list args, char c);
int				ft_putchar(char c);
int				ft_puthexa(unsigned int n, char format);
int				ft_putnbr(int n);
int				ft_putstr(const char *s);

//libft
int				ft_atoi(char *c);
char			*ft_strjoin(char const *s1, char s2);

// client
int				signal_sent(int pid, char c);

#endif