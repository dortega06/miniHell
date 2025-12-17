/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:01:43 by diespino          #+#    #+#             */
/*   Updated: 2025/12/17 11:54:34 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_shell *msh)
{
	if (ft_strcmp(msh->cmd_args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(msh->cmd_args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(msh->cmd_args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(msh->cmd_args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(msh->cmd_args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(msh->cmd_args[0], "env") == 0)
		return (1);
	else if (ft_strcmp(msh->cmd_args[0], "exit") == 0)
		return (1);
	return (0);
}

void	ft_builtins(t_shell *msh)
{
	if (ft_strcmp(msh->cmd_args[0], "env") == 0)
		ft_env(msh);
	else if (ft_strcmp(msh->cmd_args[0], "export") == 0)
		ft_export(msh);
	else if (ft_strcmp(msh->cmd_args[0], "unset") == 0)
		ft_unset(msh);

	//else if (ft_strcmp(msh->cmd_args[0], "cd") == 0)
	//	ft_cd();
	else if (ft_strcmp(msh->cmd_args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(msh->cmd_args[0], "exit") == 0)
		ft_exit_built(msh);
	else if (ft_strcmp(msh->cmd_args[0], "echo") == 0)
		ft_echo(msh);
}
