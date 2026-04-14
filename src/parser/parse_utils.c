/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:38:53 by lozhao            #+#    #+#             */
/*   Updated: 2026/04/14 16:21:14 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

bool	ms_tok_starts_redir(t_token *tok)
{
	return (tok && (tok->type == TOK_REDIR_IN
			|| tok->type == TOK_REDIR_OUT
			|| tok->type == TOK_APPEND
			|| tok->type == TOK_HEREDOC));
}

bool	ms_tok_starts_simple_item(t_token *tok)
{
	return ((tok && tok->type == TOK_WORD)
			|| ms_tok_starts_redir(tok));
}

bool	ms_tok_starts_primary(t_token *tok)
{
	return ((tok && tok->type == TOK_LPAREN)
			|| ms_tok_starts_simple_item(tok));
}
