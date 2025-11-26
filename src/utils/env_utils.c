/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:51:50 by diespino          #+#    #+#             */
/*   Updated: 2025/11/25 16:32:18 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
typedef struct s_env
{
	char 		*var_name; // nombre de la variable
	char 		*value_var;// valor de la variable
	struct s_env 	*next; 	   // siguiente elemento en la lista
}			t_env;
*/
char	*get_var_name(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=' && var[i] != ' ')
		i++;
	return (ft_substr(var, 0, i));
}

char	*get_var_value(char *var)
{
	int	i;
	int	len;

	i = 0;
	while (var[i] && var[i] != '=' && var[i] != ' ')
		i++;
	len = i + 1;
	while (var[len])
		len++;
	if (ft_isquote(var[i + 1]))
		return (ft_substr(var, i + 2, len - 1));
	else
		return (ft_substr(var, i + 1, len));
}

void	env_add_var(t_env **env, char *name, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = calloc(1, sizeof(t_env));
	new->var_name = ft_substr(name, 0, ft_strlen(name));
	new->var_value = ft_substr(value, 0, ft_strlen(value));
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

	if (!*env || !(*env))
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

void	env_init(t_env **env, char **envp)
{
	int	i;
	int	len;
	char	*var_name;
	char	*var_value;

	len = 0;
	while (envp[len])
		len++;
	i = -1;
	while (++i < len)
	{
		var_name = get_var_name(envp[i]);
		var_value = get_var_value(envp[i]);
		env_add_var(env, var_name, var_value);
		free(var_name);
		free(var_value);
	}
}
