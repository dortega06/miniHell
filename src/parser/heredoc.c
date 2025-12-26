/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:23:23 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/26 13:14:34 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_expand_line(char *line, t_shell *msh)
{
	char	*result;
	int		i;

	if (!line || !ft_strchr(line, '$'))
		return (ft_strdup(line));
	result = ft_strdup(line);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$')
			process_data(&result, msh);
		i++;
	}
	return (result);
}

static char	*process_heredoc_line(char *line, int should_expand, t_shell *msh)
{
	char	*tmp;

	if (should_expand)
	{
		tmp = ft_expand_line(line, msh);
		free(line);
		return (tmp);
	}
	return (line);
}

static void	heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

static int	read_lines(int fd, char *delimiter,
	int should_expand, t_shell *msh)
{
	char	*line;

	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (ft_heredoc_eof_warning(delimiter));
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (0);
		}
		line = process_heredoc_line(line, should_expand, msh);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

static int	ft_heredoc_child_process(int *fd, char *delimiter,
	int should_expand, t_shell *msh)
{
	int	status;

	close(fd[0]);
	status = read_lines(fd[1], delimiter, should_expand, msh);
	close(fd[1]);
	exit(status);
}

int	ft_heredoc(char *delimiter, int should_expand, t_shell *msh)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		ft_heredoc_child_process(fd, delimiter, should_expand, msh);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &status, 0);
	setup_signals(S_BASE);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(fd[0]);
		g_signal = S_SIGINT_CMD;
		return (-2);
	}
	return (fd[0]);
}
/*
int	ft_heredoc(char *delimiter, int should_expand, t_shell *msh)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		status = read_heredoc_lines(fd[1], delimiter, should_expand, msh);
		close(fd[1]);
		exit(status);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &status, 0);
	setup_signals(S_BASE);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(fd[0]);
		g_signal = S_SIGINT_CMD;
		return (-2);
	}
	return (fd[0]);
}*/
