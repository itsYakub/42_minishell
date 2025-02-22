/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:51:55 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/22 13:42:52 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Replaces an existing var value, but only if a new value is passed
*/
static void	update_var(int pos, char *var, t_mini *mini)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (var[++i])
		if ('=' == var[i])
			count++;
	if (0 == count)
		return ;
	free(mini->env[pos]);
	mini->env[pos] = ft_strdup(var);
}

/*
	Adds a new var and optional value
*/
static int	add_var(char *var, t_mini *mini)
{
	int		count;
	char	**copy;

	count = count_array(mini->env);
	if (-1 == count)
		return (1);
	copy = malloc(sizeof(char *) * (count + 2));
	if (!copy)
		return (1);
	copy_env_array(mini->env, &copy);
	copy[count] = ft_strdup(var);
	copy[count + 1] = NULL;
	ft_free2d((void **) mini->env);
	mini->env = copy;
	return (0);
}

// Capital letters first
static void	sort_and_display(char **env)
{
	int		i;
	int		j;
	int		printed_equals;

	i = -1;
	while (env[++i])
	{
		if (0 == ft_strncmp("_=", env[i], 2))
			continue ;
		write(1, "declare -x ", 11);
		j = -1;
		printed_equals = 0;
		while (env[i][++j])
		{
			write(1, &env[i][j], 1);
			if ('=' == env[i][j] && 0 == printed_equals)
				printed_equals = write(1, "\"", 1);
			if (j == ft_strlen(env[i]) - 1 && 1 == printed_equals)
				write(1, "\"", 1);
		}
		if ('\n' != env[i][j])
			write(1, "\n", 1);
	}
	ft_free2d((void **)env);
}

/*
	Checks if the var value is acceptable
*/
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
	Replicates the export command.
	Should not show the _ var
	No args lists all vars
	export name adds an empty var
	export name=value adds/updates a var
*/
void	ms_export(t_command *cmd)
{
	int		cmd_count;
	int		i;
	int		pos;
	char	**split;

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
		split = ft_split(cmd->args[i], '=');
		pos = env_var_index(split[0], cmd->mini->env);
		if (-1 == pos)
			add_var(cmd->args[i], cmd->mini);
		else
			update_var(pos, cmd->args[i], cmd->mini);
		ft_free2d((void **) split);
	}
}
