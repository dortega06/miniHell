/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 14:08:30 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/26 14:08:50 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	num_pipe(t_shell *msh)
{
	t_parser	*par;
	int			pipe_num;

	par = msh->parser;
	pipe_num = 0;
	while (par)
	{
		pipe_num++;
		par = par->next;
	}
	return (pipe_num);
}

int	ft_check_signal_and_redirs(t_shell *msh, t_parser *par)
{
	if (g_signal == S_SIGINT_CMD)
	{
		msh->exit_status = 130;
		return (1);
	}
	if (par->redir_in == -1 || !par->cmd || !par->cmd[0])
	{
		ft_handle_redirs_or_empty_cmd(par);
		return (2);
	}
	return (0);
}

void	ft_wait_children(t_shell *msh, pid_t *pids, int j)
{
	int	i;

	i = 0;
	while (i < j)
		waitpid(pids[i++], &msh->exit_status, 0);
	handle_status(msh);
}

int	ft_handle_redirs_or_empty_cmd(t_parser *par)
{
	if (par->redir_in > 0 && par->redir_in != STDIN_FILENO)
		close(par->redir_in);
	if (par->redir_out > 1 && par->redir_out != STDOUT_FILENO)
		close(par->redir_out);
	return (0);
}

void	ft_split_and_dequote_cmd(t_shell *msh, t_parser *par)
{
	int		i;
	char	*tmp;

	msh->cmd_args = split_shell(msh, par->cmd, ' ');
	i = 0;
	while (msh->cmd_args[i])
	{
		tmp = remove_quotes(msh->cmd_args[i]);
		free(msh->cmd_args[i]);
		msh->cmd_args[i] = tmp;
		i++;
	}
}
