/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:30:54 by dortega-          #+#    #+#             */
/*   Updated: 2025/09/10 18:02:43 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*init_parser(t_token *tokens)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->current_node = tokens;
	parser->has_error = false;
	parser->error_msg = NULL;
	return (parser);
}

bool	is_word(t_parser *parser)
{
	if (!parser->current_node)
		return (false);
	return (parser->current_node->type == WORD);
}

int	count_words(t_parser *parser)
{
	t_token *temp;
	int count;

	temp = parser->current_node;
	count = 0;
	while (temp && temp->type == WORD)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

char **extract_words(t_parser *parser, int count)
{
	char **words;
	int i;

	words = malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (i < count && parser->current_node && parser->current_node->type == WORD)
	{
		words[i] = ft_strdup(parser->current_node->value);
		parser->current_node = parser->current_node->next;
		i++;
	}
	words[i] = NULL;
	return (words);
}

t_cmd *parse_command(t_parser *parser)
{
	t_cmd *cmd;
	int word_count;

	if (!is_word(parser))
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	word_count = count_words(parser);
	cmd->args = extract_words(parser, word_count);
	if (!cmd->args || !cmd->args[0])
	{
		free(cmd);
		return (NULL);
	}
	cmd->cmd = ft_strdup(cmd->args[0]);
	cmd->arg_count = word_count;
	return (cmd);
}

