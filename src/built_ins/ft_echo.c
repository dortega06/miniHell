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

static int	is_flag_n(char *str)
{
int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	// Si después del '-' no hay nada, no es un flag válido
	if (str[i] == '\0')
		return (0);
	// Recorremos todas las 'n'
	while (str[i] == 'n')
		i++;
	// Si llegamos al final del string, es un flag -n válido
	if (str[i] == '\0')
		return (1);
	return (0);
}

static void	print_echo_args(t_shell *msh, int i)
{
	while (msh->cmd_args[i])
	{
		ft_putstr_fd(msh->cmd_args[i], msh->parser->redir_out);
		
		// Si existe un siguiente argumento, imprimimos el espacio separador
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