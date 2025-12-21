/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:27:08 by diespino          #+#    #+#             */
/*   Updated: 2025/12/20 21:33:18 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_export_args(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[i]))
		return (0);
	while ((ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (arg[i] != '=')
		return (0);
	printf("EXPORT ARG OK: %s\n", arg);
	return (1);
}

/* 
 * CMD && ARGs: 7
   Arg[0]:     [export]
   Arg[1]:     [JUAN=hola]
   Arg[2]:     [JUAN=2hoal]
   Arg[3]:     [JUAN3="hola"]
   Arg[4]:     [JU_AN4=]
   Arg[5]:     [JUAN5=]
   Arg[6]:     [hola]
 */

void	proccess_data(t_shell *msh, char *var)
{
	char	*name;
	char	*value;
	char	**tmp;

	tmp = ft_split(var, '=');
//	tmp[0]= JUAN // tmp[1]= hola
	name = ft_strdup(tmp[0]);
	if (tmp[1] != NULL)
		value = trim_quotes(tmp[1]);
	else
		value = ft_strdup("");
	printf("  NAME: %s\n", name);
	printf("  VALUE: %s\n", value);
	env_add_var(&msh->env, name, value);
//	printf("SE CREO\n");
	free(name);
	free(value);
	free_array(tmp);
}

void	ft_export(t_shell *msh)
{
	int	i;
	char	*tmp;

	msh->exit_status = 0;
	if (msh->count_cmd_args == 1)
		print_declared_vars(msh);
	else
	{
		i = 1;
		while (msh->cmd_args[i])
		{
			if (check_export_args(msh->cmd_args[i]))
				proccess_data(msh, msh->cmd_args[i]);
			else
			{
				tmp = trim_quotes(msh->cmd_args[i]);
				printf("minishell: export: `%s%s\n", \
						msh->cmd_args[i], ERR_EXP);
				msh->exit_status = 1;
				free(tmp);
				return ;
			}
			i++;
		}
	}
}
