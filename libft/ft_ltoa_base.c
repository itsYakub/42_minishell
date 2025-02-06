/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <joleksia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 08:12:22 by joleksia          #+#    #+#             */
/*   Updated: 2024/12/26 16:16:07 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include "./libft.h"

static size_t	fts_numlen(t_ullong n, int radix);
static char		*fts_strprc(char *s, t_ullong n, const char *b, int r);
static char		*fts_strrev(char *s, size_t len);

char	*ft_ltoa_base(unsigned long long u, const char *base, int radix)
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

static size_t	fts_numlen(t_ullong n, int radix)
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

static char	*fts_strprc(char *s, t_ullong n, const char *b, int r)
{
	char	*scpy;

	scpy = s;
	if (n == 0)
	{
		*s++ = '0';
		return (scpy);
	}
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
