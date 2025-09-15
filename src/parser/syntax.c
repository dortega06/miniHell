/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:23:46 by dortega-          #+#    #+#             */
/*   Updated: 2025/09/15 16:22:43 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int print_error(const char *prefix, const char *msg, int code)
{
    (void)prefix;
    fprintf(stderr, "%s", msg);
    return code;
}

int	validate_redirection_syntax(t_cmd *commands)
{
	t_cmd	*current_cmd;
	t_redir	*current_redir;

	current_cmd = commands;
	while (current_cmd)
	{
		current_redir = current_cmd->redirects;
		while (current_redir)
		{
			// Verificar que cada redirección tenga un archivo válido
			if (!current_redir->file || current_redir->file[0] == '\0')
				return (1);
			
			// Verificar tipos de redirección válidos
			if (current_redir->type != REDIR_OUT && current_redir->type != REDIR_IN 
				&& current_redir->type != HEREDOC && current_redir->type != APPEND)
				return (1);
			current_redir = current_redir->next;
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}

int	validate_pipe_syntax(t_cmd *commands)
{
	t_cmd	*current_cmd;
	int		cmd_count;

	if (!commands)
		return (1);
	cmd_count = 0;
	current_cmd = commands;
	// Contar comandos y verificar que cada uno tenga tokens válidos
	while (current_cmd)
	{
		cmd_count++;
		// Cada comando debe tener al menos un token válido
		if (!current_cmd->tokens)
			return (1);
		current_cmd = current_cmd->next;
	}
	// Si hay más de un comando, significa que hay pipes implícitos
	// Verificar que no sea solo un pipe vacío
	if (cmd_count == 1)
		return (0); // Un solo comando es válido
	return (0);
}

int	validate_token_syntax(t_cmd *commands)
{
	t_cmd	*current_cmd;
	t_token	*current;

	current_cmd = commands;
	while (current_cmd)
	{
		current = current_cmd->tokens;
		if (!current)
			return (1);
		while (current)
		{
			if (current->type != WORD && current->type != REDIR_IN
				&& current->type != APPEND && current->type != REDIR_OUT
				&& current->type != HEREDOC && current->type != PIPE)
				return (1);
			current = current->next;
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}

int	validate_syntax(t_cmd *commands)
{
	if (!commands)
	{
		print_error(NULL, "minishell: syntax error\n", 2);
		return (1);
	}
	if (validate_token_syntax(commands) == 1)
	{
		print_error(NULL, "minishell: syntax error\n", 2);
		return (1);
	}
	if (validate_redirection_syntax(commands) == 1)
	{
		print_error(NULL, "minishell: syntax error\n", 2);
		return (1);
	}
	if (validate_pipe_syntax(commands) == 1)
	{
		print_error(NULL, "minishell: syntax error\n", 2);
		return (1);
	}
	return (0);
}
