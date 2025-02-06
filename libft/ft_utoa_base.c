/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <joleksia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 08:12:29 by joleksia          #+#    #+#             */
/*   Updated: 2024/12/26 16:16:17 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include "./libft.h"

static unsigned int	fts_numlen(unsigned int n, int radix);
static char			*fts_strprc(char *s, unsigned int n, const char *b, int r);
static char			*fts_strrev(char *s, size_t len);

char	*ft_utoa_base(unsigned int u, const char *base, int radix)
{
	char	*result;
	size_t	nlen;

	nlen = fts_numlen(u, radix);
	result = (char *) ft_calloc(nlen + 1, sizeof(char));
	if (!result)
		return (NULL);
	result = fts_strprc(result, u, base, radix);
	return (result);
}

static unsigned	int	fts_numlen(unsigned int n, int radix)
{
	int	result;

	result = 1;
	while (n)
	{
		n /= radix;
		if (n)
			result++;
	}
	return (result);
}

static char	*fts_strprc(char *s, unsigned int n, const char *b, int r)
{
	char	*scpy;

	scpy = s;
	if (n == 0)
		*s++ = '0';
	while (n)
	{
		*s++ = b[n % r];
		n /= r;
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
