/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:31:08 by diespino          #+#    #+#             */
/*   Updated: 2025/12/26 13:19:53 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_status(t_shell *msh)
{
	int	sig;

	if (WIFEXITED(msh->exit_status))
		msh->exit_status = WEXITSTATUS(msh->exit_status);
	else if (WIFSIGNALED(msh->exit_status))
	{
		sig = WTERMSIG(msh->exit_status);
		if (sig == SIGINT)
			msh->exit_status = 130;
		else if (sig == SIGQUIT)
			msh->exit_status = 131;
	}
	if (g_signal == S_SIGINT_CMD)
		msh->exit_status = 130;
	if (msh && msh->exit_status == 127)
		printf("%s\n", ERR_CMD);
}

static void	next_cmd(t_shell *msh)
{
	int	i;

	i = 0;
	while (msh->cmd_args[i])
		free(msh->cmd_args[i++]);
	free(msh->cmd_args);
	if (msh->parser->redir_in != 0)
		close(msh->parser->redir_in);
	if (msh->parser->redir_out != 1)
		close(msh->parser->redir_out);
	msh->parser = msh->parser->next;
}

static void	child_proccess(t_shell *msh)
{
	char		**msh_env;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (msh->parser->redir_in < 0 || msh->parser->redir_out < 0)
		exit(1);
	msh_env = env_to_array(msh->env);
	ft_child_dup_redirs(msh);
	ft_child_close_all_pipes(msh);
	ft_child_exec_cmd(msh, msh_env);
	free_array(msh_env);
	exit(127);
}

static void	ft_exec_child_or_builtin(t_shell *msh, t_parser *par,
										pid_t *pids, int *j)
{
	pid_t	pid;

	if (is_builtin(msh) && msh->pipe_num == 1)
		ft_builtins(msh);
	else
	{
		pid = fork();
		if (pid == 0)
			child_proccess(msh);
		if (par->redir_in != STDIN_FILENO)
			close(par->redir_in);
		if (par->redir_out != STDOUT_FILENO)
			close(par->redir_out);
		pids[(*j)++] = pid;
	}
}

void	ft_executer(t_shell *msh)
{
	pid_t		pids[1024];
	t_parser	*par;
	int			j;
	int			check;

	j = 0;
	msh->pipe_num = num_pipe(msh);
	par = msh->parser;
	while (par)
	{
		check = ft_check_signal_and_redirs(msh, par);
		if (check == 1)
			break ;
		if (check == 2)
		{
			par = par->next;
			continue ;
		}
		ft_split_and_dequote_cmd(msh, par);
		ft_exec_child_or_builtin(msh, par, pids, &j);
		next_cmd(msh);
		par = msh->parser;
	}
	ft_wait_children(msh, pids, j);
}
