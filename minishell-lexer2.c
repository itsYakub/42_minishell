/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-lexer2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joleksia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:27:33 by joleksia          #+#    #+#             */
/*   Updated: 2025/02/11 10:49:43 by joleksia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int		msh_lexer_expand(t_lexer *l, char **env)
{
	t_lexer_mode	mode;
	t_token			*t;
	char			*tmp0;
	char			*tmp1;
	size_t			bytes;

	t = l->tokens;
	bytes = 0;
	tmp0 = NULL;
	tmp1 = NULL;
	mode = M_CMD;
	while (t->type != T_NULL)
	{
		if (t->type == T_SQUOT)
		{
			if (mode == M_CMD)
				mode = M_SQUOT;
			else
				mode = M_CMD;
		}
		else if (t->type == T_DQUOT)
		{
			if (mode == M_CMD)
				mode = M_DQUOT;
			else
				mode = M_CMD;
		}
		if (t->type == T_KEY && (mode == M_CMD || mode == M_DQUOT))
		{
			if (ft_strchr(t->data, '$'))
			{
				tmp0 = env_value(ft_strchr(t->data, '$') + 1, env);
				if (!tmp0 || !*tmp0)
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
