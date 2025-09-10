/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:45:00 by diespino          #+#    #+#             */
/*   Updated: 2025/09/10 17:52:22 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_cmd(t_cmd *cmd)
{
	int i;

	if (!cmd)
		return;
	printf("=== COMMAND ===\n");
	printf("Command: %s\n", cmd->cmd);
	printf("Arguments (%d):\n", cmd->arg_count);
	i = 0;
	while (cmd->args[i])
	{
		printf("  [%d]: %s\n", i, cmd->args[i]);
		i++;
	}
	printf("\n");
}

void free_cmd(t_cmd *cmd)
{
	int i;

	if (!cmd)
		return;
	free(cmd->cmd);
	i = 0;
	while (cmd->args[i])
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	free(cmd);
}

int main(int argc, char **argv)
{
	t_token *tokens;
	t_parser *parser;
	t_cmd *cmd;
	char *input;
	int i;
	int total_len;

	if (argc < 2)
	{
		printf("Usage: %s \"command with args\"\n", argv[0]);
		printf("Example: %s \"ls -la file.txt\"\n", argv[0]);
		return (1);
	}
	
	// Concatenar todos los argumentos en una sola string
	total_len = 0;
	i = 1;
	while (i < argc)
	{
		total_len += strlen(argv[i]) + 1; // +1 para el espacio
		i++;
	}
	
	input = malloc(total_len);
	if (!input)
		return (1);
	input[0] = '\0';
	
	i = 1;
	while (i < argc)
	{
		strcat(input, argv[i]);
		if (i < argc - 1)
			strcat(input, " ");
		i++;
	}
	
	printf("Input: %s\n", input);
	
	tokens = make_tokens(input);
	print_tokens(tokens);
	
	parser = init_parser(tokens);
	cmd = parse_command(parser);
	print_cmd(cmd);
	
	free_cmd(cmd);
	free(parser);
	free(input);
	return (0);
}
