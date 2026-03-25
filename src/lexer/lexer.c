/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihzhang <yihzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:06:00 by yihzhang          #+#    #+#             */
/*   Updated: 2026/03/25 18:27:05 by yihzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*create_new_token(char *value, t_token_type type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = value;
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

int	is_op(char *line, int i)
{
	if (ft_strncmp(&line[i], "||", 2) == 0
		|| ft_strncmp(&line[i], ">>", 2) == 0
		|| ft_strncmp(&line[i], "<<", 2) == 0
		|| ft_strncmp(&line[i], "&&", 2) == 0
		|| ft_strncmp(&line[i], "|", 1) == 0
		|| ft_strncmp(&line[i], ">", 1) == 0
		|| ft_strncmp(&line[i], "<", 1) == 0
		|| ft_strncmp(&line[i], "(", 1) == 0
		|| ft_strncmp(&line[i], ")", 1) == 0)
		return (1);
	return (0);
}

int	add_op(t_token **list, char *op, t_token_type type, int len)
{
	token_add_back(list, create_new_token(ft_strdup(op), type));
	return (len);
}

int	handle_operator(char *line, int i, t_token **list)
{
	if (ft_strncmp(&line[i], "||", 2) == 0)
		return (i + add_op(list, "||", TOK_OR, 2));
	if (ft_strncmp(&line[i], ">>", 2) == 0)
		return (i + add_op(list, ">>", TOK_APPEND, 2));
	if (ft_strncmp(&line[i], "<<", 2) == 0)
		return (i + add_op(list, "<<", TOK_HEREDOC, 2));
	if (ft_strncmp(&line[i], "&&", 2) == 0)
		return (i + add_op(list, "&&", TOK_AND, 2));
	if (ft_strncmp(&line[i], "|", 1) == 0)
		return (i + add_op(list, "|", TOK_PIPE, 1));
	if (ft_strncmp(&line[i], ">", 1) == 0)
		return (i + add_op(list, ">", TOK_REDIR_OUT, 1));
	if (ft_strncmp(&line[i], "<", 1) == 0)
		return (i + add_op(list, "<", TOK_REDIR_IN, 1));
	if (ft_strncmp(&line[i], "(", 1) == 0)
		return (i + add_op(list, "(", TOK_LPAREN, 1));
	if (ft_strncmp(&line[i], ")", 1) == 0)
		return (i + add_op(list, ")", TOK_RPAREN, 1));
	return (i);
}

int	handle_words(char *line, int i, t_token **list)
{
	int	len;
	int	quote;

	len = 0;
	quote = 0;
	while (line[i + len])
	{
		if (quote == 0 && (line[i + len] == '\'' || line[i + len] == '\"'))
			quote = line[i + len];
		else if (quote == line[i + len])
			quote = 0;
		else if (quote == 0 && (line[i + len] == ' ' || is_op(line, i + len)))
			break ;
		len++;
	}
	if (quote != 0)
	{
		printf("syntax error: unclosed quote\n");
		return (-1);
	}
	token_add_back(list, create_new_token(ft_strndup(&line[i], len), TOK_WORD));
	return (i + len);
}
// start: no space && no op
// end: space not inside the quote || op 

void	lex_input(char *line, t_token **list)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0')
			break ;
		if (is_op(line, i))
			i = handle_operator(line, i, list);
		else
			i = handle_words(line, i, list);
	}
}
