/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:16:37 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/07 17:17:35 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../libft/libft.h"

void	cmd_process(char *cmd, char *envp[])
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
		dup2(p_fd[1], 1);
		do_cmd(cmd, envp);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		waitpid(pid, NULL, 0);
	}
}

