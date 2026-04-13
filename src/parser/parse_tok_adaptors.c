/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tok_adaptors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <loiczhao@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:28:35 by lozhao            #+#    #+#             */
/*   Updated: 2026/04/13 16:21:54 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"
#include "parser.h"

static const char	*ms_tok_name(t_token *tok)
{
	if (!tok)
		return ("end-of-input");
	if (tok->type == TOK_WORD)
		return ("WORD");
	if (tok->type == TOK_PIPE)
		return ("|");
	if (tok->type == TOK_REDIR_IN)
		return ("<");
	if (tok->type == TOK_REDIR_OUT)
		return (">");
	if (tok->type == TOK_APPEND)
		return (">>");
	if (tok->type == TOK_HEREDOC)
		return ("<<");
	if (tok->type == TOK_AND)
		return ("&&");
	if (tok->type == TOK_OR)
		return ("||");
	if (tok->type == TOK_LPAREN)
		return ("(");
	if (tok->type == TOK_RPAREN)
		return (")");
	return ("EOF");
}

t_word	*ms_tok_peek_word(t_token *tok)
{
	if (!ms_tok_is_end(tok))
		return (NULL);
	return (tok->word);
}

t_word	*ms_tok_take_word(t_parser *ps)
{
	t_token	*tok;
	t_word	*word;

	tok = ps->cur;
	if (!ms_tok_is_word(tok) || !tok->word)
		return (NULL);
	word = tok->word;
	tok->word = NULL;
	ms_ps_advance(ps);
	return (word);
}

bool	ms_word_is_quoted(t_word *word)
{
	t_word_part	*part;

	if (!word)
		return (false);
	part = word->parts;
	while (part)
	{
		if (part->quote == Q_NONE)
			return (true);
		part = part->next;
	}
	return (false);
}

void	ms_syntax_err_near(t_parser *ps, const char *context)
{
	fprintf(stderr, "syntax error near '%s'",
		 ms_tok_name(ps->cur));
	if (context && *context)
		fprintf(stderr, " (expected %s)", context);
	fprintf(stderr, "\n");
}




