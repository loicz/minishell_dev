/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <loiczhao@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:40:00 by lozhao            #+#    #+#             */
/*   Updated: 2026/04/15 17:23:10 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

static t_redir_type	ms_redir_typr_fr_token(t_token *tok)
{
	if (tok && tok->type == TOK_REDIR_IN)
		return (R_IN);
	if (tok && tok->type == TOK_REDIR_OUT)
		return (R_OUT);
	if (tok && tok->type == TOK_APPEND)
		return (R_APPEND);
	return (R_HEREDOC);
}

static t_redir	*ms_parse_one_redir(t_parser *ps)
{
	t_redir_type	type;
	t_word			*target;
	t_redir			*redir;

	if (!ps->cur)
		return (NULL);
	type = ms_redir_typr_fr_token(ps->cur);
	ms_ps_advance(ps);
	if (!ps->cur || ps->cur->type != TOK_WORD)
	{
		ms_syntax_err_near(ps, "redirection target");
		return (NULL);
	}
	target = ms_tok_take_word(ps);
	if (!target)
		return (NULL);
	redir = ms_new_redir(type, target);
	if (!redir)
		return (ms_word_clear(&target), NULL);
	if (type == R_HEREDOC)
		redir->heredoc_expand = ms_word_is_quoted(target);
	return (redir);
}

static int	ms_parse_simple_item(t_parser *ps, t_ast *cmd)
{
	t_word	*word;
	t_redir	*redir;

	if (ms_tok_starts_redir(ps->cur))
	{
		redir = ms_parse_one_redir(ps);
		if (!redir)
			return (0);
		if (!ms_cmd_add_redir(cmd, redir))
			return (ms_redir_clear(&redir), 0);
		return (1);
	}
	if (ps->cur && ps->cur->type == TOK_WORD)
	{
		word = ms_tok_take_word(ps);
		if (!word)
			return (0);
		if (!ms_cmd_add_word(cmd, word))
			return (ms_word_clear(&word), 0);
		return (1);
	}
	return (0);
}

static t_ast	*ms_new_cmd(void)
{
	t_ast	*cmd;

	cmd = calloc(1, sizeof(t_ast));
	if (!cmd)
		return (NULL);
	cmd->type = AST_CMD;
	return (cmd);
}

t_ast	*ms_parse_simple_command(t_parser *ps)
{
	t_ast	*node;

	if (!ms_tok_starts_simple_item(ps->cur))
		return (NULL);
	node = ms_new_cmd();
	while (ms_tok_starts_simple_item(ps->cur))
	{
		if (!ms_parse_simple_item(ps, node))
			return (ms_ast_clear(&node), NULL);
	}
	return (node);
}
