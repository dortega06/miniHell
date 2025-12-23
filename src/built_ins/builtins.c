/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:01:43 by diespino          #+#    #+#             */
/*   Updated: 2025/12/22 19:59:10 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*int	is_builtin_a(t_shell *msh)
{
	if (ft_strcmp(msh->cmd_args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(msh->cmd_args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(msh->cmd_args[0], "exit") == 0)
		return (1);
	return (0);
}

int	is_builtin_b(t_shell *msh)
{
	if (ft_strcmp(msh->cmd_args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(msh->cmd_args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(msh->cmd_args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(msh->cmd_args[0], "env") == 0)
		return (1);
	return (0);
}

void	ft_builtins_a(t_shell *msh)
{
	if (ft_strcmp(msh->cmd_args[0], "cd") == 0)
		ft_cd(msh);
	else if (ft_strcmp(msh->cmd_args[0], "exit") == 0)
		ft_exit_built(msh);
	else if (ft_strcmp(msh->cmd_args[0], "echo") == 0)
		ft_echo(msh);
}

void	ft_builtins_b(t_shell *msh)
{
	if (ft_strcmp(msh->cmd_args[0], "env") == 0)//
		ft_env(msh);
	else if (ft_strcmp(msh->cmd_args[0], "export") == 0)//
		ft_export(msh);
	else if (ft_strcmp(msh->cmd_args[0], "unset") == 0)//
		ft_unset(msh);
	else if (ft_strcmp(msh->cmd_args[0], "pwd") == 0)//
		ft_pwd(msh);
	exit(msh->exit_status);
}*/

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
	if (ft_strcmp(msh->cmd_args[0], "env") == 0)//
		ft_env(msh);
	else if (ft_strcmp(msh->cmd_args[0], "export") == 0)//
		ft_export(msh);
	else if (ft_strcmp(msh->cmd_args[0], "unset") == 0)//
		ft_unset(msh);
	else if (ft_strcmp(msh->cmd_args[0], "cd") == 0)
		ft_cd(msh);
	else if (ft_strcmp(msh->cmd_args[0], "pwd") == 0)//
		ft_pwd(msh);
	else if (ft_strcmp(msh->cmd_args[0], "exit") == 0)
		ft_exit_built(msh);
	else if (ft_strcmp(msh->cmd_args[0], "echo") == 0)
		ft_echo(msh);
}
