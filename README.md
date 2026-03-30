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


Metacognition_pain-free learning framework_learn how to find answers

Self-Learning Architecture

1. understand waht's the problem
child-friendly human language to explain(give me examples and use metaphors) what the subject want, what problems i need to solve and what knowledge i should equip for solving the problems
2. equip myself with necessary new knowledge
train me to learn the "Black Box"
3. build the structure to solve the problems
4. under the structure to build a MVP in practice
4. 