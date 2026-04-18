/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <loiczhao@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:30:29 by lozhao            #+#    #+#             */
/*   Updated: 2026/04/18 18:08:38 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

static t_ast	*ms_parse_pipeline_right(t_parser *ps, t_ast *left)
{
	t_ast	*right;
	t_ast	*joined;

	ms_ps_advance(ps);
	right = ms_parse_simple_command(ps);
	if (!right)
	{
		ms_syntax_err_near(ps, "command after '|'");
		ms_ast_clear(&left);
		return (NULL);
	}
	joined = ms_new_binary(AST_PIPE, left, right);
	if (!joined)
	{
		ms_ast_clear(&left);
		ms_ast_clear(&right);
		return (NULL);
	}
	return (joined);
}

t_ast	*ms_parse_pipeline(t_parser *ps)
{
	t_ast	*left;
	t_ast	*next;

	left = ms_parse_simple_command(ps);
	if (!left)
		return (NULL);
	while (ps->cur && ps->cur->type == TOK_PIPE)
	{
		next = ms_parse_pipeline_right(ps, left);
		if (!next)
			return (NULL);
		left = next;
	}
	return (left);
}
