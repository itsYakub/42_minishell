/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:59:53 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/20 09:57:09 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/*
	Sorts the env vars alphabetically. Used by ms_export
*/
char	**sort_vars(t_command *cmd)
{
	char	**output;
	int		count;
	int		i;
	int		j;
	char	*tmp;

	count = count_array(cmd->mini->env);
	output = init_env_array(cmd->mini->env);
	i = -1;
	while (++i < count -1)
	{
		j = i;
		while (++j < count)
		{
			if (ft_strcmp(output[i], output[j]) > 0)
			{
				tmp = output[i];
				output[i] = output[j];
				output[j] = tmp;
			}
		}
	}
	return (output);
}

// Checks if a var value is not allowed. Used by ms_export
int	str_disallowed(char *str)
{
	int	i;

	if (!(ft_isalpha(str[0]) || '_' == str[0]))
		return (1);
	i = -1;
	while (str[++i])
	{
		if (ft_isalnum(str[i]) || '=' == str[i])
			continue ;
		return (1);
	}
	return (0);
}

/*
	Checks that the input has at least one printable character
*/
int	is_unprintable(char *str)
{
	int	i;
	int	no_chars;

	i = -1;
	no_chars = 1;
	while (str[++i])
	{
		if (str[i] > 32 && str[i] < 127)
			no_chars = 0;
	}
	return (no_chars);
}
