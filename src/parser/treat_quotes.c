/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:12:05 by dortega-          #+#    #+#             */
/*   Updated: 2025/11/15 17:12:54 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_quotes_parser(t_lexer *lex)
{
	t_lexer	*tmp;
	char	*data;
	int		i;
	char	quote;

	tmp = lex;
	while (tmp)
	{
		data = tmp->data;
		i = 0;
		quote = 0;
		while (data[i])
		{
			if ((data[i] == '\'' || data[i] == '\"') && !quote)
				quote = data[i];
			else if (data[i] == quote)
				quote = 0;
			i++;
		}
		if (quote != 0)
			return (ft_putendl_fd("miniHell: syntax error unclosed quote", 2), 0);
		tmp = tmp->next;
	}
	return (1);
}

/*
** Elimina las comillas de un string (primera y última si coinciden)
** y retorna una nueva string sin ellas
*/
char	*strip_quotes(char *str)
{
	char	*result;
	int		len;
	int		start;
	int		end;

	if (!str || !*str)
		return (ft_strdup(""));
	len = ft_strlen(str);
	start = 0;
	end = len;

	// Si empieza y termina con la misma comilla, quitarlas
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'')
		|| (str[0] == '\"' && str[len - 1] == '\"')))
	{
		start = 1;
		end = len - 1;
	}
	result = ft_calloc(end - start + 1, sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, str + start, end - start + 1);
	return (result);
}

/*
** Procesa un token quitando las comillas externas
** Mantiene comillas internas si las hay
*/
char	*process_token_quotes(char *token)
{
	char	*processed;
	char	*temp;
	int		has_quotes;

	if (!token)
		return (NULL);

	// Verificar si el token tiene comillas
	has_quotes = (token[0] == '\'' || token[0] == '\"');

	if (!has_quotes)
		return (ft_strdup(token));

	// Quitar las comillas externas
	processed = strip_quotes(token);
	if (!processed)
		return (ft_strdup(token));

	return (processed);
}

/*
** Verifica si un token está entre comillas simples
** (para saber si debemos expandir variables o no)
*/
int	is_single_quoted(char *str)
{
	int	len;

	if (!str || !*str)
		return (0);
	len = ft_strlen(str);
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (1);
	return (0);
}

/*
** Verifica si un token está entre comillas dobles
*/
int	is_double_quoted(char *str)
{
	int	len;

	if (!str || !*str)
		return (0);
	len = ft_strlen(str);
	if (len >= 2 && str[0] == '\"' && str[len - 1] == '\"')
		return (1);
	return (0);
}
