/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:27:08 by diespino          #+#    #+#             */
/*   Updated: 2025/12/15 17:41:55 by diespino         ###   ########.fr       */
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

t_env	*sort_lst(t_env *env)
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

t_env	*copy_lst(t_env *env)
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
				printf("declare -x %s=\"%s\"\n", tmp->var_name, tmp->var_value);
			else
				printf("declare -x %s\n", tmp->var_name);
		}
		tmp = tmp->next;
	}
	free_env_lst(&lst_cpy);
}

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

int	check_export_args(t_shell *msh)
{
	int	i;
		
	i = 0;
	if (ft_isdigit(msh->cmd_args[1][i]))
		return (0);
	while (ft_isalnum(msh->cmd_args[1][i]) || \
			msh->cmd_args[1][i] == '_')
		i++;
	if (msh->cmd_args[1][i] != '=')
		return (0);
	printf("EXPORT ARGs OK\n");
	return (1);
}

void	proccess_data(t_shell *msh)
{
	char	*name;
	char	*value;
	char	**tmp;
	int		i;

	tmp = ft_split(msh->cmd_args[1], '=');
	i = -1;
	while (tmp[++i])
		printf("%s\n", tmp[i]);
	name = tmp[0];
	if (msh->count_cmd_args == 2)
		value = tmp[1];
	else if (msh->count_cmd_args > 2)
	{
		if (ft_isquote(msh->cmd_args[2][0]))
			value = ft_strtrim(msh->cmd_args[2], "\'\"");
		else
			value = "\0";
	}
	printf("NAME: %s\n", name);
	printf("VALUE: %s\n", value);
	env_add_var(&msh->env, name, value);
	free_array(tmp);
}

void	ft_export(t_shell *msh)
{
	if (msh->count_cmd_args == 1)
		print_declared_vars(msh);
	else
	{
		if (check_export_args(msh))
			proccess_data(msh);
		else
			printf("EXPORT ARGs ERROR\n");
	}
	msh->exit_status = 0;
}
