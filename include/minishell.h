/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihzhang <yihzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:05:55 by yihzhang          #+#    #+#             */
/*   Updated: 2026/03/25 18:06:20 by yihzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

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
	TOK_EOF,
	TOK_INVALLID
}t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	// t_quote_type	quote;
	struct s_token	*prev;
	struct s_token	*next;
}t_token;

void	lex_input(char *line, t_token **list);

void	print_tokens(t_token *list);
int		ft_strncmp(char *line, char *str, int n);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
char	*ft_strndup(char *str, int n);

#endif