/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:15:25 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/08 16:03:39 by dortega-         ###   ########.fr       */
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
	if (tmp->type == T_REDIR_IN)
		ft_redir_in(tmp, cmd_node);
	else if (tmp->type == T_REDIR_OUT)
		ft_redir_out(tmp, cmd_node);
	else if (tmp->type == T_APPEND)
		ft_append(tmp, cmd_node);
	else if (tmp->type == T_HEREDOC)
		ft_heardoc(tmp, cmd_node);
}

void	fill_cmd(t_lexer *tmp, t_parser **cmd_node)
{
	int	len;
	int	first;

	len = ft_len_cmd(tmp);
	first = 1;
	(*cmd_node)->cmd = ft_calloc(len, sizeof(char));
	while (tmp && (tmp->type == T_CMD || tmp->type == T_GENERAL))
	{
		if (!first)
			ft_strlcat((*cmd_node)->cmd, " ", len);
		ft_strlcat((*cmd_node)->cmd, tmp->data, len);
		first = 0;
		tmp = tmp->next;
	}
}

int	ft_len_cmd(t_lexer *tmp)
{
	int	len;

	len = 0;
	while (tmp && (tmp->type == T_CMD || tmp->type == T_GENERAL))
	{
		len += ft_strlen(tmp->data);
		len += 1;
		tmp = tmp->next;
	}
	if (len > 0)
		return (len);
	else
		return (1);
}

void	fill_redir(t_lexer *lex, t_parser **cmd_node, int *start, int end)
{
	t_lexer	*tmp;
	int		aux;

	tmp = lex;
	while (tmp && tmp->index != *start)
		tmp = tmp->next;
	aux = *start;
	while (tmp && aux <= end)
	{
		if (tmp->type == T_REDIR_IN || tmp->type == T_REDIR_OUT
			|| tmp->type == T_APPEND || tmp->type == T_HEREDOC)
		{
			if (tmp->index == *start)
				*start += 2;
			ft_redirect(tmp, cmd_node);
		}
		tmp = tmp->next;
		aux++;
	}
}
