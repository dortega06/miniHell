/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 14:01:18 by diespino          #+#    #+#             */
/*   Updated: 2025/12/21 14:02:01 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_shell *msh)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		msh->exit_status = 1;
		perror("pwd");
		return ;
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	msh->exit_status = 0;
}
