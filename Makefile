# ============================================================================== #
#                                 VARIABLES                                      #
# ============================================================================== #

NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I include
RM          = rm -f

# --- Core Minishell Sources (What your teammate works on) ---
# Note: Add all the other src folders here as your team builds them!
SRCS        = src/main.c \
              src/lexer/lexer.c \
              src/utils/str.c

OBJS        = $(SRCS:.c=.o)

# --- Lexer Test Sources (What YOU work on) ---
# Notice that we DO NOT include src/main.c here!
LEXER_SRCS  = tests/main_lexer.c\
			  tests/print.c \
              src/lexer/lexer.c \
              src/utils/str.c

LEXER_OBJS  = $(LEXER_SRCS:.c=.o)
LEXER_EXEC  = test_lexer

# ============================================================================== #
#                                 RULES                                          #
# ============================================================================== #

# Default rule: Compiles the final Minishell project
all: $(NAME)

$(NAME): $(OBJS)
	@echo "Building final $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) compiled successfully!"

# --- YOUR CUSTOM TEST RULE ---
# Run this by typing: make lexer
lexer: $(LEXER_OBJS)
	@echo "Building Lexer Test Environment..."
	$(CC) $(CFLAGS) $(LEXER_OBJS) -o $(LEXER_EXEC)
	@echo "--- RUNNING $(LEXER_EXEC) ---"
	@./$(LEXER_EXEC)

# ============================================================================== #
#                                HOUSEKEEPING                                    #
# ============================================================================== #

# Cleans up all the .o files for both the main project and the tests
clean:
	$(RM) $(OBJS) $(LEXER_OBJS)

# Cleans up the .o files AND the executables (minishell + tester)
fclean: clean
	$(RM) $(NAME) $(LEXER_EXEC)

# Completely rebuilds the main project
re: fclean all
relexer: clean fclean lexer

# Tells make that these aren't files, they are commands!
.PHONY: all clean fclean re lexer