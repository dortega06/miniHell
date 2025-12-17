/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:51:50 by diespino          #+#    #+#             */
/*   Updated: 2025/12/16 11:38:33 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	replace_value(t_env **env, char *name, char *value)
{
		t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, name) == 0)
		{
			if (tmp->var_value)
				ft_memfree(tmp->var_value);
			tmp->var_value = ft_strdup(value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	env_add_var(t_env **env, char *name, char *value)
{
	t_env	*new;
	t_env	*tmp;

	if (!replace_value(env, name, value))
		return ;
	new = calloc(1, sizeof(t_env));
	new->var_name = ft_strdup(name);
	new->var_value = ft_strdup(value);
	new->next = NULL;
	if (*env == NULL)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_env_lst(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->var_name);
		free((*env)->var_value);
		free(*env);
		*env = tmp;
	}
	*env = NULL;
}
