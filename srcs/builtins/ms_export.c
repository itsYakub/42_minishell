/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:51:55 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/18 12:24:11 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Replaces an existing var value, but only if a new value is passed
*/
static void	update_var(int pos, char *var_name, char *var_val, t_command *cmd)
{
	char	*temp;

	free(cmd->mini->env[pos]);
	if (var_val)
	{
		cmd->mini->env[pos] = ft_strjoin(var_name, "=");
		temp = ft_strjoin(cmd->mini->env[pos], var_val);
		free(cmd->mini->env[pos]);
		cmd->mini->env[pos] = ft_strdup(temp);
		free(temp);
	}
	else
		cmd->mini->env[pos] = ft_strdup(var_name);
}

/*
	Adds a new var and optional value
*/
static int	add_var(char *var_name, char *var_val, t_command *cmd)
{
	int		count;
	char	**copy;
	char	*temp;

	count = count_array(cmd->mini->env);
	if (-1 == count)
		return (1);
	copy = malloc(sizeof(char *) * (count + 2));
	if (!copy)
		return (1);
	copy_env_array(cmd->mini->env, &copy);
	if (!var_val)
		copy[count] = ft_strdup(var_name);
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
	return (0);
}

// Capital letters first
static void	sort_and_display(char **env)
{
	int		i;
	int		len;
	char	**split;

	i = -1;
	while (env[++i])
	{
		if (0 == ft_strncmp("_=", env[i], 2))
			continue ;
		split = lw_split(env[i], '=');
		printf("declare -x %s", split[0]);
		if (split[1])
			printf("=\"%s\"", split[1]);
		free_stringlist(split);
		len = ft_strlen(env[i]);
		if ('\n' != env[i][len - 1])
			printf("\n");
	}
	free_stringlist(env);
}

static int	is_invalid_identifier(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
	{
		if (str_disallowed(cmd->args[i]))
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd("'", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			cmd->mini->exitcode = 1;
			return (1);
		}
	}
	return (0);
}

/*
	Emulates the export command.
	Should not show the _ var
	No args lists all vars
	export name adds an empty var
	export name=value adds a var
*/
void	ms_export(t_command *cmd)
{
	int		cmd_count;
	char	**split;
	int		i;
	int		pos;

	cmd_count = count_array(cmd->args);
	if (1 == cmd_count)
	{
		sort_and_display(sort_vars(cmd));
		return ;
	}
	i = 0;
	if (1 == is_invalid_identifier(cmd))
		return ;
	while (cmd->args[++i])
	{
		split = lw_split(cmd->args[i], '=');
		pos = env_var_index(split[0], cmd->mini->env);
		if (-1 == pos)
			cmd->mini->exitcode = add_var(split[0], split[1], cmd);
		else if (split[1])
			update_var(pos, split[0], split[1], cmd);
		free_stringlist(split);
	}
}
