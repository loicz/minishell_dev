#include "lexer.h"

char    *get_type_name(t_token_type type)
{
    if (type == TOK_WORD) return ("TOK_WORD");
    if (type == TOK_PIPE) return ("TOK_PIPE");
    if (type == TOK_REDIR_IN) return ("TOK_REDIR_IN");
    if (type == TOK_REDIR_OUT) return ("TOK_REDIR_OUT");
    if (type == TOK_APPEND) return ("TOK_APPEND");
    if (type == TOK_HEREDOC) return ("TOK_HEREDOC");
    if (type == TOK_AND) return ("TOK_AND");
    if (type == TOK_OR) return ("TOK_OR");
    if (type == TOK_LPAREN) return ("TOK_LPAREN");
    if (type == TOK_RPAREN) return ("TOK_RPAREN");
    if (type == TOK_EOF) return ("TOK_EOF");
    return ("TOK_INVALID");
}

// NEW: A dictionary to translate the quote tags into human text!
char    *get_quote_name(t_quote_mode quote)
{
    if (quote == Q_NONE) return ("Q_NONE");
    if (quote == Q_SINGLE) return ("Q_SINGLE");
    if (quote == Q_DOUBLE) return ("Q_DOUBLE");
    return ("UNKNOWN");
}

void    print_tokens(t_token *list)
{
    t_token     *tmp;
    t_word_part *part;

    tmp = list;
    printf("--- TOKEN LIST ---\n");
    while (tmp)
    {
        printf("Type: %-14s", get_type_name(tmp->type));
        
        // 1. Is it a WORD? Open the Box!
        if (tmp->word)
        {
            // Print the parser flag
            printf(" | join_next: %d | Parts: ", tmp->word->join_next);
            
            // Iterate through the slices inside the box
            part = tmp->word->parts;
            while (part)
            {
                printf("[%s](%s) ", part->text, get_quote_name(part->quote));
                if (part->next)
                    printf("➔ ");
                part = part->next;
            }
        }
        // 2. Is it an OPERATOR? It has no box!
        else
        {
            printf(" | (Operator: word is NULL)");
        }
        
        printf("\n");
        tmp = tmp->next;
    }
    printf("------------------\n\n");
}