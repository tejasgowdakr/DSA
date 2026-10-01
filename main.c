#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 20

struct stack {
    int top;
    char data[SIZE];
};

typedef struct stack STACK;

void push(STACK *s, char item) {
    s->data[++(s->top)] = item;
}

char pop(STACK *s) {
    return s->data[(s->top)--];
}

int preced(char symbol) {
    switch (symbol) {
        case '^': return 5;
        case '*':
        case '/': return 3;
        case '+':
        case '-': return 1;
    }
    return 0;
}

void infixtopostfix(STACK *s, char infix[]) {
    int i = 0, j = 0;
    char symbol;
    char postfix[SIZE];

    push(s, '#');

    while ((symbol = infix[i++]) != '\0') {
        if (isalnum(symbol)) {
            postfix[j++] = symbol;
        } else if (symbol == '(') {
            push(s, symbol);
        } else if (symbol == ')') {
            while (s->data[s->top] != '(') {
                postfix[j++] = pop(s);
            }
            pop(s); // remove '('
        } else {
            while (preced(s->data[s->top]) >= preced(symbol)) {
                postfix[j++] = pop(s);
            }
            push(s, symbol);
        }
    }

    while (s->data[s->top] != '#') {
        postfix[j++] = pop(s);
    }

    postfix[j] = '\0';
    printf("\nPostfix expression is: %s", postfix);
}

int main() {
    char infix[20];
    STACK s;
    s.top = -1;

    printf("\nRead infix expression: ");
    scanf("%s", infix);

    infixtopostfix(&s, infix);

    return 0;
}
