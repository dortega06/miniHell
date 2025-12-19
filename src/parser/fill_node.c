/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 18:15:25 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/19 15:10:49 by diespino         ###   ########.fr       */
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
	while (tmp && tmp->index != start)
		tmp = tmp->next;
	fill_cmd(tmp, cmd_node);
}

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
	int	len;
///	int	first;
	int	exp;
	char	*trim;

	len = ft_len_cmd(tmp);
//	first = 1;
	exp = 0;
	(*cmd_node)->cmd = ft_calloc(len, sizeof(char));
	while (tmp && (tmp->type == T_CMD || tmp->type == T_GENERAL))
	{
//		if (!first)
//			ft_strlcat((*cmd_node)->cmd, " ", len);
		if (!ft_strncmp(tmp->data, "export", 6))
			exp = 1;
//		printf("EXP: %d\n", exp);
		if (tmp->data[0] == '\"' && exp == 0)
			trim = ft_strtrim(tmp->data, "\"");
		else if (tmp->data[0] == '\'' && exp == 0)
			trim = ft_strtrim(tmp->data, "\'");
		else
			trim = ft_strdup(tmp->data);
		ft_strlcat((*cmd_node)->cmd, trim, len);
/*		if (tmp->type == T_GENERAL && tmp->next && \
//				ft_isquote(tmp->next->data[0]))*/
//			first = 1;
//		else
//			first = 0;
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
