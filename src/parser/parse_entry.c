/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <loiczhao@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:29:35 by lozhao            #+#    #+#             */
/*   Updated: 2026/04/14 11:56:01 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

void	ms_ps_advance(t_parser *ps)
{
	if (!ps || !ps->cur)
		return ;
	ps->cur = ps->cur->next;
}

//entry for mandatory
t_ast	*ms_parse_tokens(t_token *tokens)
{
	t_parser	ps;
	t_ast		*root;

	ps.cur = tokens;
	if (!ps.cur)
		return (NULL);
	root = ms_parse_pipeline(&ps);
	if (!root)
	{
		if (ps.cur)
			ms_syntax_err_near(&ps, "command or pipeline");
		return (NULL);
	}
	if (ps.cur)
	{
		ms_syntax_err_near(&ps, "unexpected token after pipeline");
		ms_ast_clear(&root);
		return (NULL);
	}
	return (root);
}
