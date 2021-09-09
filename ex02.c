#include <stdio.h>
#include <stdlib.h>

#define _MAX_ 4

typedef int 
    Boolean,
    ElementType, 
    ElementPointer;

typedef struct element {
    ElementType value;
}Element;

typedef struct _queue {
    int length;
    Element elements[_MAX_];
    ElementPointer begin, end;
}Queue;

//FUNCTIONS HEADER
// + Required
int dequeue(Queue* q);              
void showQueue(Queue q);          
void enqueue(Queue* q, int value); 
void queueJump(Queue* q, int value);
//  Optional
int isFull(Queue q);
int isEmpty(Queue q);               
//  Aux                
int getPosition(int i);
void initQueue(Queue* q);
void error(int error_code);
//----------------------//

int main() {
    //inicializa a fila
    Queue q;
    initQueue(&q);

    //desenfileirar fila vazia
    ElementType element = dequeue(&q);

    //enfileirar
    enqueue(&q, 2);
    enqueue(&q, 8);

    //printar na tela a fila
    showQueue(q);

    //adicionar na cabeça
    queueJump(&q, 7);
    showQueue(q);

    //desenfileirar
    element = dequeue(&q);
    showQueue(q);
    printf("elemento: %d\nh");

    //overflow da fila
    queueJump(&q, 1);
    queueJump(&q, 8);
    queueJump(&q, 9);


    return 0;
}

void initQueue(Queue* q) {
    q->begin = 0;
    q->end = q->begin;
    q->length = 0;
}

void enqueue(Queue* q, int value){
    if (q->length == _MAX_) {
        error(0);
    } else {
        q->elements[q->end].value = value;
        q->end = (q->end + 1) % _MAX_;
        q->length++;
    }    
}

void showQueue(Queue q) {
    int i = 0, start = q.begin;

    printf("fila -> [");
    while(i < q.length) {
        printf("%d", q.elements[start].value);
        start = (start+1) % _MAX_;
        i++;
        if (i+1 <= q.length) {
            printf(", ");
        }        
    }
    printf("]\n");    
}

void queueJump(Queue* q, int value) {
    if (isFull(*q)) {        
        error(0);
    } else if (isEmpty(*q)) {
        q->elements[q->begin].value = value;
        q->length++;
    } else {
        q->begin = getPosition(q->begin);
        q->elements[q->begin].value = value;
        q->length++;
    }       
}

ElementType dequeue(Queue* q) {
    if (isEmpty(*q)) {
        error(1);
        return -1;
    } else {
        q->length--;
        ElementType element = q->elements[q->end].value;
        q->end = getPosition(q->end);
        return element;
    }   
}

Boolean isEmpty(Queue q) {
    return q.length == 0;
}

Boolean isFull(Queue q) {
    return q.length == _MAX_;
}

void error(int error_code) {
    switch (error_code) {
    case 0:
        printf("FILA CHEIA! Remova um item para poder adicionar na fila.\n");    
        break;
    case 1: 
        printf("FILA VAZIA! adicione um item na fila antes de tentar remove-lo.\n");    
    default:
        break;
    }
}

int getPosition(int i) {
    i--;
    if (i < 0) {
        return i + _MAX_;
    } 
    return i % _MAX_;    
}