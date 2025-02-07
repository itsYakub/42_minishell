/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:51:55 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 16:49:53 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_var(char *var_name, char *var_val, t_mini *mini)
{
	char	*temp;
	int		pos;

	pos = env_var_pos(var_name, mini->env);
	free(mini->env[pos]);
	mini->env[pos] = ft_strjoin(var_name, "=");
	temp = ft_strjoin(mini->env[pos], var_val);
	free(mini->env[pos]);
	mini->env[pos] = ft_strdup(temp);
	free(temp);
}

static void	add_var(char *var_name, char *var_val, t_mini *mini)
{
	int		count;
	char	**copy;
	char	*temp;

	count = count_array(mini->env);
	if (-1 == count)
		return ;
	copy = malloc(sizeof(char *) * count + 2);
	if (!copy)
		return ;	
	copy_env_array(mini->env, &copy);
	if (!var_val)
		copy[count] = ft_strjoin(var_name, "=''");
	else
	{
		copy[count] = ft_strjoin(var_name, "=");
		temp = ft_strjoin(copy[count], var_val);
		free(copy[count]);
		copy[count] = ft_strdup(temp);
		free(temp);
	}	
	copy[count + 1] = NULL;
	free_stringlist(mini->env);
	mini->env = copy;
}

// capital letters first
static void	sort_and_display(t_mini *mini)
{
	int	i;
	int	len;
	
	i = -1;
	while (mini->env[++i])
	{
		ft_putstr_fd(mini->env[i], mini->cmd->fd1);
		len = ft_strlen(mini->env[i]);
		if ('\n' != mini->env[i][len - 1])
			ft_putstr_fd("\n", mini->cmd->fd1);
	}
}

void	ms_export(t_mini *mini)
{
	int		cmd_count;
	char	**split;
	int		i;
	int		len;

	cmd_count = count_array(mini->cmd->cmd);
	if (1 == cmd_count)
	{
		sort_and_display(mini);
		return ;
	}
	i = 0;
	while (mini->cmd->cmd[++i])
	{
		split = ft_split(mini->cmd->cmd[i], '=');
		if (!env_var(split[0], mini->env))
			add_var(split[0], split[1], mini);
		else
			update_var(split[0], split[1], mini);
		free_stringlist(split);
	}
}
