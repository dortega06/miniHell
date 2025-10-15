/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:23:23 by dortega-          #+#    #+#             */
/*   Updated: 2025/10/15 19:37:47 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_heredoc_loop(char *limit, int fd)
{
	char	*line;

	while (1)
	{
		line = readline(HEREDOC_MSG);
		if (!line || (!ft_strncmp(limit, line, ft_strlen(limit))
				&& !ft_strncmp(limit, line, ft_strlen(line))))
			exit(EXIT_SUCCESS);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		ft_memfree(line);
	}
}


