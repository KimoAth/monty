#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

typedef struct
{
        int data[STACK_SIZE];
        int top;
} Stack;

void initStack(Stack *stack)
{
        stack->top = -1;
}

int isEmpty(Stack *stack)
{
        return stack->top == -1;
}

int isFull(Stack *stack)
{
        return stack->top == STACK_SIZE - 1;
}

void push(Stack *stack, int value)
{
        if (isFull(stack))
        {
                printf("Stack is full, cannot push.\n");
                exit(EXIT_FAILURE);
        }
        stack->data[++stack->top] = value;
}

int pop(Stack *stack)
{
        if (isEmpty(stack))
        {
                printf("Stack is empty, cannot pop.\n");
                exit(EXIT_FAILURE);
        }
        return stack->data[stack->top--];
}

void pall(Stack *stack)
{
        int i;

        for (i = stack->top; i >= 0; i--)
        {
                printf("%d\n", stack->data[i]);
        }
}

int main()
{
        Stack stack;
        char line[100];
        int line_number = 1;
        FILE *file = fopen("bytecodes/00.m", "r");

        if (file == NULL)
        {
                printf("File not found.\n");
                return 1;
        }

        initStack(&stack);

        while (fgets(line, sizeof(line), file) != NULL)
        {
                char opcode[10];
                int value;

                line[strcspn(line, "$\n")] = '\0';

                if (sscanf(line, "%s %d", opcode, &value) == 2 && strcmp(opcode, "push") == 0)
                {
                        push(&stack, value);
                }
                else if (strcmp(opcode, "pall") == 0)
                {
                        pall(&stack);
                }
                else
                {
                        printf("Error at line %d: Invalid opcode or arguments.\n", line_number);
                        return 1;
                }

                line_number++;
        }

        fclose(file);
        return 0;
}
