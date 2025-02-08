/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:51:55 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/08 15:01:53 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_var(char *var_name, char *var_val, t_cmd *cmd)
{
	char	*temp;
	int		pos;

	pos = env_var_index(var_name, cmd->mini->env);
	free(cmd->mini->env[pos]);
	cmd->mini->env[pos] = ft_strjoin(var_name, "=");
	temp = ft_strjoin(cmd->mini->env[pos], var_val);
	free(cmd->mini->env[pos]);
	cmd->mini->env[pos] = ft_strdup(temp);
	free(temp);
}

static void	add_var(char *var_name, char *var_val, t_cmd *cmd)
{
	int		count;
	char	**copy;
	char	*temp;

	count = count_array(cmd->mini->env);
	if (-1 == count)
		return ;
	copy = malloc(sizeof(char *) * (count + 2));
	if (!copy)
		return ;
	copy_env_array(cmd->mini->env, &copy);
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
	free_stringlist(cmd->mini->env);
	cmd->mini->env = copy;
}

// capital letters first
static void	sort_and_display(char **env, int fd)
{
	int	i;
	int	len;

	i = -1;
	while (env[++i])
	{
		if (0 == ft_strncmp("_=", env[i], 2))
			continue ;
		ft_putstr_fd(env[i], fd);
		len = ft_strlen(env[i]);
		if ('\n' != env[i][len - 1])
			ft_putstr_fd("\n", fd);
	}
}

static void	sort_vars(t_cmd *cmd)
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
	sort_and_display(output, cmd->fd1);
	free_stringlist(output);
}

/*
	Emulates the export command.
	Should not show the _ var
	No args lists all vars
	export name adds and empty var
	export name=value adds a var
*/
void	ms_export(t_cmd *cmd)
{
	int		cmd_count;
	char	**split;
	int		i;

	cmd_count = count_array(cmd->cmd);
	if (1 == cmd_count)
	{
		sort_vars(cmd);
		return ;
	}
	i = 0;
	while (cmd->cmd[++i])
	{
		split = ft_split(cmd->cmd[i], '=');
		if (!env_var(split[0], cmd->mini->env))
			add_var(split[0], split[1], cmd);
		else
			update_var(split[0], split[1], cmd);
		free_stringlist(split);
	}
}
