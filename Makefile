# ============================================================================== #

NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I include
RM          = rm -f

# --- Core Minishell Sources
# Note: Add all the other src folders here as your team builds them!
SRCS        = src/main.c \
              src/lexer/lexer.c \
			  src/lexer/operator.c \
			  src/lexer/words.c \
              src/utils/str.c

OBJS        = $(SRCS:.c=.o)

# --- Lexer Test Sources
# Notice that we DO NOT include src/main.c here!
LEXER_SRCS  = tests/main_lexer.c\
			  tests/print_lexer.c \
              src/lexer/lexer.c \
			  src/lexer/operator.c \
			  src/lexer/words.c \
              src/utils/str.c

LEXER_OBJS  = $(LEXER_SRCS:.c=.o)
LEXER_EXEC  = test_lexer

# ============================================================================== #

# Default rule: Compiles the final Minishell project
all: $(NAME)

$(NAME): $(OBJS)
	@echo "Building final $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) compiled successfully!"

# just test lexer: make lexer
lexer: $(LEXER_OBJS)
	@echo "Building Lexer Test Environment..."
	$(CC) $(CFLAGS) $(LEXER_OBJS) -o $(LEXER_EXEC)
	@echo "--- RUNNING $(LEXER_EXEC) ---"
	@./$(LEXER_EXEC)

# ============================================================================== #

clean:
	$(RM) $(OBJS) $(LEXER_OBJS)

fclean: clean
	$(RM) $(NAME) $(LEXER_EXEC)

re: fclean all
relexer: clean fclean lexer

.PHONY: all clean fclean re lexer