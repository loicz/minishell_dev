/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <loiczhao@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 20:44:22 by lozhao            #+#    #+#             */
/*   Updated: 2026/04/18 22:22:31 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "parser.h"

void	ms_word_clear(t_word **word)
{
	t_word_part	*cur;
	t_word_part	*next;

	if (!word || !*word)
		return ;
	cur = (*word)->parts;
	while (cur)
	{
		next = cur->next;
		free(cur->text);
		free(cur);
		cur = next;
	}
	free(*word);
	*word = NULL;
}

void	ms_redir_clear(t_redir **redir)
{
	t_redir	*cur;
	t_redir	*next;

	if (!redir || !*redir)
		return ;
	cur = *redir;
	while (cur)
	{
		next = cur->next;
		if (cur->heredoc_fd >= 0)
			close(cur->heredoc_fd);
		ms_word_clear(&cur->target);
		free(cur);
		cur = next;
	}
	*redir = NULL;
}

void	ms_ast_clear(t_ast **node)
{
	size_t	i;

	if (!node || !*node)
		return ;
	if ((*node)->type == AST_CMD)
	{
		i = 0;
		while (i < (*node)->u.cmd.argc)
		{
			ms_word_clear((*node)->u.cmd.argv_words + i);
			i++;
		}
		free((*node)->u.cmd.argv_words);
		ms_redir_clear(&(*node)->u.cmd.redirs);
	}
	else if ((*node)->type == AST_SUBSHELL)
		ms_ast_clear(&(*node)->u.child);
	else
	{
		ms_ast_clear(&(*node)->u.bin.left);
		ms_ast_clear(&(*node)->u.bin.right);
	}
	free(*node);
	*node = NULL;
}
