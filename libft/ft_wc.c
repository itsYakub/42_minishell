/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:41:52 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/19 09:35:14 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wc(const char *s, char *delim)
{
	int	res;

	if (!s || !*s)
		return (0);
	res = 0;
	while (*s)
	{
		while (*s && ft_strchr(delim, *s))
			s++;
		if (*s && !ft_strchr(delim, *s))
			res++;
		while (*s && !ft_strchr(delim, *s))
			s++;
	}
	return (res);
}
