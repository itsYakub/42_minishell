/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:22:21 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 11:18:58 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char	*lw_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*result;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		result[i] = s2[i - len1];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	update_pwd(char **env_vars)
{
	int	pos;

	pos = env_var_pos("PWD=", env_vars);
	free(env_vars[pos]);	
	env_vars[pos]= lw_strjoin("PWD=", getcwd(NULL, 0));
}

void	ms_cd(char *new_dir, char *env_vars[])
{
	char	*path;
	int		pos;

	pos = env_var_pos("OLDPWD=", env_vars);
	free(env_vars[pos]);	
	env_vars[pos]= lw_strjoin("OLDPWD=", getcwd(NULL, 0));
	if (!new_dir)
	{
		path = env_var("HOME=", env_vars);
		chdir(path);
		update_pwd(env_vars);
		free(path);
	}
	else
	{
		chdir(new_dir);
		update_pwd(env_vars);
	}
}
