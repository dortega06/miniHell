/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:50:00 by diespino          #+#    #+#             */
/*   Updated: 2025/12/26 13:00:50 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_shell *msh)
{
	char	**msh_env;
	int		i;

	if (msh->count_cmd_args > 1)
	{
		printf("env: `%s': No such file or directory\n",
			msh->cmd_args[1]);
		msh->exit_status = 127;
		return ;
	}
	msh_env = env_to_array(msh->env);
	i = 0;
	while (msh_env[i])
		printf("%s\n", msh_env[i++]);
	msh->exit_status = 0;
	free_array(msh_env);
}
