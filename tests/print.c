/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihzhang <yihzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:05:30 by yihzhang          #+#    #+#             */
/*   Updated: 2026/03/25 18:13:04 by yihzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_type_name(t_token_type type)
{
	if (type == TOK_WORD)
		return ("TOK_WORD");
	if (type == TOK_PIPE)
		return ("TOK_PIPE");
	if (type == TOK_REDIR_IN)
		return ("TOK_REDIR_IN");
	if (type == TOK_REDIR_OUT)
		return ("TOK_REDIR_OUT");
	if (type == TOK_APPEND)
		return ("TOK_APPEND");
	if (type == TOK_HEREDOC)
		return ("TOK_HEREDOC");
	if (type == TOK_AND)
		return ("TOK_AND");
	if (type == TOK_OR)
		return ("TOK_OR");
	if (type == TOK_LPAREN)
		return ("TOK_LPAREN");
	if (type == TOK_RPAREN)
		return ("TOK_RPAREN");
	if (type == TOK_EOF)
		return ("TOK_EOF");
	return ("TOK_INVALID");
}

void	print_tokens(t_token *list)
{
	t_token *tmp;

	tmp = list;
    printf("--- TOKEN LIST ---\n");
    while (tmp)
    {
        // Use %s and call your dictionary function!
        printf("Type: %-14s | Value: [%s]\n", get_type_name(tmp->type), tmp->value);
        tmp = tmp->next;
    }
    printf("------------------\n\n");
}