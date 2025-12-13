/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:27:08 by diespino          #+#    #+#             */
/*   Updated: 2025/12/13 17:51:49 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
minisHell$> export JUAN="hola"

CMD && ARGs: 3
   Arg[0]:     [export]
   Arg[1]:     [JUAN=]
   Arg[2]:     [hola]
IS_BUILT-IN (ft_executer)
 minisHell$> export JUAN=hola

CMD && ARGs: 2
   Arg[0]:     [export]
   Arg[1]:     [JUAN=hola]
IS_BUILT-IN (ft_executer)
zsh: segmentation fault (core dumped)  ./minishell

No chuta JUAN= y no deberia pillar JUAN+hola
*/

static int	array_len(char **tmp)
{
	int	len;

	printf("ARRAY_LEN\n");
	len = 0;
	while (tmp[len])
		len++;
	return (len);
}

void	set_data(t_shell *msh)
{
	char	**tmp;
	char	*name;
	char	*value;

	if (msh->count_cmd_args <= 2)
	{
		printf("IF msh->count_cmd_args <= 2\n");
		tmp = ft_split(msh->cmd_args[1], '=');
		printf("Hace split\n");
		name = ft_strdup(tmp[0]);
		if (array_len(tmp) == 1)
		{
			printf("if (array_len(tmp) == 1)\n");
			value = NULL;
		}
		else
			value = ft_strdup(tmp[1]);
		free_array(tmp);
	}
	else
	{
		printf("ELSE\n");
		name = ft_strtrim(msh->cmd_args[1], "=");
		value = ft_strdup(msh->cmd_args[2]);
	}
	env_add_var(&msh->env, name, value);
	free(name);
	free(value);
}

void	ft_export(t_shell *msh)
{
	printf("EXPORT\n");
	if (msh->count_cmd_args == 1)
		return ;
	if (msh->count_cmd_args == 2 && msh->cmd_args[1][0] == '-')
	{
		printf("minishell: export: %s: invalid option\n", \
				msh->cmd_args[1]);
		msh->exit_status = 127;
		return ;
	}
	set_data(msh);
	msh->exit_status = 0;
}
