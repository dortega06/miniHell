/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:30:48 by diespino          #+#    #+#             */
/*   Updated: 2025/12/21 16:46:02 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
 * QUE FALTA:
 * get_env_value(msh->env, "HOME") --> env_utils.c
 * update_env_var(msh, oldpwd, getcwd(NULL, 0)) --> env_add_var()
 * free_pwd(oldpwd, newpwd) --> liberar
 */

static void	free_pwd(char *oldpwd, char *newpwd)
{
	if (!oldpwd)
		free(oldpwd);
	if (!newpwd)
		free(newpwd);
}

static void	update_env_var(t_shell *msh, char *oldpwd, char *newpwd)
{
	env_add_var(&msh->env, "OLDPWD", oldpwd);
	env_add_var(&msh->env, "PWD", newpwd);
}

static char	*get_oldpwd(t_shell *msh)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("cd");
		msh->exit_status = 1;
		return (NULL);
	}
	return (oldpwd);
}

static char	*get_newpwd(t_shell *msh)
{
	char	*path;

	if (msh->cmd_args[1])
	{
		path = ft_strdup(msh->cmd_args[1]);
		return (path);
	}
	path = get_env_value(msh->env, "HOME");
	if (!path)
	{
		printf("minishel: cd: HOME not set\n");
		msh->exit_status = 1;
		return (NULL);
	}
	return (path);
}

void	ft_cd(t_shell *msh)
{
	char	*oldpwd;
	char	*newpwd;

	if (msh->count_cmd_args > 2)
	{
		printf("minishell: cd: too many arguments\n");
		msh->exit_status = 1;
		return ;
	}
	oldpwd = get_oldpwd(msh);
	newpwd = get_newpwd(msh);
	if (!oldpwd || !newpwd)
	{
		free_pwd(oldpwd, newpwd);
		return ;
	}
	if (chdir(newpwd) == -1)
	{
		perror("cd");
		free_pwd(oldpwd, newpwd);
		msh->exit_status = 1;
		return ;
	}
	update_env_var(msh, oldpwd, getcwd(NULL, 0));
	free_pwd(oldpwd, newpwd);
}
