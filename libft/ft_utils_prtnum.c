/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_prtnum.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <joleksia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:41:04 by joleksia          #+#    #+#             */
/*   Updated: 2024/12/26 16:16:58 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include "./libft.h"
#include "ft_utils.h"

size_t	ft_printint(int i)
{
	char	*str;
	size_t	bytes;

	str = ft_itoa(i);
	if (!str)
		return (0);
	bytes = write(STDOUT_FILENO, str, ft_strlen(str));
	free(str);
	return (bytes);
}

size_t	ft_printuint(unsigned int u)
{
	char	*str;
	size_t	bytes;

	str = ft_utoa(u);
	if (!str)
		return (0);
	bytes = write(STDOUT_FILENO, str, ft_strlen(str));
	free(str);
	return (bytes);
}

size_t	ft_printhex(unsigned int u, int lowercase)
{
	char	*str;
	size_t	bytes;

	if (lowercase)
	{
		str = ft_utoa_base(u, "0123456789abcdef", 16);
		if (!str)
			return (0);
		bytes = write(STDOUT_FILENO, str, ft_strlen(str));
		free(str);
		return (bytes);
	}
	else
	{
		str = ft_utoa_base(u, "0123456789ABCDEF", 16);
		if (!str)
			return (0);
		bytes = write(STDOUT_FILENO, str, ft_strlen(str));
		free(str);
		return (bytes);
	}
}

size_t	ft_printptr(void *ptr)
{
	char	*str;
	size_t	bytes;
	size_t	addr;

	addr = (uintptr_t) ptr;
	if (!addr)
		return (write(STDOUT_FILENO, "(nil)", 5));
	bytes = write(STDOUT_FILENO, "0x", 2);
	str = ft_ltoa_base(addr, "0123456789abcdef", 16);
	if (!str)
		return (0);
	bytes += write(STDOUT_FILENO, str, ft_strlen(str));
	free(str);
	return (bytes);
}
