/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 14:25:27 by diespino          #+#    #+#             */
/*   Updated: 2025/12/10 19:39:36 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void    free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char	*get_cmd_path(char *cmd, t_env *env)
{
	t_env	*tmp;
	char	**allpath;
	char	*tmp_path;
	char	*cmd_path;
	int		i;

	tmp = env;
	while (tmp && ft_strcmp(tmp->var_name, "PATH") != 0)
		tmp = tmp->next;
	allpath = ft_split(tmp->var_value, ':');
	i = -1;
	while (allpath[++i])
	{
		tmp_path = ft_strjoin(allpath[i], "/");
		cmd_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(cmd_path, F_OK) == 0)
		{
//			ft_memfree_all(allpath);
			free_array(allpath);
			return (cmd_path);
		}
		free(cmd_path);
	}
//	ft_memfree_all(allpath);
	free_array(allpath);
	return (cmd);
}

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
