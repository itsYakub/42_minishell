#include "minishell.h"

void	show_error(char *error, int error_code)
{
	write(2, error, ft_strlen(error));
	if (0 != error_code)
		exit (error_code);
}

static void	free_split(char **split_str)
{
	int	i;

	i = 0;
	while (split_str[i])
		free(split_str[i++]);
	free(split_str);
}

static char	*make_path(char *command, char *path)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path, "/");
	tmp2 = ft_strjoin(tmp, command);
	free(tmp);
	if (0 == access(tmp2, F_OK | X_OK))
		return (tmp2);
	free(tmp2);
	return (NULL);
}

static char	*extract_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (0 == ft_strncmp("PATH", envp[i], 4))
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

int	do_cmd(t_cmd *cmd, char *envp[])
{
	char	**split_path;
	char	*path;
	char	*tmp_path;
	int		i;

	if (0 == ft_strcmp("exit", cmd->args[0]))
	{
		//ms_env(cmd);
		ms_exit(cmd);
		exit(127);
	}

	path = extract_path(envp);
	if (!path)
		show_error("PATH not found!\n", 1);
	if (0 == access(cmd->args[0], F_OK | X_OK))
		return (execve(cmd->args[0], cmd->args, envp));
	i = 0;
	split_path = ft_split(path, ':');
	while (split_path[i])
	{
		tmp_path = make_path(cmd->args[0], split_path[i]);
		if (tmp_path)
			return (execve(tmp_path, cmd->args, envp));
		i++;
	}
	free_split(split_path);
	show_error("command not found\n", 127);
	return (1);
}

static void	cmd_process(t_cmd *cmd, char *envp[])
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
		close(p_fd[1]);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
		close(p_fd[0]);
	}
}

int	pipe_test(t_mini *mini)
{
	int	inputfd;
	int	outputfd;
	int	i;
	int	len;

	inputfd = 0;
	outputfd = 1;
	dup2(inputfd, 0);
	len = mini->cmdc;
	i = 0;
	while (i < len - 1)
	{
		cmd_process(&mini->cmd[i], mini->env);
		i++;
	}
	dup2(outputfd, 1);
	do_cmd(&mini->cmd[len - 1], mini->env);
	return (0);
}
