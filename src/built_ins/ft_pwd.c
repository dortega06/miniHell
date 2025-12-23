/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:01:18 by diespino          #+#    #+#             */
/*   Updated: 2025/12/22 18:56:43 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_shell *msh)
{
	char	*pwd;
	char	*env_pwd;

	env_pwd = get_env_value(msh->env, "PWD");
	if (env_pwd)
	{
		ft_putendl_fd(env_pwd, STDOUT_FILENO);
		msh->exit_status = 0;
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("minishell: pwd: error retrieving current directory: "
			"getcwd: cannot access parent directories\n");
		msh->exit_status = 1;
		return ;
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	msh->exit_status = 0;
}
