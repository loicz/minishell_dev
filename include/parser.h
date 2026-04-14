/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:52:54 by lozhao            #+#    #+#             */
/*   Updated: 2026/04/14 16:21:05 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include "lexer.h"
# include "shell.h"

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	t_word			*target;
	int				heredoc_fd;
	bool			heredoc_expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	t_word	**argv_words;
	size_t	argc;
	t_redir	*redirs;
}	t_cmd;

typedef enum e_ast_type
{
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_SUBSHELL
}	t_ast_type;

typedef struct s_ast	t_ast;
typedef struct s_ast
{
	t_ast_type			type;
	union u_ast_data
	{
		t_cmd			cmd;
		struct s_ast_bin
		{
			t_ast		*left;
			t_ast		*right;
		}bin;
		struct s_ast	*child;
	}	u;
}	t_ast;

typedef struct s_parser
{
	t_token	*cur;
	t_shell	*sh;
}	t_parser;

//part of principal functions that I will use, there will be more than this
t_ast	*ms_parse_tokens(t_token *tokens);
t_ast	*ms_parse_simple_command(t_parser *ps);
t_ast	*ms_parse_pipeline(t_parser *ps);
t_ast	*ms_parse_logical_bonus(t_parser *ps);

void	ms_ps_advance(t_parser *ps);
t_ast	*ms_parse_tokens(t_token *tokens);

//parse adaptors
t_word	*ms_tok_peek_word(t_token *tok);
t_word	*ms_tok_take_word(t_parser *ps);
bool	ms_word_is_quoted(t_word *word);
void	ms_syntax_err_near(t_parser *ps, const char *context);

//parse utils
bool	ms_tok_starts_redir(t_token *tok);
bool	ms_tok_starts_simple_item(t_token *tok);
bool	ms_tok_starts_primary(t_token *tok);
#endif
