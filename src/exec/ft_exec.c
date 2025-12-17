/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:31:08 by diespino          #+#    #+#             */
/*   Updated: 2025/12/17 11:36:13 by dortega-         ###   ########.fr       */
/*   Updated: 2025/12/16 16:04:44 by diespino         ###   ########.fr       */
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
	if (WIFEXITED(msh->exit_status))
		msh->exit_status = WEXITSTATUS(msh->exit_status);
	if (msh && msh->exit_status == 127)
		printf("%s: %s\n", ERR_CMD, msh->cmd_args[0]);
//	if (g_signal == S_SIGNAL_CMD)
//		msh->exit_status = 130;
//	g_signal = S_BASE;
}

static void	next_cmd(t_shell *msh)
{
	int     i;

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

/*static void	exec_cmd(t_shell *msh)
{
	char	*cmd_path;
	char	**msh_env;

	if (msh->parser->redir_in < 0)
		exit(1);
	msh_env = env_to_array(msh->env);
	if (msh->parser->redir_in != 0)
	{
		dup2(msh->parser->redir_in, STDIN_FILENO);
		close(msh->parser->redir_in);
	}
	if (msh->parser->redir_out != 1)
	{
		dup2(msh->parser->redir_out, STDOUT_FILENO);
		close(msh->parser->redir_out);
	}
	cmd_path = get_cmd_path(msh->cmd_args[0], msh->env);
	execve(cmd_path, msh->cmd_args, msh_env);
	exit(127);
}*/

static void	child_proccess(t_shell *msh)
{
	char	*cmd_path;
	char	**msh_env;

	if (msh->parser->redir_in < 0 || msh->parser->redir_out < 0)
		exit(1);
	msh_env = env_to_array(msh->env);
	if (msh->parser->redir_in != 0)
	{
		dup2(msh->parser->redir_in, STDIN_FILENO);
		close(msh->parser->redir_in);
	}
	if (msh->parser->redir_out != 1)
	{
		dup2(msh->parser->redir_out, STDOUT_FILENO);
		close(msh->parser->redir_out);
	}
	cmd_path = get_cmd_path(msh->cmd_args[0], msh->env);
	execve(cmd_path, msh->cmd_args, msh_env);
	free_array(msh_env);
	exit(127);
}
//  || !ft_isascii(msh->parser->cmd[0])

void	ft_executer(t_shell *msh)
{
	pid_t	pid;
	
	while (msh->parser)
	{
		if (!msh->parser->cmd[0])
		{
			msh->exit_status = 1;
			return ;
		}
		msh->cmd_args = split_shell(msh, msh->parser->cmd, ' ');
		printf("\nCMD && ARGs: %d\n", msh->count_cmd_args);
		print_array(msh->cmd_args);
		if (is_builtin(msh))
/**/		{
//			printf("IS_BUILT-IN (ft_executer)\n");
			ft_builtins(msh);
		}
		else
		{
//			g_signal = S_CMD;
			pid = fork();
			if (pid == 0)
				child_proccess(msh);
			else
				waitpid(-1, &msh->exit_status, 0);
			handle_status(msh);
		}
		next_cmd(msh);
	}
}
