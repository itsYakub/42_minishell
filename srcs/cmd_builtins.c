/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:40:53 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/20 14:32:56 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Diverts the command to use out version instead of the system one
*/
void	msh_exec_builtin(t_command *cmd)
{
	if (!ft_strncmp("pwd", *cmd->args, ft_strlen(*cmd->args)))
		ms_pwd(cmd);
	else if (!ft_strncmp("cd", *cmd->args, ft_strlen(*cmd->args)))
		ms_cd(cmd);
	else if (!ft_strncmp("exit", *cmd->args, ft_strlen(*cmd->args)))
		ms_exit(cmd);
	else if (!ft_strncmp("env", *cmd->args, ft_strlen(*cmd->args)))
		ms_env(cmd);
	else if (!ft_strncmp("export", *cmd->args, ft_strlen(*cmd->args)))
		ms_export(cmd);
	else if (!ft_strncmp("echo", *cmd->args, ft_strlen(*cmd->args)))
		ms_echo(cmd);
	else if (!ft_strncmp("unset", *cmd->args, ft_strlen(*cmd->args)))
		ms_unset(cmd);
}

/*
	Checks if the command is one we need to handle with our implementation
*/
int	msh_isbuiltin(t_command *cmd)
{
	if (!cmd->args[0] || 0 == ft_strlen(cmd->args[0]))
		return (0);
	return (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0]))
		|| !ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0]))
		|| !ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0]))
		|| !ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0]))
		|| !ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0]))
		|| !ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0]))
		|| !ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0]))
	);
}
