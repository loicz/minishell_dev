/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <loiczhao@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 01:10:03 by lozhao            #+#    #+#             */
/*   Updated: 2026/04/08 03:20:30 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdbool.h>
# include <sys/types.h>
# include "parser.h"
# include "shell.h"

//exec这层只负责暴露执行器模块真正需要共享的接口
//
//我个人比较推荐的设计：
//1. exec消费parser产出的AST
//2. exec不拥有shell全局状态的定义，只通过 t_shell * 使用它
//3. expand / redirection / builtin 都是 exec 之前或exec过程中会调用的子模块
//4. 不在这个头文件里重新定义env的真实存储结构(真实存储结构我放在env.h里)
//
//这样可以避免：
//- exec.h 和 env.h / signal.h / shell.h 互相缠绕
//- 每个模块各自维护一份上下文定义



//builtin先做成枚举，会比单纯is_builtin(char *)方便后续操作
//好处是：
//避免反复strcmp
//parent builtin / child builtin 的判断更清晰
//dispatch更干净

typedef enum e_builtin_id
{
	BI_NONE,
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT
}	t_builtin_id;


//执行期的临时IO状态
//
//这不是shell全局状态，而是“一次执行过程中”的局部上下文
//例如parent builtin做redirection 时，需要先保存 stdin/stdout，
//执行后再恢复

typedef struct s_exec_io
{
	int	saved_stdin;
	int	saved_stdout;
	int	in_fd;
	int	out_fd;
}	t_exec_io;


//核心
//execute_ast():
//AST 总入口，根据 node->type 分派：
//- AST_CMD      -> execute_cmd()
//- AST_PIPE     -> execute_pipe()
//- AST_AND/OR   -> execute_logical()
//- AST_SUBSHELL -> execute_subshell()
//这些 AST 类型已经在 parser.h 里存在乐


int				execute_ast(t_ast *node, t_shell *sh);
int				execute_cmd(t_ast *node, t_shell *sh);
int				execute_pipe(t_ast *node, t_shell *sh);
int				execute_logical(t_ast *node, t_shell *sh);
int				execute_subshell(t_ast *node, t_shell *sh);


//expansion桥接,这个部分建议不要放在exec里，最好拆到expand里，
//你可以看看你来做expand还是我来做，你根据你的精力计划一下
//parser目前保留的是shell level 结构：
//    t_cmd.argv_words -> t_word **
//    t_redir.target   -> t_word *
//
//所以exec不能直接把 AST_CMD 当成最终 argv 使用
//必须先经过expand，把shell word 变成真正可执行的 argv / path
//
//我建议由expand模块提供桥接函数，exec在执行前调用它们
char			**expand_cmd_argv(t_cmd *cmd, t_shell *sh);
char			*expand_redir_target(t_word *target, t_shell *sh);


//path解决方案
//get_exec_path():
//    根据命令名和 PATH 寻找可执行文件绝对路径
//
//find_path_value():
//    从 shell 环境中拿到 PATH 的值
//
//注意：
//建议读取 shell 的权威环境结构，而不是一直依赖 char **envp


char			*get_exec_path(const char *cmd, t_shell *sh);
char			*find_path_value(t_shell *sh);


//重定向
// apply_redirections():
//     对redir链表逐个应用open/dup2/close
//
// save_stdio():
//     parent builtin执行前保存当前stdin/stdout
//
// restore_stdio():
//     parent builtin执行后恢复shell原始 stdin/stdout
//
// heredoc 的输入fd已经在 parser/redir 结构里有heredoc_fd 字段，
// exec 这里只负责消费，不负责重新定义heredoc数据结构


int				save_stdio(t_exec_io *io);
void			restore_stdio(t_exec_io *io);
int				apply_redirections(t_redir *redirs, t_shell *sh);


//Builtin
//builtin 分三步：
//1. 识别是什么 builtin
//2. 判断它是否必须在parent执行
//3. 真正 dispatch 到对应 builtin 实现
//
//parent builtin的典型例子：
//    cd / export / unset / exit
//
//因为它们会影响主shell状态，不能只在child里改


t_builtin_id	get_builtin_id(const char *cmd);
bool			is_builtin_name(const char *cmd);
bool			is_parent_builtin(t_builtin_id id);
int				run_builtin(t_builtin_id id, char **argv, t_shell *sh);


//helper
//这些helper也不是必须都在第一版实现，可以先把接口定下来的话，
//后面execute_cmd / execute_pipe这些会更整齐

int				exec_external(char **argv, t_shell *sh);
int				wait_pipeline(pid_t last_pid);

//一些你自己会用到的工具函数，这里只是例子，你根据你的需求加就好了
void			free_str_arr(char **arr);
void			error_msg(const char *cmd, const char *msg);

#endif
