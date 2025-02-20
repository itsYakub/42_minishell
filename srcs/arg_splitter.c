/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_splitter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwillis <lwillis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:43:25 by lwillis           #+#    #+#             */
/*   Updated: 2025/02/20 14:54:55 by lwillis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Gets the next finished argument
*/
static char	*extract_argument(char *frm, char *to)
{
	char	*sub;

	sub = ft_substr(frm, 0, ft_strlen(frm) - ft_strlen(to));
	sub = add_char_and_free(sub, '\n');
	return (sub);
}

/*
	Updates the state after leaving some text
*/
static void	handle_text(char *s, t_parse_state *state)
{
	if (SPACE == *s)
		*state = EMPTY;
	else if ('"' == *s || '\'' == *s)
		*state = QUOTE;
}

/*
	Updates the state after leaving an empty space
*/
static char	*handle_empty(char *s, t_parse_state *state)
{
	if ('"' == *s || '\'' == *s)
		*state = QUOTE;
	else if (SPACE != *s)
		*state = TEXT;
	return (s);
}

/*
	FSM to handle empty space, quoted text, and normal text
*/
static char	*split_keeping_quotes(char *s)
{
	char			*start;
	t_parse_state	state;
	char			*out;

	out = NULL;
	state = EMPTY;
	while (*s)
	{
		if (EMPTY == state)
			start = handle_empty(s, &state);
		else if (TEXT == state)
		{
			handle_text(s, &state);
			if (state == EMPTY)
				out = join_and_free(out, extract_argument(start, s));
		}
		else if ('"' == *s || '\'' == *s)
			state = TEXT;
		s++;
	}
	if (state != EMPTY)
		out = join_and_free(out, extract_argument(start, s));
	return (out);
}

/*
	Splits the arguments for execution, keeping quoted whitespace
*/
char	**split_args(char *s)
{
	char	*str;
	char	**split;

	if (!s || 1 == is_unprintable(s))
	{
		split = malloc(sizeof(char *) * 2);
		split[0] = strdup("");
		split[1] = NULL;
	}
	else
	{
		str = split_keeping_quotes(s);
		split = ft_split(str, '\n');
		free(str);
	}
	return (split);
}
