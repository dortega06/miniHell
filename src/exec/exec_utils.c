/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 14:25:27 by diespino          #+#    #+#             */
/*   Updated: 2025/12/06 17:09:05 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_to_array(t_env *env)
{
	t_env	*tmp;
	char	**array;
	char	*tmp_str;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (i + 1));
	tmp = env;
	i = 0;
	while (tmp)
	{
		tmp_str = ft_strjoin(tmp->var_name, "=");
		array[i] = ft_strjoin(tmp_str, tmp->var_value);
		free(tmp_str);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
