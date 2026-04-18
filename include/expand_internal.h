/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <loiczhao@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:32:16 by lozhao            #+#    #+#             */
/*   Updated: 2026/04/18 17:09:22 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_INTERNAL_H
# define EXPAND_INTERNAL_H

# include <dirent.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "env.h"
# include "exec.h"

//动态字符串缓冲区
typedef struct s_xbuf
{
	char	*data;
	size_t	len;
	size_t	cap;
}	t_xbuf;

//word展开后的片段链表
typedef struct s_seg
{
	char			*text;
	bool			quoted;
	struct s_seg	*next;
}	t_seg;

//动态字符串数组，为了生成 char **argv
typedef struct s_strvec
{
	char	**items;
	size_t	count;
	size_t	cap;
}	t_strvec;

//函数TBD
#endif
