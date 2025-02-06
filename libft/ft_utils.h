/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <joleksia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 08:11:58 by joleksia          #+#    #+#             */
/*   Updated: 2024/12/22 16:04:01 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

/* SECTION: Inclusions */
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef unsigned long long	t_ullong;

/* SECTION: Function declarations */
size_t	ft_printva(char c, va_list list);

size_t	ft_printchar(char c);
size_t	ft_printstring(const char *s);
size_t	ft_printint(int i);
size_t	ft_printuint(unsigned int u);
size_t	ft_printhex(unsigned int u, int lowercase);
size_t	ft_printptr(void *ptr);

char	*ft_utoa(unsigned int u);
char	*ft_utoa_base(unsigned int u, const char *base, int radix);
char	*ft_ltoa_base(unsigned long long u, const char *base, int radix);

#endif