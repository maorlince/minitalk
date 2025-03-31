/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:37:44 by manon             #+#    #+#             */
/*   Updated: 2025/03/28 19:47:15 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
// basique
# define _POSIX_SOURCE 1
# define _POSIX_C_SOURCE 199309L
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
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
void			*ft_calloc(size_t elementCount, size_t elementSize);
char			*ft_strdup(const char *src);

// server
void			signal_receive(int signum, siginfo_t *info, void *context);
unsigned char	deprint_bits(char *binary);
void			stock_message(char c, pid_t n, siginfo_t *info);

#endif