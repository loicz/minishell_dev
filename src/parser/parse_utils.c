/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:38:53 by lozhao            #+#    #+#             */
/*   Updated: 2026/04/14 12:22:01 by lozhao           ###   ########.fr       */
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
