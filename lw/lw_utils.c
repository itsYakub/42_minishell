/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lw_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:59:53 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/14 15:09:46 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Appends a string to a string, freeing the old one
*/
char	*join_and_free(char *old, char *new)
{
	char	*tmp;

	if (!old)
		old = ft_strdup("");
	tmp = ft_strjoin(old, new);
	free(new);
	free(old);
	return (tmp);
}

/*
	Appends a char to a string, freeing the old one
*/
char	*add_char_and_free(char *old, char new)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!old)
		old = ft_strdup("");
	tmp = malloc(ft_strlen(old) + 2);
	while (old[++i])
		tmp[i] = old[i];
	tmp[i] = new;
	tmp[i + 1] = '\0';
	free(old);
	return (tmp);
}
