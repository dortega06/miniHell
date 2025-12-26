/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:31:08 by diespino          #+#    #+#             */
/*   Updated: 2025/12/24 09:32:53 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
* typedef struct s_parser
* {
* 	char *cmd;
* 	char	**args;             // comando que será ejecutado
* 	int redir_in;	           // redireccionamiento de entrada
* 	int redir_out;	          // redireccionamiento de salida
* 	struct s_parser *next;   //  siguiente elemento en la lista
* }			t_parser;
*
*typedef struct s_shell
*{
*        char **paths;       // variables de entorno del sistema
*        char **cmd_args;    // comando seguido de argumentos
*        int count_cmd_args; // cantidad de comando + argumentos
*        t_env *env;         // lista de nodos que representa `envp`
*        t_lexer *lexer;     // lista de nodos que separa los tokens
*        t_parser *parser;   // lista de nodos que separa los comandos
*        int exit_status;    // entero que representa el estado de salida
*}
*/

static void	handle_status(t_shell *msh)
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
		printf("%s: %s\n", ERR_CMD, msh->cmd_args[0]);
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
	char	*cmd_path;
	char	**msh_env;
	t_parser *tmp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (msh->parser->redir_in < 0 || msh->parser->redir_out < 0)
		exit(1);
	msh_env = env_to_array(msh->env);
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
	tmp = msh->parser;
	while (tmp)
	{
		if (tmp->redir_in > 2 && tmp->redir_in != STDIN_FILENO)
			close(tmp->redir_in);
		if (tmp->redir_out > 2 && tmp->redir_out != STDOUT_FILENO)
			close(tmp->redir_out);
		tmp = tmp->next;
	}
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
	free_array(msh_env);
	exit(127);
}

void	ft_executer(t_shell *msh)
{
	pid_t		pids[1024];
	pid_t		pid;
	t_parser	*par;
	int			j;
	int			i;
	char		*tmp;

	j = 0;
	par = msh->parser;
	msh->pipe_num = 0;
	while (par)
	{
		msh->pipe_num++;
		par = par->next;
	}
	par = msh->parser;
	while (par)
	{
		if (g_signal == S_SIGINT_CMD)
		{
			msh->exit_status = 130;
			break ;
		}
		if (par->redir_in == -1 || !par->cmd || !par->cmd[0])
		{
			if (par->redir_in > 0  && par->redir_in != STDIN_FILENO)
				close(par->redir_in);
			if (par->redir_out > 1 && par->redir_out != STDOUT_FILENO)
				close(par->redir_out);
			par = par->next;
			continue ;
		}
		msh->cmd_args = split_shell(msh, par->cmd, ' ');
		i = 0;
		while (msh->cmd_args[i])
		{
			tmp = remove_quotes(msh->cmd_args[i]);
			free(msh->cmd_args[i]);
			msh->cmd_args[i] = tmp;
			i++;
		}

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
			pids[j++] = pid;
		}

		next_cmd(msh);
		par = msh->parser;
	}
	i = 0;
	while (i < j)
		waitpid(pids[i++], &msh->exit_status, 0);
	handle_status(msh);
}
