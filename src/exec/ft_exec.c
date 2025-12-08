/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 10:31:08 by diespino          #+#    #+#             */
/*   Updated: 2025/12/06 14:19:49 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_cmd(t_shell *msh)
{
	char	*cmd_path;
	char	**msh_env;

	msh_env = env_to_array(msh);

}

static void	child_proccess(t_sell *msh)
{
//	if (is_builtin(msh))
//		ft_builtin(msh);
//	else
	exec_cmd(msh);
}

void	ft_executer(t_shell *msh)
{
	t_pid	pid;
	
	if (!ft_isascii(msh->parser->cmd[0]))
	{
		msh->exit_status = 1;
		return ;
	}
	msh->cmd_args = ft_split_shell(msh, msh->parser->cmd, ' ');
/*//	if (is_builtin(msh))
//		ft_builtin(msh);
//	else
//	{
//		g_signal = S_CMD;
	pid = fork();
	if (pid == 0)
		child_proccess(msh);
	else
		waitpid(-1, &msh->exit_status, 0);
	handle_status(msh);
//	}
//	ft_next_cmd();*/
}
