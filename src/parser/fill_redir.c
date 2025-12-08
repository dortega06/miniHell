/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:38:07 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/08 16:04:26 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redir_in(t_lexer *tmp, t_parser **cmd_node)
{
	int	fd;

	fd = open(tmp->next->data, O_RDONLY);
	if (fd == -1)
		printf("minishell: error abriendo %s\n", tmp->next->data);
	(*cmd_node)->redir_in = fd;
}

void    ft_redir_out(t_lexer *tmp, t_parser **cmd_node)
{
	int	fd;

	fd = open(tmp->next->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	(*cmd_node)->redir_out = fd;

}

void    ft_append(t_lexer *tmp, t_parser **cmd_node)
{
	int fd;

	fd = open(tmp->next->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	(*cmd_node)->redir_out = fd;
}

void    ft_heardoc(t_lexer *tmp, t_parser **cmd_node)
{
	int	fd;

	fd = ft_heredoc(tmp->next->data);
	(*cmd_node)->redir_in = fd;
	if (g_signal != S_CANCEL_EXEC)
		g_signal = S_BASE;
}
