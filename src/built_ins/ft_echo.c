/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:36:52 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/17 11:45:27 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

static char	*str_quotes(char *str)
{
	int		i;
	int		j;
	char	*new;

	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

static int	is_flag_n(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = str_quotes(str);
	if (!tmp)
		return (0);
	if (tmp[i++] != '-')
		return (0);
	while (tmp[i] == 'n')
		i++;
	if (tmp[i] != '\0')
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

static void	print_echo_args(t_shell *msh, int i)
{
	char	*arg;

	while (msh->cmd_args[i])
	{
		arg = str_quotes(msh->cmd_args[i]);
		if (arg)
		{
			ft_putstr_fd(arg, msh->parser->redir_out);
			free(arg);
		}
		if (msh->cmd_args[i + 1])
			ft_putchar_fd(' ', msh->parser->redir_out);
		i++;
	}
}

void	ft_echo(t_shell *msh)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	msh->exit_status = 0;
	while (msh->cmd_args[i] && is_flag_n(msh->cmd_args[i]))
	{
		newline = 0;
		i++;
	}
	print_echo_args(msh, i);
	if (newline)
		ft_putchar_fd('\n', msh->parser->redir_out);
}
