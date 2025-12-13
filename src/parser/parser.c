/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:27:19 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/13 19:18:05 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_add_nodes(t_parser **cmd_node, t_shell *msh);
static void	connect_pipes(t_parser *parser);

void	ft_parser(t_parser **parser, t_shell *msh)
{
	t_parser	*cmd_node;

	if (msh->lexer == NULL)
		return ;
	ft_index(msh->lexer);
	if (*parser == NULL)
		*parser = ft_calloc(1, sizeof(t_parser));
	cmd_node = *parser;
	if (cmd_node)
		ft_add_nodes(&cmd_node, msh);
	connect_pipes(*parser);
}

static void	ft_add_nodes(t_parser **cmd_node, t_shell *msh)
{
	int	start;
	int	num_pipes;
	int	i;
	int	end;

	start = 0;
	num_pipes = ft_count_pipes(msh->lexer);
	i = 0;
	while (i <= num_pipes)
	{
		end = get_last(msh->lexer, start);
		ft_fill_node(cmd_node, start, end, msh);
		if (i < num_pipes)
		{
			(*cmd_node)->next = ft_calloc(1, sizeof(t_parser));
			*cmd_node = (*cmd_node)->next;
		}
		start = end + 2;
		i++;
	}
}

static void	connect_pipes(t_parser *parser)
{
	t_parser	*current;
	int			fd[2];

	current = parser;
	while (current && current->next)
	{
		if (pipe(fd) == -1)
			return ;
		if (current->redir_out == STDOUT_FILENO)
			current->redir_out = fd[1];
		else
			close(fd[1]);
		if (current->next->redir_in == STDIN_FILENO)
			current->next->redir_in = fd[0];
		else
			close(fd[0]);
		current = current->next;
	}
}
