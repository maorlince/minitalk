/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manon <manon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:24:54 by manon             #+#    #+#             */
/*   Updated: 2025/02/27 12:09:29 by manon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
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
// server
void			signal_receive(int signum, siginfo_t *info, void *context);
unsigned char	deprint_bits(char *binary);

// client
int				ft_atoi(char *c);
char			*print_bits(unsigned char letter);
int				signal_send(int pid, char *binary);

#endif