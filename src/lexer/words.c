/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihzhang <yihzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:53:36 by yihzhang          #+#    #+#             */
/*   Updated: 2026/03/30 21:06:16 by yihzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_word	*ft_getword(t_word_part *wordparts, char *line, int is_op)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (NULL);
	word->parts = wordparts;
	if (line && is_op == 1)
		word->join_next = true;
	else
		word->join_next = false;
	return (word);
}

void	slice_words(t_word_part **p, char *line, int *s, t_quote_mode q)
{
	if (s[1] > s[0])
		parts_add(p, parts(ft_strndup(&line[s[0]], s[1] - s[0]), q));
}

t_quote_mode	ft_getquote(char c)
{
	t_quote_mode	q;

	if (c == '\"')
		q = Q_DOUBLE;
	else if (c == '\'')
		q = Q_SINGLE;
	else
		q = Q_NONE;
	return (q);
}

int	process_char(char *line, int *s, t_quote_mode *q, t_word_part **p)
{
	char	c;

	c = line[s[1]];
	if (*q == Q_NONE)
	{
		if (c == '\'' || c == '\"')
		{
			slice_words(p, line, s, *q);
			*q = ft_getquote(c);
			s[0] = s[1] + 1;
		}
		else if (c == ' ' || is_op(line, s[1]))
			return (1);
	}
	else if ((*q == Q_DOUBLE && c == '\"') || (*q == Q_SINGLE && c == '\''))
	{
		slice_words(p, line, s, *q);
		*q = Q_NONE;
		s[0] = s[1] + 1;
	}
	return (0);
}

int	handle_words(char *line, int i, t_token **list)
{
	int				s[2];
	t_quote_mode	q;
	t_word_part		*p;

	s[0] = i;
	s[1] = i;
	q = Q_NONE;
	p = NULL;
	while (line[s[1]])
	{
		if (process_char(line, s, &q, &p))
			break ;
		s[1]++;
	}
	if (q != Q_NONE)
		return (printf("syntax error: unclosed quote\n"), -1);
	slice_words(&p, line, s, q);
	token_add_back(list, create_new_token(ft_getword(p,
				&line[s[1]], is_op(line, s[1])), TOK_WORD));
	return (s[1]);
}
