# In2Post

**Introduction** The conversion of infix expressions (where operators are placed between operands, e.g., "3 + 4") to postfix expressions (where operators follow operands, e.g., "3 4 +") is a fundamental concept in computer science. The evaluation of postfix notation is efficient as it eliminates the need for parentheses and follows a straightforward left-to-right execution order. This project aims to implement an infix-to-postfix converter and an evaluator for arithmetic expressions.

**Implementation Details** The program is implemented in C++ and follows a structured approach with the following key components:
•	Token Classification: The program identifies numbers, operators, and parentheses using helper functions. 
•	Operator Precedence Handling: Operators are assigned precedence values with multiplication and division having higher precedence than addition and subtraction. A stack is used to manage operator precedence during the conversion process.
•	Infix to Postfix Conversion: This process employs a stack-based algorithm where operators are pushed and popped based on their precedence. Parentheses are handled separately to ensure a correct grouping of operations.
•	Postfix Evaluation: The postfix expression is evaluated using a stack to manage operands. 
•	Error Handling: The program includes error detection mechanisms to catch invalid expressions such as unbalanced parentheses, invalid tokens, and division by zero.

**Algorithmic Approach** The following steps outline the core algorithm used in the implementation:
1.	Infix to Postfix Conversion:
o	Scan the infix expression token by token.
o	If the token is an operand it will append it to the output.
o	If the token is an operator, pop operators from the stack with higher or equal precedence and append them to the output before pushing the new operator onto the stack.
o	If the token is a left parenthesis, push it onto the stack.
o	If the token is a right parenthesis, pop operators until a left parenthesis is encountered.
o	After processing all tokens, pop any remaining operators from the stack.
2.	Postfix Evaluation:
o	Scan the postfix expression token by token.
o	Push it onto the stack if the token is an operand.
o	If the token is an operator, pop the top two operands, perform the operation, and push the result back onto the stack.
o	The final result is found at the top of the stack after processing all the tokens.

**Results** The program successfully converts infix expressions into postfix notation and evaluates the result correctly. Sample runs demonstrate its ability to handle various expressions including those with multiple operators and nested parentheses. The error handling mechanisms effectively catch and report syntax errors enhancing robustness.

**Conclusion** This project effectively implements an infix-to-postfix converter and evaluator using a stack-based approach. The structured error handling and operator precedence management ensure the correct evaluation of expressions. 
