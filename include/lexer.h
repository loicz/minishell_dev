/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihzhang <yihzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:05:55 by yihzhang          #+#    #+#             */
/*   Updated: 2026/04/13 15:51:44 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef enum e_token_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_APPEND,
	TOK_HEREDOC,
	TOK_AND,
	TOK_OR,
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_INVALLID
}t_token_type;

typedef enum e_quote_mode
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote_mode;

typedef struct s_word_part
{
	char				*text;
	t_quote_mode		quote;
	struct s_word_part	*next;
}	t_word_part;

typedef struct s_word
{
	t_word_part	*parts;
	bool		join_next;
}	t_word;

typedef struct s_token
{
	t_word			*word;
	t_token_type	type;
	struct s_token	*prev;
	struct s_token	*next;
}t_token;

void		lex_input(char *line, t_token **list);
int			handle_words(char *line, int i, t_token **list);
int			handle_operator(char *line, int i, t_token **list);
t_word_part	*parts(char *text, t_quote_mode quote);
void		parts_add(t_word_part **list, t_word_part *new_node);
t_token		*create_new_token(t_word *word, t_token_type type);
void		token_add_back(t_token **list, t_token *new_node);
int			is_op(char *line, int i);

void		print_tokens(t_token *list);
int			ft_strncmp(char *line, char *str, int n);
int			ft_strlen(char *str);
char		*ft_strdup(char *str);
char		*ft_strndup(char *str, int n);

#endif
