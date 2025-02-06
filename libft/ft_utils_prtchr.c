/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_prtchr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <joleksia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:42:26 by joleksia          #+#    #+#             */
/*   Updated: 2024/12/26 16:16:52 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include "./libft.h"

size_t	ft_printchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

size_t	ft_printstring(const char *s)
{
	if (!s)
		return (write(STDOUT_FILENO, "(null)", 6));
	return (write(STDOUT_FILENO, s, ft_strlen(s)));
}
