/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:16:37 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/08 08:32:41 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../libft/libft.h"
#include "../minishell.h"

void	cmd_process(t_cmd *cmd, char *envp[])
{
	int	pid;
	int	p_fd[2];

	if (-1 == pipe(p_fd))
		show_error("Pipe error!\n", 1);
	pid = fork();
	if (-1 == pid)
		show_error("Fork error!\n", 1);
	if (0 == pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], cmd->fd1);
		do_cmd(*cmd, envp);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], cmd->fd0);
		waitpid(pid, NULL, 0);
	}
}

