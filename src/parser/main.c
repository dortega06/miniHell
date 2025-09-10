/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatgpt                                       +#+  +:+       +#+     */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../../includes/minishell.h"

/* Prototipos (ya definidos en tus otros .c) */
t_token     *make_tokens(char *str);
void        print_tokens(t_token *token);
t_parser    *init_parser(t_token *tokens);
t_cmd       *parse_command(t_parser *parser);

void    print_command(t_cmd *cmd)
{
    int i = 0;

    if (!cmd)
    {
        printf("No se pudo parsear el comando.\n");
        return;
    }
    printf("\n=== Comando Parseado ===\n");
    printf("cmd: %s\n", cmd->cmd);
    printf("argc: %d\n", cmd->arg_count);
    while (i < cmd->arg_count)
    {
        printf("argv[%d] = %s\n", i, cmd->args[i]);
        i++;
    }
    printf("========================\n\n");
}

int main(void)
{
    char    *line;
    t_token *tokens;
    t_parser *parser;
    t_cmd   *cmd;

    while ((line = readline("minishell> ")) != NULL)
    {
        tokens = make_tokens(line);
        printf("\n--- TOKENS ---\n");
        print_tokens(tokens);

        parser = init_parser(tokens);
        cmd = parse_command(parser);

        print_command(cmd);

        free(line);
        // Aquí deberías liberar tokens, parser y cmd con tus funciones de free.
    }
    return 0;
}

