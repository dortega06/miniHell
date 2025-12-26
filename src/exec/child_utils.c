/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:22:41 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/26 14:23:00 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_child_dup_redirs(t_shell *msh)
{
	if (msh->parser->redir_in != STDIN_FILENO)
	{
		dup2(msh->parser->redir_in, STDIN_FILENO);
		close(msh->parser->redir_in);
	}
	if (msh->parser->redir_out != STDOUT_FILENO)
	{
		dup2(msh->parser->redir_out, STDOUT_FILENO);
		close(msh->parser->redir_out);
	}
}

void	ft_child_close_all_pipes(t_shell *msh)
{
	t_parser	*tmp;

	tmp = msh->parser;
	while (tmp)
	{
		if (tmp->redir_in > 2 && tmp->redir_in != STDIN_FILENO)
			close(tmp->redir_in);
		if (tmp->redir_out > 2 && tmp->redir_out != STDOUT_FILENO)
			close(tmp->redir_out);
		tmp = tmp->next;
	}
}

void	ft_child_exec_cmd(t_shell *msh, char **msh_env)
{
	char	*cmd_path;

	if (is_builtin(msh))
	{
		ft_builtins(msh);
		exit(msh->exit_status);
	}
	else
	{
		cmd_path = get_cmd_path(msh->cmd_args[0], msh->env);
		execve(cmd_path, msh->cmd_args, msh_env);
	}
}
