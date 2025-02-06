/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <joleksia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 08:12:07 by joleksia          #+#    #+#             */
/*   Updated: 2024/12/26 16:16:27 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./libft.h"
#include "ft_utils.h"

static size_t	fts_print_format(const char **s, const char *f, va_list l);
static size_t	fts_print_string(const char **s);

int	ft_printf(const char *s, ...)
{
	va_list		list;
	char		*format;
	size_t		bytes;

	format = "cspdiuxX%";
	va_start(list, s);
	bytes = 0;
	while (*s)
	{
		if (*s == '%')
			bytes += fts_print_format(&s, format, list);
		else
			bytes += fts_print_string(&s);
	}
	va_end(list);
	return ((int) bytes);
}

static size_t	fts_print_format(const char **s, const char *f, va_list l)
{
	size_t	bytes;

	if (ft_strchr(f, *(*s + 1)))
	{
		bytes = ft_printva(*(*s + 1), l);
		*s += 2;
	}
	else
	{
		bytes = write(STDOUT_FILENO, *s, 2);
		*s += 2;
	}
	return (bytes);
}

static size_t	fts_print_string(const char **s)
{
	size_t	bytes;
	size_t	offset;

	if (!ft_strchr(*s, '%'))
		offset = ft_strlen(*s);
	else
		offset = ft_strchr(*s, '%') - *s;
	bytes = write(STDOUT_FILENO, *s, offset);
	*s += offset;
	return (bytes);
}
