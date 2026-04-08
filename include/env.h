/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <loiczhao@outlook.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 02:56:36 by lozhao            #+#    #+#             */
/*   Updated: 2026/04/08 03:19:03 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h>

//这层负责环境变量链表本身
//设计目标：
//1.让export/unset/env/path查询都围绕同一套权威数据结构
//2.让execve前可以把链表序列化成char **envp
//3.所有权清晰，失败路径简明
//---------------------------------------------------
//value 可以为 NULL
//因为 shell 里存在这种情况：
//    export NAME
//这表示：
//- NAME 已经在 shell 里存在一个“标识符”
//- 但它可能还没有显式赋值
//exported 表示它是否应被当作导出变量处理

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			exported;
	struct s_env	*next;
}	t_env;

//构造 / 清理
//从系统给的 envp 构造内部链表
//典型用法：
//    sh->env = ms_env_from_envp(envp);
//返回：
//- 成功：链表头
//- 失败：NULL

t_env	*ms_env_from_envp(char **envp);

//单独创建一个 env 节点
//key / value 都会被函数内部复制
//value 可以传 NULL

t_env	*ms_env_new(const char *key, const char *value, bool exported);


//释放整条 env 链表
void	ms_env_clear(t_env **env);

//按 key 查找节点
//
//返回：
//- 找到：对应节点
//- 找不到：NULL
t_env	*ms_env_find(t_env *env, const char *key);

//取某个 key 的 value
//注意：
//- 返回的是“链表内部持有的指针”，不是新分配的字符串
//- 调用者不要 free
//- 找不到时返回 NULL
//典型用途：
//    PATH 查询
//    expand 时处理 $VAR

char	*ms_env_get(t_env *env, const char *key);

//判断用key是否是合法shell标识符
//一般用于：
//    export
//    unset
//例如：
//- "PATH"      -> true
//- "_USER42"   -> true
//- "42USER"    -> false
//- "A-B"       -> false
bool	ms_env_key_is_valid(const char *key);


//修改
//设置或更新一个变量
//规则建议：
//- 如果 key 不存在：创建新节点
//- 如果 key 已存在：更新 value / exported
//value 可以为 NULL
//返回：
//- 成功：1
//- 失败：0
int		ms_env_set(t_env **env, const char *key,
			const char *value, bool exported);

//删除一个变量
//返回：
//- 成功删除：1
//- 原本不存在：1
//- 内部异常：0
//之所以找不到也返回成功，是因为shell的unset通常不把
//“变量不存在”视为致命错误
int		ms_env_unset(t_env **env, const char *key);

// 序列化
// 把内部链表转成 execve 需要的 char **envp
// 约定建议：
// - 只导出 exported == true 的项
// - 每个元素形如 "KEY=VALUE"
// 返回的数组和里面的每个字符串都由调用者拥有，后续应自行 free
// 典型用法：
//     envp_arr = ms_env_to_envp(sh->env);
//     execve(path, argv, envp_arr);
//     free_str_arr(envp_arr);
char	**ms_env_to_envp(t_env *env);

#endif
