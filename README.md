### This is the ongoing 42 minishell project, with team members `Yihuan Zhang` and `Loic Zhao`.


# Lexer
| Original Command (User Input) | Tokenized Result (Linked List) |
| :--- | :--- |
| `ls -l` | `[ls]` ➔ `[-l]` |
| `echo "hello world"` | `[echo]` ➔ `["hello world"]` |
| `echo "hello"world` | `[echo]` ➔ `["hello"world]` |
| `cat\|grep` | `[cat]` ➔ `[\|]` ➔ `[grep]` |
| `echo "hello"          world`| `[echo]` ➔ `["hello"]` ➔ `[world]` |
| `ls -l >> "my files.txt" \| grep 'hidden'` | `[ls]` ➔ `[-l]` ➔ `[>>]` ➔ `["my files.txt"]` ➔ `[\|]` ➔ `[grep]` ➔ `['hidden']` |
