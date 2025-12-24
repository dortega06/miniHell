/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:38:07 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/13 19:29:04 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redir_in(t_lexer *tmp, t_parser **cmd_node)
{
	int	fd;

	fd = open(tmp->next->data, O_RDONLY);
	if (fd == -1)
		printf("minishell: %s: %s\n", tmp->next->data, strerror(errno));
	(*cmd_node)->redir_in = fd;
}

void	ft_redir_out(t_lexer *tmp, t_parser **cmd_node)
{
	int	fd;

	fd = open(tmp->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		printf("minishell: %s:  %s\n", tmp->next->data, strerror(errno));
	(*cmd_node)->redir_out = fd;
}

void	ft_append(t_lexer *tmp, t_parser **cmd_node)
{
	int	fd;

	fd = open(tmp->next->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		printf("minishell: %s: %s\n", tmp->next->data, strerror(errno));
	(*cmd_node)->redir_out = fd;
}

void	ft_heardoc(t_lexer *tmp, t_parser **cmd_node, t_shell *msh)
{
	int		fd;
	char	*delimiter;
	int		had_quotes;

	had_quotes = ft_has_quotes(tmp->next->data);
	delimiter = ft_remove_quotes(tmp->next->data);
	fd = ft_heredoc(delimiter, ! had_quotes, msh);
	free(delimiter);
	if (fd == -2)
	{
		(*cmd_node)->redir_in = -1;
		msh->exit_status = 130;
		return ;
	}
	(*cmd_node)->redir_in = fd;
}
