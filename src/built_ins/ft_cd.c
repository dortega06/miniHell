/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:30:48 by diespino          #+#    #+#             */
/*   Updated: 2025/12/26 17:07:24 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_oldpwd(t_shell *msh)
{
	char	*env_pwd;

	env_pwd = get_env_value(msh->env, "PWD");
	if (env_pwd)
		return (env_pwd);
	return (getcwd(NULL, 0));
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
		printf("minishell: cd: HOME not set\n");
		msh->exit_status = 1;
		return (NULL);
	}
	return (ft_strdup(path));
}

static void	cd_update_pwd(t_shell *msh, char *oldpwd, char *newpwd)
{
	char	*realpwd;
	char	*pwd;

	realpwd = getcwd(NULL, 0);
	if (!realpwd)
	{
		printf("minishell: cd: %s: getcwd: %s: %s\n",
			ERR_CD, ERR_GCWD, ERR_FDIR);
		pwd = get_env_value(msh->env, "PWD");
		if (pwd && msh->cmd_args[1])
			realpwd = join_three(pwd, "/", msh->cmd_args[1]);
		else
			realpwd = ft_strdup(newpwd);
	}
	update_env_var(msh, oldpwd, realpwd);
	free(realpwd);
}

static int	cd_change_dir(t_shell *msh, char **oldpwd, char **newpwd)
{
	if (msh->count_cmd_args > 2)
	{
		printf("minishell: cd: too many arguments\n");
		msh->exit_status = 1;
		return (1);
	}
	*oldpwd = get_oldpwd(msh);
	*newpwd = get_newpwd(msh);
	if (!*newpwd)
	{
		free_pwd(*oldpwd, NULL);
		return (1);
	}
	if (chdir(*newpwd) == -1)
	{
		printf("minishell: cd: %s\n", strerror(errno));
		free_pwd(*oldpwd, *newpwd);
		msh->exit_status = 1;
		return (1);
	}
	return (0);
}

void	ft_cd(t_shell *msh)
{
	char	*oldpwd;
	char	*newpwd;

	if (cd_change_dir(msh, &oldpwd, &newpwd))
		return ;
	cd_update_pwd(msh, oldpwd, newpwd);
	free_pwd(oldpwd, newpwd);
	msh->exit_status = 0;
}

/*void	ft_cd(t_shell *msh)
{
	char	*oldpwd;
	char	*newpwd;
	char	*realpwd;
	char	*pwd;

	if (msh->count_cmd_args > 2)
	{
		printf("minishell: cd: too many arguments\n");
		msh->exit_status = 1;
		return ;
	}
	oldpwd = get_oldpwd(msh);
	newpwd = get_newpwd(msh);
	if (!newpwd)
	{
		free_pwd(oldpwd, NULL);
		return ;
	}
	if (chdir(newpwd) == -1)
	{
		printf("minishell: cd: %s\n", strerror(errno));
		free_pwd(oldpwd, newpwd);
		msh->exit_status = 1;
		return ;
	}
	realpwd = getcwd(NULL, 0);
	if (!realpwd)
	{
		printf("minishell: cd: error retrieving current directory: "
				"getcwd: cannot access parent directories: "
				"No such file or directory\n");
		pwd = get_env_value(msh->env, "PWD");
		if (pwd && msh->cmd_args[1])
			realpwd = join_three(pwd, "/", msh->cmd_args[1]);
		else	
			realpwd = ft_strdup(newpwd);
	}
	update_env_var(msh, oldpwd, realpwd);
	free_pwd(oldpwd, newpwd);
	free(realpwd);
	msh->exit_status = 0;
}*/
