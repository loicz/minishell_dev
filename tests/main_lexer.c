/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihzhang <yihzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:18:25 by yihzhang          #+#    #+#             */
/*   Updated: 2026/03/25 18:03:33 by yihzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main() 
{
    t_token *list = NULL;

    printf("TEST 1: Normal Space\nls -l >> \"my files.txt\" | grep 'hidden'\n");
    lex_input("ls -l >> \"my files.txt\" | grep 'hidden'", &list);
    print_tokens(list);
	list = NULL;
	
    printf("TEST 2: The Glued Word\necho \"hello\"world(yihuan)\n");
    lex_input("echo \"hello\"world(yihuan)", &list);
    print_tokens(list);
    list = NULL;

    printf("TEST 3: Operators\ncat|grep\n");
    lex_input("cat|grep || << < >> > (|)", &list);
    print_tokens(list);
    list = NULL;

    printf("TEST 4: Single quote should prevent the shell from interpreting anything\n \'Hello $USER | wc\'\n");
	lex_input("\'Hello $USER | wc\'", &list);
    print_tokens(list);
    list = NULL;

    printf("TEST 5: Double quote should prevent the shell from interpreting anything except $\n echo \"Hello $USER | wc\"\n");
	lex_input("echo \"Hello $USER | wc\"", &list);
    print_tokens(list);
    list = NULL;

    return 0;
}