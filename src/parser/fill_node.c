/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:15:25 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/26 13:16:05 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_fill_node(t_parser **cmd_node, int start, int end, t_shell *msh)
{
	t_lexer	*tmp;

	tmp = msh->lexer;
	(*cmd_node)->redir_in = STDIN_FILENO;
	(*cmd_node)->redir_out = STDOUT_FILENO;
	fill_redir(cmd_node, &start, end, msh);
	if (g_signal == S_SIGINT_CMD)
	{
		if ((*cmd_node)->redir_in > 2)
			close((*cmd_node)->redir_in);
		if ((*cmd_node)->redir_out > 2)
			close((*cmd_node)->redir_out);
		(*cmd_node)->redir_in = -1;
		return ;
	}
	while (tmp && tmp->index != start)
		tmp = tmp->next;
	fill_cmd(tmp, cmd_node);
}
/*
static int	count_heredocs(t_lexer *tmp, int start, int end)
{
	int	count;
	int	aux;

	count = 0;
	aux = start;
	while (tmp && tmp->index != start)
		tmp = tmp->next;
	while (tmp && aux <= end)
	{
		if (tmp->type == T_HEREDOC)
			count++;
		tmp = tmp->next;
		aux++;
	}
	return (count);
}*/

void	fill_redir(t_parser **cmd_node, int *start, int end, t_shell *msh)
{
	t_lexer	*tmp;
	int		aux;

	tmp = msh->lexer;
	while (tmp && tmp->index != *start)
		tmp = tmp->next;
	aux = *start;
	while (tmp && aux <= end)
	{
		if (g_signal == S_SIGINT_CMD)
			return ;
		if (tmp->type == T_REDIR_IN || tmp->type == T_REDIR_OUT
			|| tmp->type == T_APPEND || tmp->type == T_HEREDOC)
		{
			if (tmp->index == *start)
				*start += 2;
			ft_redirect(tmp, cmd_node, msh);
		}
		tmp = tmp->next;
		aux++;
	}
}
/*
void	fill_redir(t_parser **cmd_node, int *start, int end, t_shell *msh)
{
	t_lexer	*tmp;
	int		aux;
	int		heredoc_count;

	tmp = msh->lexer;
	heredoc_count = count_heredocs(tmp, *start, end);
	msh->count_heredoc += heredoc_count;
	if (msh->count_heredoc > MAX_HEREDOCS)
	{
		ft_putendl_fd("minishell: maximum here-document count exceeded", 2);
		(*cmd_node)->redir_in = -1;
		msh->exit_status = 2;
		return ;
	}
	while (tmp && tmp->index != *start)
		tmp = tmp->next;
	aux = *start;
	while (tmp && aux <= end)
	{
		if (g_signal == S_SIGINT_CMD)
			return ;
		if (tmp->type == T_REDIR_IN || tmp->type == T_REDIR_OUT
			|| tmp->type == T_APPEND || tmp->type == T_HEREDOC)
		{
			if (tmp->index == *start)
				*start += 2;
			ft_redirect(tmp, cmd_node, msh);
		}
		tmp = tmp->next;
		aux++;
	}
}*/

void	ft_redirect(t_lexer *tmp, t_parser **cmd_node, t_shell *msh)
{
	if (tmp->type == T_REDIR_IN)
		ft_redir_in(tmp, cmd_node);
	else if (tmp->type == T_REDIR_OUT)
		ft_redir_out(tmp, cmd_node);
	else if (tmp->type == T_APPEND)
		ft_append(tmp, cmd_node);
	else if (tmp->type == T_HEREDOC)
		ft_heardoc(tmp, cmd_node, msh);
}

void	fill_cmd(t_lexer *tmp, t_parser **cmd_node)
{
	int		len;
	char	*trim;

	len = ft_len_cmd(tmp);
	(*cmd_node)->cmd = ft_calloc(len, sizeof(char));
	while (tmp && (tmp->type == T_CMD || tmp->type == T_GENERAL
			|| tmp->type == T_SPACE))
	{
		trim = ft_strdup(tmp->data);
		ft_strlcat((*cmd_node)->cmd, trim, len);
		free(trim);
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
