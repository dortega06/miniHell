/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:50:00 by diespino          #+#    #+#             */
/*   Updated: 2025/12/13 15:26:30 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* typedef struct s_shell
 * {
 *        char **paths; ????? // variables de entorno del sistema
 *        char **cmd_args;    // comando seguido de argumentos
 *        int count_cmd_args; // cantidad de comando + argumentos
 *        t_env *env;         // lista de nodos que representa `envp`
 *        t_lexer *lexer;     // lista de nodos que separa los tokens
 *        t_parser *parser;   // lista de nodos que separa los comandos
 *        int exit_status;    // entero que representa el estado de salida
 *}
*/

/*
 * Comprobaciones de args:
 * 	solo env sin ningun arg
 * 		-> si tiene args no se ejecuta && exit_status = 1?
 */
void	ft_env(t_shell *msh)
{
	char	**msh_env;
	int		i;

	if (msh->count_cmd_args > 1)
	{
		printf("env: `%s': No such file or directory\n", \
      			msh->cmd_args[1]);
		msh->exit_status = 127;
		return ;
	}
	msh_env = env_to_array(msh->env);
	i = 0;
	while (msh_env[i])
		printf("%s\n", msh_env[i++]);
	msh->exit_status = 0;
	free_array(msh_env);
}
