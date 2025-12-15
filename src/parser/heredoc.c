/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:23:23 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/15 17:18:25 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_has_quotes(char *str)
{
	if (!str || !str[0])
		return (0);
	return (str[0] == '"' || str[0] == '\'');
}

char	*ft_remove_quotes(char *str)
{
	int		len;
	char	*result;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') || \
		(str[0] == '\'' && str[len - 1] == '\'')))
	{
		result = ft_substr(str, 1, len - 2);
		return (result);
	}
	return (ft_strdup(str));
}

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

int	ft_heredoc(char *delimiter, int should_expand, t_shell *msh)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		line = process_heredoc_line(line, should_expand, msh);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}
