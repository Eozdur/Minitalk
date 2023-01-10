/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <ozduremre06@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:12:26 by eozdur            #+#    #+#             */
/*   Updated: 2023/01/09 10:12:29 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check(char c, va_list arg)
{
	int	p;

	p = 0;
	if (c == 'c')
		p += ft_putchar(va_arg(arg, int));
	else if (c == 's')
		p += ft_putstr(va_arg(arg, char *));
	else if (c == 'd' || c == 'i')
		p += ft_putnbr(va_arg(arg, int));
	else if (c == 'u')
		p += ft_u(va_arg(arg, unsigned int));
	else if (c == 'x')
		p += ft_x(va_arg(arg, unsigned int), 0);
	else if (c == 'X')
		p += ft_x(va_arg(arg, unsigned int), 1);
	else if (c == 'p')
	{
		p += ft_putstr("0x");
		p += ft_p(va_arg(arg, unsigned long));
	}
	else if (c == '%')
		p += ft_putchar('%');
	else
		return (ft_putchar(c));
	return (p);
}

int	ft_printf(const char *s, ...)
{
	va_list	arg;
	int		i;
	int		j;

	va_start(arg, s);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '%')
		{
			ft_putchar(s[i]);
			j++;
		}
		if (s[i] == '%')
		{
			i++;
			while (s[i] == ' ' && s[i])
				i++;
			j += ft_check(s[i], arg);
		}
		i++;
	}
	va_end(arg);
	return (j);
}
