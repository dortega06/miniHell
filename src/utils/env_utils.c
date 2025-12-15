/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:51:50 by diespino          #+#    #+#             */
/*   Updated: 2025/12/13 17:47:04 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_add_var(t_env **env, char *name, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = calloc(1, sizeof(t_env));
	new->var_name = ft_strdup(name);
	new->var_value = ft_strdup(value);
//	new->var_name = ft_substr(name, 0, ft_strlen(name));
//	new->var_value = ft_substr(value, 0, ft_strlen(value));
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
