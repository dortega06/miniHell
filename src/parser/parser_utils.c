/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:25:08 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/24 10:11:58 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_parser_lst(t_parser **parser)
{
	t_parser	*tmp;
	t_parser	*next;

	if (!parser || !*parser)
		return ;
	tmp = *parser;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->redir_in > STDIN_FILENO)
			close(tmp->redir_in);
		if (tmp->redir_out > STDOUT_FILENO)
			close(tmp->redir_out);
		free(tmp);
		tmp = next;
	}
	*parser = NULL;
}

void	ft_index(t_lexer *lex)
{
	t_lexer	*tmp;
	int		i;

	tmp = lex;
	i = 0;
	while (tmp)
	{
		tmp->index = i;
		tmp = tmp->next;
		i++;
	}
}

int	ft_count_pipes(t_lexer *lex)
{
	t_lexer	*tmp;
	int		i;

	tmp = lex;
	i = 0;
	while (tmp)
	{
		if (tmp->type == T_PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	get_last(t_lexer *lex, int start)
{
	t_lexer	*tmp;
	int		last;

	last = -1;
	tmp = lex;
	while (tmp && tmp->next)
	{
		if (tmp->type == T_PIPE && tmp->index > start)
			return (tmp->index - 1);
		tmp = tmp->next;
	}
	last = tmp->index;
	return (last);
}

int	ft_heredoc_eof_warning(char *delimiter)
{
	write(2, ERR_WARNING, 68);
	write(2, delimiter, ft_strlen(delimiter));
	write(2, "')\n", 3);
	return (0);
}
