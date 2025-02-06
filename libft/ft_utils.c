/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <joleksia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 08:11:48 by joleksia          #+#    #+#             */
/*   Updated: 2024/12/14 15:26:42 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

size_t	ft_printva(char c, va_list list)
{
	if (c == 'c')
		return (ft_printchar((char) va_arg(list, int)));
	else if (c == '%')
		return (ft_printchar('%'));
	else if (c == 's')
		return (ft_printstring(va_arg(list, const char *)));
	else if (c == 'i' || c == 'd')
		return (ft_printint(va_arg(list, int)));
	else if (c == 'u')
		return (ft_printuint(va_arg(list, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_printhex((unsigned int) va_arg(list, int), c == 'x'));
	else if (c == 'p')
		return (ft_printptr(va_arg(list, void *)));
	return (0);
}
