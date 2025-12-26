/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dortega- <dortega-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 13:22:49 by dortega-          #+#    #+#             */
/*   Updated: 2025/12/26 13:24:03 by dortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_has_quotes(char *str)
{
	if (! str || !str[0])
		return (0);
	return (str[0] == '"' || str[0] == '\'');
}

char	*ft_remove_quotes(char *str)
{
	int		len;
	char	*result;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\'')))
	{
		result = ft_substr(str, 1, len - 2);
		return (result);
	}
	return (ft_strdup(str));
}
