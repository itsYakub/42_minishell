/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:50:36 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/06 10:28:38 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split(char const *s, char c)
{
	char	**warr;
	int		tlen;
	int		i;

	warr = (char **) malloc((ft_wc(s, &c) + 1) * sizeof(char *));
	if (!warr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (ft_strchr(s, c))
				tlen = ft_strchr(s, c) - s;
			else if (!ft_strchr(s, c))
				tlen = ft_strlen(s);
			warr[i++] = ft_substr(s, 0, tlen);
			s += tlen;
		}
	}
	warr[i] = NULL;
	return (warr);
}
