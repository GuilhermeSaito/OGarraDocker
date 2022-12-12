#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

void printStack(struct Stack* stack) {
    for (int i = 0; i < stack->capacity; i++)
         Serial.print(stack->array[i]);
}

int isFull(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

void push(struct Stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    //printf("%d pushed to stack\n", item);
}

int pop(struct Stack* stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

int top(struct Stack* stack)
{
    if (isEmpty(stack))
        return INT_MAX;
    return stack->array[stack->top];
}

int patio_cheio(Stack** p) {
    for (int i = 1; i < 5; i++) {
        if (!(isFull(p[i])))
            return 0;
    }

    return 1;
}

int can_add_container(Stack** p) {
    // j =  colunas, i = linhas
    for (int j = 1; j < 5; j++) {
        for (int i = 2; i < p[j]->capacity; i++) {
            if (p[i - 1][j].array[i] < p[i][j].array[i]) {
                printf("Nao foi possivel inserir o container");

                return 0;   // Nao pode inserir o container
            }
        }
    }

    // Pode inserir o container
    return 1;
}

void add_container(Stack** p, int container) {
    
    if (patio_cheio(p)) {
        printf("Patio Cheio, impossivel adicionar container.");
        return;
    }

    for (int i = 1; i < 5; i++) {
        if (isFull(p[i]))
            continue;
        else {
            if (container < top(p[i])) {
                push(p[i], container);
                return;
            }
        }
    }

    int maior = -1;
    int pos = 0;

    for (int i = 1; i < 5; i++) {
        if (maior < top(p[i])) {
            if (!(isFull(p[i]))) {
                maior = top(p[i]);
                pos = i;
            }
        }
    }
    
    push(p[0], pop(p[pos]));
    add_container(p,container);

    while (!isEmpty(p[0]))
        add_container(p, pop(p[0]));
}

void rm_container(Stack** p, int id) {
    for (int i = 1; i < 5; i++) {
        if (top(p[i]) == id) {
            pop(p[i]);
            return;
        }
    }

    printf("container n�o encontrado ou n�o est� no topo das pilhas");
    return;
}