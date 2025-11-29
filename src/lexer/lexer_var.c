/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:28:24 by diespino          #+#    #+#             */
/*   Updated: 2025/11/28 16:56:55 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 1. Separar partes del string
// * Head
// * Var
// * Tail
//
// 2. Exandir var
// * expand_var()
//
// 3. Juntar string
// * Head + New_var + Tail
// * ft_memcpy() || ft_memmove() || ft_strjoin() ??
// * 
char	*concat_new_var(char *head, char *var, char *tail)
{
	int		len_head;
	int		len_var;
	int		len_tail;
	char	*new_data;

	len_head = ft_strlen(head);
	len_var = ft_strlen(var);
	len_tail = ft_strlen(tail);
//	printf("H: %d | V: %d | T: %d\n", len_head, len_var, len_tail);
	new_data = malloc(len_head + len_var + len_tail + 1);
	if (!new_data)
		return (NULL);
	ft_memcpy(new_data, head, len_head);
	new_data[len_head] = '\0';
//	printf("1: ~%s~\n", new_data);
	ft_memcpy(new_data + len_head, var, len_var);
	new_data[len_head + len_var] = '\0';
//	printf("2: ~%s~\n", new_data);
	ft_memcpy(new_data + len_head + len_var, tail, len_tail);
	new_data[len_head + len_var + len_tail] = '\0';
//	printf("New_str: ~%s~\n", new_data);
	return (new_data);
}

void	expand_var(char **var, t_env *env)
{
	char	*tmp;
	
	tmp = *var;
	if (tmp[0] == '$')
		tmp++;
	while (env)
	{
		if (!ft_strcmp(tmp, env->var_name))
		{
//			printf("Se encontro: %s --> %s\n", env->var_name, env->var_value);
			free(*var);
			*var = ft_strdup(env->var_value);
			break ;
		}
		env = env->next;
	}
}

void	process_data(char **data, t_env *env)
{
	int		i;
	int		var_start;
	char	*tmp;
	char	*head;
	char	*var;
	char	*tail;

	i = 0;
	tmp = *data;
	while (tmp[i] && tmp[i] != '$')
		i++;
	head = ft_substr(tmp, 0, i);
//	printf("Head: ~%s~\n", head);
	var_start = i;
	i++;
	while (tmp[i] && (tmp[i] == '_' || \
				ft_isalpha(tmp[i]) || ft_isdigit(tmp[i])))
		i++;
	var = ft_substr(tmp, var_start, i - var_start);
//	printf("Var: ~%s~\n", var);
	tail = ft_substr(tmp, i, ft_strlen(tmp) - i);
//	printf("Tail: ~%s~\n", tail);
	expand_var(&var, env);
//	printf("New_var: ~%s~\n", var);
	free(*data);
	*data = concat_new_var(head, var, tail);
	free(head);
	free(var);
	free(tail);
}

void	ft_lexer_var(t_shell *msh)
{
	t_lexer *lex;
	int		i;

	lex = msh->lexer;
	while (lex)
	{
		i = 0;
		if (lex->type == T_GENERAL && lex->data[0] != '\'')
		{
			while (lex->data[i])
			{
				if (lex->data[i] == '$')
					process_data(&lex->data, msh->env);
				i++;
			}
		}
		lex = lex->next;
	}
}
