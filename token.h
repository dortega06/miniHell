/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:01:04 by diespino          #+#    #+#             */
/*   Updated: 2025/09/09 13:55:45 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdio.h>
# include <stdlib.h>

typedef enum token_type
{
	WORD,//		cmd, args, etc
	PIPE,//		|
	REDIR_IN,//	<
	REDIR_OUT,//	>
	APPEND,// 	>>
	HEREDOC,// 	<<
} 	t_token_type;

typedef struct s_token
{
	t_token_type	type;// WORD, PIPE,...
	char		*value;// palabra o simbolo
	int		position;// posicion palabra
}			t_token;

#endif
