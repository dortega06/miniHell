/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:52:52 by diespino          #+#    #+#             */
/*   Updated: 2025/12/21 18:26:36 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	del_node(t_env *node)
{
	free(node->var_name);
	free(node->var_value);
	free(node);
}

void	cmp_var(char *var, t_shell *msh)
{
	t_env	*env;
	t_env	*tmp;
	t_env	*next;

	env = msh->env;
	next = NULL;
	while (env && env->next)
	{
		if (!ft_strcmp(env->next->var_name, var))
		{
			tmp = env;
			env = env->next;
			if (env->next != NULL)
				next = env->next;
			del_node(env);
			tmp->next = next;
			break ;
		}
		env = env->next;
	}
}

void	ft_unset(t_shell *msh)
{
	int		i;
	t_env	*tmp;

	if (msh->count_cmd_args == 1)
	{
		msh->exit_status = 1;
		return ;
	}
	i = 1;
	while (msh->cmd_args[i])
	{
		if (!ft_strcmp(msh->env->var_name, msh->cmd_args[i]))
		{
			tmp = msh->env;
			msh->env = msh->env->next;
			del_node(tmp);
		}
		else
			cmp_var(msh->cmd_args[i], msh);
		i++;
	}
	msh->exit_status = 0;
}
