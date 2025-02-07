/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:22:21 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 15:19:51 by lwillis          ###   ########.fr       */
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

void	update_pwd(t_mini *mini)
{
	int	pos;

	pos = env_var_pos("PWD=", mini->env);
	free(mini->env[pos]);	
	mini->env[pos]= lw_strjoin("PWD=", getcwd(NULL, 0));
}

void	ms_cd(t_mini *mini)
{
	char	*path;
	int		pos;

	pos = env_var_pos("OLDPWD=", mini->env);
	free(mini->env[pos]);	
	mini->env[pos]= lw_strjoin("OLDPWD=", getcwd(NULL, 0));
	if (!mini->cmd->cmd[1])
	{
		path = env_value("HOME", mini->env);
		chdir(path);
		update_pwd(mini);
		free(path);
	}
	else
	{
		chdir(mini->cmd->cmd[1]);
		update_pwd(mini);
	}
}
