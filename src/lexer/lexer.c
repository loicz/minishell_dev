/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihzhang <yihzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:06:00 by yihzhang          #+#    #+#             */
/*   Updated: 2026/04/08 15:48:10 by yihzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_word_part	*parts(char *text, t_quote_mode quote)
{
	t_word_part	*node;

	node = malloc(sizeof(t_word_part));
	if (!node)
		return (NULL);
	node->text = text;
	node->quote = quote;
	node->next = NULL;
	return (node);
}

void	parts_add(t_word_part **list, t_word_part *new_node)
{
	t_word_part	*tmp;

	if (!list || !new_node)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	tmp = *list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
}

t_token	*create_new_token(t_word *word, t_token_type type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->word = word;
	node->type = type;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	token_add_back(t_token **list, t_token *new_node)
{
	t_token	*tmp;

	if (!list || !new_node)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	tmp = *list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_node;
	new_node->prev = tmp;
}

int	lex_input(char *line, t_token **list)
{
	int	i;
	int	next_i;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0')
			break ;
		if (is_op(line, i))
			next_i = handle_operator(line, i, list);
		else
			next_i = handle_words(line, i, list);
		if (next_i < 0)
			return (0);
		i = next_i;
	}
	return (1);
}
