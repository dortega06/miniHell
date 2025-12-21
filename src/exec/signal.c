/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:38:15 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/20 18:42:26 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_signal = S_BASE;

/*static void sigint_handler(int sig)
{
    (void)sig;

	if (sig == SIGINT)
	{
		if (g_signal == S_BASE)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_signal = S_SIGINT_CMD;
		}
    		else if (g_signal == S_CMD)
    		{
	        	write(1, "\n", 1);
	        	g_signal = S_SIGINT_CMD;
	    	}
	    	else if (g_signal == S_HEREDOC)
	    	{
	        	write(1, "\n", 1);
	        	exit(130);
	    	}
	}
}*/

static void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();

    if (g_signal == S_HEREDOC)
        exit(130);
    else
        g_signal = S_SIGINT_CMD;
}

void setup_signals(t_signal state)
{
    g_signal = state;

    if (state == S_BASE)
    {
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, SIG_IGN); // Ctrl + \ no hace nada en el prompt
    }
    else if (state == S_CMD)
    {
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, sigint_handler); // Ctrl + \ sí afecta a comandos
    }
    else if (state == S_HEREDOC)
    {
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, SIG_IGN);
    }
}
