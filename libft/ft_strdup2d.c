/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:12:23 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/06 15:18:18 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup2d(char **ptr, size_t index, size_t count)
{
	size_t	iter;
	char	**arr;

	arr = ft_calloc(count, sizeof(char *));
	iter = -1;
	while (++iter < count)
		arr[iter] = ft_strdup(ptr[index + iter]);
	return (arr);
}
