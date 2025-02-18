/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:59:53 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/18 12:23:51 by lwillis          ###   ########.fr       */
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
	Frees all the strings in the list, then the list itself
*/
void	free_stringlist(char **list)
{
	int	i;

	i = -1;
	while (list[++i])
		free(list[i]);
	free(list);
}

void	copy_env_array(char **original, char ***copy)
{
	int	i;

	i = -1;
	while (original[++i])
		(*copy)[i] = ft_strdup(original[i]);
}

/*
	Creates a copy of the env vars so it can be freed later
*/
char	**init_env_array(char **envp)
{
	char	**env_vars;
	int		count;
	int		pos;
	char	*pwd;

	count = count_array(envp);
	env_vars = malloc(sizeof(char *) * (count + 1));
	if (!env_vars)
		return (NULL);
	copy_env_array(envp, &env_vars);
	env_vars[count] = NULL;
	pos = env_var_index("OLDPWD", env_vars);
	free(env_vars[pos]);
	pwd = getcwd(NULL, 0);
	env_vars[pos] = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	return (env_vars);
}

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

int	str_contains(char *str, char *set)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (set[++j])
		if (str[i] == set[j])
			return (1);
	}
	return (0);
}

// for export
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
