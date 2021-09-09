#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM 3

//Structs
typedef struct _stack{
    char elements[MAX_TAM];
    int length;
    char* begin,* end;
}StringStack;

typedef struct _arrayStringStack{
    StringStack lines[MAX_TAM];
    int length;
}ArrayStringStack;

//Functions Header
void initStack(StringStack* stack);
void setElements(StringStack* stack);
ArrayStringStack split(StringStack* ss);
void printList(ArrayStringStack ass);
void reverseString(ArrayStringStack* ass);
void toString(ArrayStringStack ass, char* cpy_string);
void finalizeString(StringStack* str);
void toLower(StringStack* ss);
//start
int main() {

    StringStack ss;

    initStack(&ss);
    setElements(&ss);
    toLower(&ss);

    ArrayStringStack ass = split(&ss);  
    
    //printList(ass);

    reverseString(&ass);

    char reverse[MAX_TAM];
    toString(ass, reverse);
    printf("%s", reverse);
   
    return 0;
}

void initStack(StringStack* stack) {

    stack->begin = &stack->elements[0];
    stack->end = stack->begin;
    stack->length = 0;

}

void setElements(StringStack* stack) {
    
    printf("Digite a frase a ser alterada:\n");
    fgets(stack->elements, MAX_TAM, stdin);
    int i = 0;
    while (stack->elements[i] != '\0') {
        stack->length++;
        i++;
    }
    printf("length: %d\n", stack->length);
    stack->end = &stack->elements[stack->length];    
}

void push(StringStack* ss, char c){
    if (ss->length < MAX_TAM) {
        ss->elements[ss->length] = c;
        ss->end = &ss->elements[ss->length];
        ss->length++;
    } else {
        printf("PILHA CHEIA! Por favor, retire ao menos 1 elementos para realizar esta tarefa");
    }   
}

ArrayStringStack split(StringStack* ss) {
    ArrayStringStack ass;
    int i = 0, line = 0;

    while (ss->elements[i] != '\0') {
        if (ss->elements[i] == ' ') {
            finalizeString(&ass.lines[line]);
            line++;

        } else if (ss->elements[i] != '\n')  {
            push(&ass.lines[line], ss->elements[i]);
        }
        i++;
    }
    ass.length = line+1;
    return ass;
}

void finalizeString(StringStack* str) {     
    str->elements[str->length] = '\0';
    str->end = &str->elements[str->length - 1];    
}

void printList(ArrayStringStack ass) {
    int line = 0, i;
    while (line < ass.length) {
        i = 0;
        printf("line[%d] = {%s}\n", line, ass.lines[line].elements);      
        line++;
    }
    
}

void reverseWord(char* word, char* reverse) {
    int len = strlen(word), 
        start = 0, 
        end = len-1;

    while (start < len) {
        reverse[start] = word[end];
        start++;
        end--; 
    }
    reverse[len] = '\0';    
}

void reverseString(ArrayStringStack* ass) {
    int line = 0;
    char reverse[MAX_TAM];
    while (line < ass->length) {
        reverseWord(ass->lines[line].elements, reverse);
        strcpy(ass->lines[line].elements, reverse);
        line++;
    }
    
}

void toString(ArrayStringStack ass, char* cpy_string) {
    int line = 0, i, el = 0;
    while (line < ass.length) {
        i = 0;
        while (ass.lines[line].elements[i] != '\0') {    
            cpy_string[el] = ass.lines[line].elements[i];               
            el++;
            i++;
        }
        cpy_string[el] = ' ';
        el++;
        line++;        
    }
    cpy_string[el-1] = '\0';     
}

void toLower(StringStack* ss) {
    int i;
    for (i = 0; i < ss->length; i++) {
           
        if (ss->elements[i] > 64 && ss->elements[i] < 91) {
            ss->elements[i] = ss->elements[i] + 32;
        }        
    }    
}