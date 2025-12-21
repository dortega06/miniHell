/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:28:24 by diespino          #+#    #+#             */
/*   Updated: 2025/12/20 21:36:17 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*concat_new_var(char *head, char *var, char *tail)
{
	int		len_head;
	int		len_var;
	int		len_tail;
	char	*new_data;

	len_head = ft_strlen(head);
	len_var = ft_strlen(var);
	len_tail = ft_strlen(tail);
	new_data = malloc(len_head + len_var + len_tail + 1);
	if (!new_data)
		return (NULL);
	ft_memcpy(new_data, head, len_head);
	new_data[len_head] = '\0';
	ft_memcpy(new_data + len_head, var, len_var);
	new_data[len_head + len_var] = '\0';
	ft_memcpy(new_data + len_head + len_var, tail, len_tail);
	new_data[len_head + len_var + len_tail] = '\0';
	return (new_data);
}

void	expand_var(char **var, t_shell *msh)
{
	int		i;
	char	*tmp;
	t_env	*env;

	i = 0;
	tmp = *var;
	env = msh->env;
	if (tmp[i] == '$')
		i++;
	while (env)
	{
		if (tmp[i] == '?')
		{
			free(*var);
			*var = ft_itoa(msh->exit_status);
			return ;
		}
		if (!ft_strcmp(tmp + i, env->var_name))
		{
			free(*var);
			*var = ft_strdup(env->var_value);
			return ;
		}
		env = env->next;
	}
}

void	process_data(char **data, t_shell *msh)
{
	int		i;
	int		var_start;
	char	*head;
	char	*var;
	char	*tail;

	i = 0;
	while ((*data)[i] && (*data)[i] != '$')
		i++;
	head = ft_substr((*data), 0, i);
	var_start = i;
	i++;
	while ((*data)[i] && ((*data)[i] == '_' || (*data)[i] == '?' || \
			ft_isalpha((*data)[i]) || ft_isdigit((*data)[i])))
		i++;
	var = ft_substr((*data), var_start, i - var_start);
	tail = ft_substr((*data), i, ft_strlen((*data)) - i);
	expand_var(&var, msh);
	free(*data);
	*data = concat_new_var(head, var, tail);
	free(head);
	free(var);
	free(tail);
}



void	ft_lexer_var(t_shell *msh)
{
	t_lexer	*lex;
	int		i;

	lex = msh->lexer;
	while (lex)
	{
		i = 0;
		if (lex->type == T_GENERAL && lex->data[0] != '\'') //&& lex->data[0] != '\"')
		{
			while (lex->data[i])
			{
				if (lex->data[i] == '$')
					process_data(&lex->data, msh);
				i++;
			}
		}
		lex = lex->next;
	}
}
