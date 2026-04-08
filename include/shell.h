/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <loiczhao@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 01:23:46 by lozhao            #+#    #+#             */
/*   Updated: 2026/04/08 03:23:00 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdbool.h>
# include <signal.h>

//具体的定义在env.h里，这里只做前向声明
typedef struct s_env	t_env;

//minishell可以并且只能使用一个全局变量，我只声明在这里
//真正的定义会方到需要的那个.c文件里
extern volatile sig_atomic_t	g_signal;

//t_shell是整个全局上下文，这样就不是你的执行器里的一个局部上下文
//因为exec也好，expand也好，builtin，env，signal等都要使用一份
//共享的shell状态
typedef struct s_shell
{
	t_env	*env;
	int		last_status;
	bool	running;
	bool	interactive;
}	t_shell;

#endif
