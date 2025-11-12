/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:15:25 by dortega-          #+#    #+#             */
/*   Updated: 2025/11/12 11:45:23 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_fill_node(t_lexer *lex, t_parser **cmd_node, int start, int end)
{
	t_lexer	*tmp;

	tmp = lex;
	(*cmd_node)->redir_in = STDIN_FILENO;
	(*cmd_node)->redir_out = STDOUT_FILENO;
	fill_redir(lex, cmd_node, &start, end);
	while (tmp && tmp->index != start)
		tmp = tmp->next;
	fill_cmd(tmp, cmd_node);
}

void	ft_redirect(t_lexer *tmp, t_parser **cmd_node)
{
	int	fd;

	if (tmp->type == T_REDIR_IN)
	{
		fd = open(tmp->next->data, O_RDONLY);
		(*cmd_node)->redir_in = fd;
	}
	else if (tmp->type == T_REDIR_OUT)
	{
		fd = open(tmp->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		(*cmd_node)->redir_out = fd;
	}
	else if (tmp->type == T_APPEND)
	{
		fd = open(tmp->next->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
		(*cmd_node)->redir_out = fd;
	}
	else if (tmp->type == T_HEREDOC)
	{
		fd = ft_heredoc(tmp->next->data);
		(*cmd_node)->redir_in = fd;
		if (g_signal != S_CANCEL_EXEC)
			g_signal = S_BASE;
	}
}

void	fill_cmd(t_lexer *tmp, t_parser **cmd_node)
{
	int	len;

	len = ft_len_cmd(tmp);
	(*cmd_node)->cmd = ft_calloc(len, sizeof(char));
	while (tmp && tmp->type == T_CMD)
	{
		ft_strlcat((*cmd_node)->cmd, tmp->data, len);
		if (tmp->next && tmp->next->type == T_CMD)
			ft_strlcat((*cmd_node)->cmd, " ", len);
		tmp = tmp->next;
	}
}

int	ft_len_cmd(t_lexer *tmp)
{
	int	len;

	len = 0;
	while (tmp && tmp->type == T_CMD)
	{
		len += (ft_strlen(tmp->data) + 1);
		tmp = tmp->next;
	}
	return (len);
}
