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
  int entrada;
      
  //inicializa a fila
  Queue q;
  initQueue(&q);
do{
  printf("\n  ==================================\n");
  printf("  >>> MENU DE AÇÕES DA PILHA\n");
  printf("     [x]   Selecione uma opção abaixo:\n");
  printf("     [1] - ENFILEIRAR\n");
  printf("     [2] - DESENFILEIRAR\n");
  printf("     [3] - MOSTRAR A FILA\n");
  printf("     [4] - FURAR FILA\n");
  printf("     [0] – SAIR\n");
  printf("  ==================================\n");
  
  scanf("%d",&entrada);
  switch(entrada){
    //enfileirar
    case 1:
      printf("   Digite o valor a ser inserido na fila:\n");
      scanf("%d", &entrada);
      enqueue(&q, entrada);
      showQueue(q);
      break;
      
    //desenfileirar fila vazia
    case 2:    
      showQueue(q);
      ElementType element = dequeue(&q);
      break;

    //printar na tela a fila
    case 3:
      showQueue(q);
      break;
    
    //adicionar no topo
    case 4:
      printf("   Digite o valor a ser inserido na fila:\n");
      scanf("%d", &entrada);
      queueJump(&q, entrada);
      showQueue(q);
      break;
    default: 
      if(entrada!=0)
      printf("   Selecione uma opção válida!");
      break;
  }
}while(entrada != 0);
    return 0;
}

//Inicia a fila
void initQueue(Queue* q) {
    q->begin = 0;
    q->end = q->begin;
    q->length = 0;
}

//Adiciona elemento à fila
void enqueue(Queue* q, int value){
    if (q->length == _MAX_) {
        error(0);
    } else {
        q->elements[q->end].value = value;
        q->end = (q->end + 1) % _MAX_;
        q->length++;
    }    
}

//Mostra a fila
void showQueue(Queue q) {
    int i = 0, start = q.begin;

    printf("\n   Fila -> [");
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

//Pula fila
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

//Remove um elemento da fila 
ElementType dequeue(Queue* q) {
    if (isEmpty(*q)) {
        error(1);
        return -1;
    } else {
        q->length--;
        ElementType element = q->elements[q->end].value;
        q->end = getPosition(q->end);
        printf("Pilha Atualizada\n");
        return element;
    }   
}

//Verifica se a fila está vazia
Boolean isEmpty(Queue q) {
    return q.length == 0;
}

//Verifica se a fila está cheia
Boolean isFull(Queue q) {
    return q.length == _MAX_;
}

//Aviso de fila cheia ou vazia
void error(int error_code) {
    switch (error_code) {
    case 0:
        printf(" >>> FILA CHEIA!\n [Remova um item para poder adicionar na fila.]\n");    
        break;
    case 1: 
        printf(" >>> FILA VAZIA!\n [Adicione um item na fila antes de tentar remove-lo.]\n");    
    default:
        break;
    }
}

//Verifica posição na fila
int getPosition(int i) {
    i--;
    if (i < 0) {
        return i + _MAX_;
    } 
    return i % _MAX_;    
}