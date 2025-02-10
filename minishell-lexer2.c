/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-lexer2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:27:33 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/10 16:00:58 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int		msh_lexer_expand(t_lexer *l, char **env)
{
	t_token	*t;
	char	*tmp0;
	char	*tmp1;
	size_t	bytes;

	t = l->tokens;
	bytes = 0;
	tmp0 = NULL;
	tmp1 = NULL;
	while (t->type != T_NULL)
	{
		if (t->type == T_KEY)
		{
			if (ft_strchr(t->data, '$'))
			{
				tmp0 = env_value(ft_strchr(t->data, '$') + 1, env);
				if (!tmp0)
					tmp0 = ft_calloc(1, 1);
				bytes = ft_strchr(t->data, '$') - t->data + ft_strlen(tmp0) + 1;
				tmp1 = ft_calloc(bytes + 1, sizeof(char));
				ft_strlcpy(tmp1, t->data, bytes - ft_strlen(tmp0));
				ft_strlcat(tmp1, tmp0, bytes);
				free(t->data);
				free(tmp0);
				t->data = tmp1;
			}
		}
		t = t->next;
	}
	return (1);
}
