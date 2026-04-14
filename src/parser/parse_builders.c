/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:32:36 by lozhao            #+#    #+#             */
/*   Updated: 2026/04/14 18:13:20 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include <stddef.h>
#include <stdlib.h>

t_ast	*ms_new_binary(t_ast_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type == type;
	node->u.bin.left = left;
	node->u.bin.right = right;
	return (node);
}

t_ast	*ms_new_subshell(t_ast *child)
{
	t_ast	*node;

	node = calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = AST_SUBSHELL;
	node->u.child = child;
	return (node);
}

t_redir	*ms_new_redir(t_redir_type type, t_word *target)
{
	t_redir	*redir;

	redir = calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->target = target;
	redir->heredoc_fd = -1;
	redir->heredoc_expand = true;
	return (redir);
}

int	ms_cmd_add_word(t_ast *cmd, t_word *word)
{
	size_t	new_count;
	size_t	i;
	t_word	**new_tab;

	if (!cmd || cmd->type != AST_CMD || !word)
		return (0);
	new_count = cmd->u.cmd.argc + 1;
	new_tab = calloc(new_count + 1, sizeof(t_word *));
	if (!new_tab)
		return (0);
	i = 0;
	while (i < cmd->u.cmd.argc)
	{
		new_tab[i] = cmd->u.cmd.argv_words[i];
		i++;
	}
	free(cmd->u.cmd.argv_words);
	cmd->u.cmd.argv_words[cmd->u.cmd.argc] = word;
	cmd->u.cmd.argv_words = new_tab;
	cmd->u.cmd.argc = new_count;
	return (1);
}

int	ms_cmd_add_redir(t_ast *cmd, t_redir *redir)
{
	t_redir	*cur;

	if (!cmd || cmd->type != AST_CMD || !redir)
		return (0);
	if (!cmd->u.cmd.redirs)
	{
		cmd->u.cmd.redirs = redir;
		return (1);
	}
	cur = cmd->u.cmd.redirs;
	while (cur->next)
		cur = cur->next;
	cur->next = redir;
	return (1);
}
