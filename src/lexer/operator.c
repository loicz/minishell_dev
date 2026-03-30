/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihzhang <yihzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:52:54 by yihzhang          #+#    #+#             */
/*   Updated: 2026/03/30 21:05:31 by yihzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

int	add_op(t_token **list, t_token_type type, int len)
{
	token_add_back(list, create_new_token(NULL, type));
	return (len);
}

int	handle_operator(char *line, int i, t_token **list)
{
	if (ft_strncmp(&line[i], "||", 2) == 0)
		return (i + add_op(list, TOK_OR, 2));
	if (ft_strncmp(&line[i], ">>", 2) == 0)
		return (i + add_op(list, TOK_APPEND, 2));
	if (ft_strncmp(&line[i], "<<", 2) == 0)
		return (i + add_op(list, TOK_HEREDOC, 2));
	if (ft_strncmp(&line[i], "&&", 2) == 0)
		return (i + add_op(list, TOK_AND, 2));
	if (ft_strncmp(&line[i], "|", 1) == 0)
		return (i + add_op(list, TOK_PIPE, 1));
	if (ft_strncmp(&line[i], ">", 1) == 0)
		return (i + add_op(list, TOK_REDIR_OUT, 1));
	if (ft_strncmp(&line[i], "<", 1) == 0)
		return (i + add_op(list, TOK_REDIR_IN, 1));
	if (ft_strncmp(&line[i], "(", 1) == 0)
		return (i + add_op(list, TOK_LPAREN, 1));
	if (ft_strncmp(&line[i], ")", 1) == 0)
		return (i + add_op(list, TOK_RPAREN, 1));
	return (i);
}
