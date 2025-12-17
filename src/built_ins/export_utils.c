/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:57:16 by diespino          #+#    #+#             */
/*   Updated: 2025/12/16 15:59:28 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*sort_lst(t_env *env)
{
	t_env	*tmp;
	char	*tmp_name;
	char	*tmp_value;

	tmp = env;
	while (env->next)
	{
		if (env->next && \
			ft_strcmp(env->var_name, env->next->var_name) > 0)
		{
			tmp_name = env->var_name;
			tmp_value = env->var_value;
			env->var_name = env->next->var_name;
			env->var_value = env->next->var_value;
			env->next->var_name = tmp_name;
			env->next->var_value = tmp_value;
			env = tmp;
		}
		else
			env = env->next;
	}
	env = tmp;
	return (env);
}

static t_env	*copy_lst(t_env *env)
{
	t_env	*tmp;
	t_env	*cpy;

	tmp = env;
	cpy = NULL;
	while (tmp)
	{
		env_add_var(&cpy, tmp->var_name, tmp->var_value);
		tmp = tmp->next;
	}
	return (cpy);
}

void	print_declared_vars(t_shell *msh)
{
	t_env	*tmp;
	t_env	*lst_cpy;

	lst_cpy = copy_lst(msh->env);
	tmp = sort_lst(lst_cpy);
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, "_") != 0)
		{
			if (tmp->var_value[0])
				printf("declare -x %s=\"%s\"\n", \
						tmp->var_name, tmp->var_value);
			else
				printf("declare -x %s\n", tmp->var_name);
		}
		tmp = tmp->next;
	}
	free_env_lst(&lst_cpy);
}
