/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <joleksia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 08:11:36 by joleksia          #+#    #+#             */
/*   Updated: 2024/12/26 16:16:36 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include "./libft.h"

static int	fts_numlen(unsigned int n);
static char	*fts_strproc(char *s, unsigned int n);
static char	*fts_strrev(char *s, size_t len);

char	*ft_utoa(unsigned int u)
{
	char	*result;

	result = (char *) ft_calloc(fts_numlen(u) + 1, sizeof(char));
	if (!result)
		return (NULL);
	result = fts_strproc(result, u);
	return (result);
}

static int	fts_numlen(unsigned int n)
{
	int	result;

	result = 1;
	while (n)
	{
		n /= 10;
		if (n)
			result++;
	}
	return (result);
}

static char	*fts_strproc(char *s, unsigned int n)
{
	char	*scpy;

	scpy = s;
	if (n == 0)
		*s++ = '0';
	while (n)
	{
		*s++ = n % 10 + '0';
		n /= 10;
	}
	return (fts_strrev(scpy, ft_strlen(scpy)));
}

static char	*fts_strrev(char *s, size_t len)
{
	size_t	i;
	char	temp;

	i = -1;
	while (++i < len / 2)
	{
		temp = s[i];
		s[i] = s[len - 1 - i];
		s[len - 1 - i] = temp;
	}
	return (s);
}
