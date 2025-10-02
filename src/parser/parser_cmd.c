/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:49:25 by dortega-          #+#    #+#             */
/*   Updated: 2025/10/02 20:42:45 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	add_args(t_lexer *tokens, t_cmd *cmd_node)
{
	t_arg	*tmp;
	t_arg	*new_arg;

	new_arg = ft_calloc(1, sizeof(t_arg));
	if (!new_arg)
		return (false);
	new_arg->data = ft_strdup(tokens->data);
	if (!new_arg->data)
	{
		free(new_arg);
		return (false);
	}
	tmp = cmd_node->args;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_arg;
	cmd_node->cmd_argc += 1;
	return (true);
}

t_cmd	*create_cmd(t_token *tokens)
{
	t_cmd	*node;

	node = NULL;
	node = ft_calloc(1, sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->next = NULL;
	node->redirs = NULL;
	node->cmd_argc = 1;
	node->is_command = true;
	node->args = ft_calloc(1, sizeof(t_arg));
	if (!node->args)
		return (free_commands(&node), NULL);
	node->args->data = ft_strdup(tokens->data);
	if (!node->args->data)
		return (free_commands(&node), NULL);
	node->args->next = NULL;
	return (node);
}
