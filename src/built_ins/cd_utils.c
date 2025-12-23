/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:35:23 by diespino          #+#    #+#             */
/*   Updated: 2025/12/22 14:35:30 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pwd(char *oldpwd, char *newpwd)
{
	if (oldpwd)
		free(oldpwd);
	if (newpwd)
		free(newpwd);
}

void	update_env_var(t_shell *msh, char *oldpwd, char *newpwd)
{
	env_add_var(&msh->env, "OLDPWD", oldpwd);
	env_add_var(&msh->env, "PWD", newpwd);
}

char	*join_three(char *pwd, char *slash, char *cmd_arg)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(pwd, slash);
	result = ft_strjoin(tmp, cmd_arg);
	free(tmp);
	return (result);
}
