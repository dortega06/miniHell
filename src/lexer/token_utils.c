/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:13:45 by diespino          #+#    #+#             */
/*   Updated: 2025/09/10 16:05:58 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_quotes(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

t_token_type	is_symbol(char *str)
{	
	int	i;

	i = 0;
	if (str[i] == '|' && str[i + 1] == '\0')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '\0')
		return (REDIR_IN);
	else if (str[i] == '>' && str[i + 1] == '\0')
		return (REDIR_OUT);
	else if (str[i] == '<' && str[i + 1] == '<' && 
			str[i + 2] == '\0')
		return (APPEND);
	else if (str[i] == '>' && str[i + 1] == '>' &&
			str[i + 2] == '\0')
		return (HEREDOC);
	return (ERROR);
}
