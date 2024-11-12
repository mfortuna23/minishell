/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:10:11 by mfortuna          #+#    #+#             */
/*   Updated: 2024/10/28 11:02:31 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_fprintnbr (long n, char *str, int base, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * -1;
	}
	if (n >= base)
	{
		ft_fprintnbr(n / base, str, base, fd);
		ft_fprintnbr(n % base, str, base, fd);
	}
	else
		ft_putchar_fd(str[n], fd);
}

void ft_fnbr(const char *s, va_list args, int fd)
{
	unsigned long n;

	if (*s == 'd' || *s == 'i')
		return (ft_fprintnbr((long)va_arg(args, int), "0123456789", 10, fd));
	if (*s == 'u')
		return (ft_fprintnbr((long)va_arg(args, unsigned int), "0123456789", 10, fd));
	if (*s == 'x')
		return (ft_fprintnbr((long)va_arg(args, unsigned int), "0123456789abcdef", 16, fd));
	if (*s == 'X')
		return (ft_fprintnbr((long)va_arg(args, unsigned int), "0123456789ABCDEF", 16, fd));
	if (*s == 'p')
	{
		n = va_arg (args, unsigned long);
		if (!n)
			return (ft_putstr_fd("(nil)", fd));
		ft_putchar_fd('0', fd);
		ft_putchar_fd('x', fd);
		return (ft_fprintnbr((long)va_arg(args, unsigned int), "0123456789abcdef", 16, fd));	
	}

}

void ft_fsign(const char *s, va_list args, int fd)
{
	char	*str;

	if (*s == 'd' || *s == 'i' || *s == 'u' || *s == 'x' \
	|| *s == 'X' || *s == 'p')
		return (ft_fnbr(s, args, fd));
	else if (*s == 'c')
		return (ft_putchar_fd(va_arg(args, int), fd));
	else if (*s == 's')
	{
		str = (va_arg(args, char *));
		if (!str)
			return (ft_putstr_fd("(null)", fd));
		return (ft_putstr_fd(str, fd));
	}
	else if (*s == '%')
		return (ft_putchar_fd('%', fd));
	ft_putchar_fd('%', fd);
	ft_putchar_fd(*s, fd);
}

int	ft_fprintf(int fd, int r_value, const char *s, ...)
{
	va_list args;

	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
			ft_fsign(++s, args, fd);
		else
			ft_putchar_fd(*s, fd);
		s++;
	}
	return (r_value);
}