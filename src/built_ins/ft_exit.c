/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:19:10 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/21 18:20:51 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_exit_args(t_shell *msh)
{
	int		i;
	char	*arg;

	if (msh->count_cmd_args > 2)
		return (1);
	arg = msh->cmd_args[1];
	if (arg)
	{
		i = 0;
		if (arg[0] == '+' || arg[0] == '-')
			i++;
		if (arg[i] == '\0')
		{
			fprintf(stderr, "exit: %s: numeric argument required\n", arg);
			return (255);
		}
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
			{
				fprintf(stderr, "exit: %s: numeric argument required\n", arg);
				return (255);
			}
			i++;
		}
		return (ft_atoi(arg));
	}
	return (0);
}

void	ft_exit_built(t_shell *msh)
{
	ft_putendl_fd("exit", 2);
	msh->exit_status = check_exit_args(msh);
	if (msh->exit_status != 1)
		exit(msh->exit_status);
	ft_putendl_fd("exit: too many arguments", 2);
}
