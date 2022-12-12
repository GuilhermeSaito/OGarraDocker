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

void rm_container(Stack** p, int priority) {
    for (int i = 1; i < 5; i++) {
        if (top(p[i]) == priority) {
            pop(p[i]);
            return;
        }
    }

    printf("container não encontrado ou não está no topo das pilhas");
    return;
}


int main() {

    pilha** patio = (pilha**)malloc(sizeof(pilha*) * 5); //cria patio

    for (int i = 0; i < 5; i++)
        patio[i] = createStack(4); //cria pilhas de altura 4

    add_container(patio, 4);
    add_container(patio, 7);
    add_container(patio, 12);
    add_container(patio, 13);
    add_container(patio, 3);
    add_container(patio, 6);
    add_container(patio, 8);
    add_container(patio, 2);
    add_container(patio, 5);
    add_container(patio, 9);
    add_container(patio, 14);
    add_container(patio, 20);
    add_container(patio, 15);
    add_container(patio, 1);
    add_container(patio, 30);
    add_container(patio, 11);



    for (int i = 0; i < 5; i++) {
        printf("Pilha %d:", i);
        printStack(patio[i]);
        printf("\n");
    }

    rm_container(patio, 1);
    add_container(patio, 50);

    printf("\n");

    for (int i = 0; i < 5; i++) {
        printf("Pilha %d:", i);
        printStack(patio[i]);
        printf("\n");
    }

    return 0;
}