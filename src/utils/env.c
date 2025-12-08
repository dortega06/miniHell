/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 08:58:36 by diespino          #+#    #+#             */
/*   Updated: 2025/12/04 09:34:07 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int	start;

	i = 0;
	while (var[i] && var[i] != '=' && var[i] != ' ')
		i++;
	if (!var[i])
		return (ft_strdup(""));
	start = i + 1;
	if (ft_isquote(var[start]))
	{
		start++;
		len = ft_strlen(var) - start - 1;
		return (ft_substr(var, start, len));
	}
	else
	{
		len = ft_strlen(var) - start;
		return (ft_substr(var, start, len));
	}
}

void	mshell_lvl(t_env **env)
{
	t_env	*tmp;
	int		lvl;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var_name, "SHLVL"))
		{
			lvl = ft_atoi(tmp->var_value);
			lvl += 1;
			free(tmp->var_value);
			tmp->var_value = ft_itoa(lvl);
			return ;
		}
		tmp = tmp->next;
	}
}

void	env_init(t_env **env, char **envp)
{
	int		i;
	int		len;
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
	mshell_lvl(env);
}
