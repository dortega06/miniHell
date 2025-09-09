/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diespino <diespino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:01:04 by diespino          #+#    #+#             */
/*   Updated: 2025/09/09 15:53:22 by diespino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/includes/libft.h"

typedef enum token_type
{
	WORD,//		0 cmd, args, etc
	PIPE,//		1 |
	REDIR_IN,//	2 <
	REDIR_OUT,//	3 >
	APPEND,// 	4 >>
	HEREDOC,// 	5 <<
	ERROR,//	6
} 	t_token_type;

typedef struct s_token
{
	t_token_type	type;// WORD, PIPE,...
	char		*value;// palabra o simbolo
	int		position;// posicion palabra
}			t_token;

#endif
