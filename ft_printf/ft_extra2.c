/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extra2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozdur <ozduremre06@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:12:32 by eozdur            #+#    #+#             */
/*   Updated: 2023/01/09 10:14:12 by eozdur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_u(unsigned int u)
{
	int	i;

	i = 0;
	if (u <= 9)
		i += ft_putchar(u + '0');
	else
	{
		i += ft_u(u / 10);
		i += ft_u(u % 10);
	}
	return (i);
}

int	ft_p(unsigned long p)
{
	int	i;

	i = 0;
	if (p >= 16)
		i += ft_p(p / 16);
	if ((p % 16) < 10)
		i += ft_putchar((p % 16) + '0');
	else
		i += ft_putchar((p % 16) + 87);
	return (i);
}

int	ft_x(unsigned int x, int b)
{
	int	i;

	i = 0;
	if (x >= 16)
		i += ft_x(x / 16, b);
	if ((x % 16) < 10)
		i += ft_putchar((x % 16) + '0');
	else
	{
		if (b == 0)
			i += ft_putchar((x % 16) + 87);
		else
			i += ft_putchar((x % 16) + 55);
	}
	return (i);
}
