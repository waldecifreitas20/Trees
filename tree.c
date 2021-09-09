#include <stdio.h>
#include <stdlib.h>

#define _HEAD_ "RAIZ"
#define _LEFT_ "ESQUERDA"
#define _RIGHT_ "DIREITA"

typedef struct _tree {
    struct _tree* left,* right,* father;
    int value, level;
    char* side;
}Tree;

//Required
void addLeaf(Tree** t, int value);
void removeLeaf(Tree** t, int value);
int search(Tree* t, int value);
void showTree(Tree* t);
//Extra
int doubleNode(Tree* t); //
int countLeafs(Tree* t, int value);//
int howDeepIs(Tree* t);
void maxAndMin(Tree* t);
void drawTree(Tree* t);
//Aux
Tree* initTree();
void setValues(Tree** t);


int main() {
    Tree* t = initTree();
    int r = 0;
    setValues(&t);
   /*
    showTree(t);
    if(!search(t, 25)) {
        printf("elemento nao encontrado!\n");
    }
   */
    maxAndMin(t);

    return 0;
}

//Aux
void setValues(Tree** t) {
    int i = 0;
    int vet[] = {
        86, 11, 7, 35, 170, 2, 
        120, 21, 88, 152, 31, 12, 
        181, 28, 134, 70, 1, 85, 
        25, 77, 10, 128, 198
    };
    for (i = 0; i < sizeof(vet)/sizeof(int); i++) {       
        addLeaf(&t, vet[i]);
    }
        printf("i = %d\n", sizeof(vet)/sizeof(int)); 
}

Tree* initTree() {
    Tree* t = (Tree*) malloc(sizeof(Tree));   
    t->father = NULL;
    t->value = NULL;
    t->right = NULL;
    t->level = -1;
    t->left = NULL;
    return t;
}

Tree* newNode(int value) {
    Tree* node = initTree();
    node->value = value;    
    return node;
}

int max(Tree* t) {
    if (t->right == NULL) {
        return t->value;
    }
    return max(t->right);    
}

int min(Tree* t) {
    if (t->left == NULL)
        return t->value;
    
    return min(t->left);    
}

//Required
void addLeaf(Tree** t, int value) {
    Tree* node = newNode(value);
    if ((*t)->value == NULL) {          
        node->level = 0;
        node->side = _HEAD_;
        *t = node;   
    } else {
        if ((*t)->value < value) {
            if ((*t)->right == NULL) {
                node->level = (*t)->level + 1; 
                node->side = _RIGHT_; 
                node->father = *t;              
                (*t)->right = node;
            } else {
                addLeaf(&(*t)->right, value);
            }           
        } else if ((*t)->value > value) {
            if ((*t)->left == NULL) {
                node->level = (*t)->level + 1;  
                node->side = _LEFT_;     
                node->father = *t;         
                (*t)->left = node;
            } else {             
                addLeaf(&(*t)->left, value);
            }           
        } else {
            printf("Elemento ja existente na arvore!\n");
        }
    }    
}

void removeLeaf(Tree** t, int value);

int search(Tree* t, int value) {
    int aafolou = 0, left = 0, right = 0;
    if (t->value == value) {
        puts("\nElemento encontrado!\n");
        printf("    Valor: %d\n", t->value);
        printf("    Nivel: %d\n", t->level);
        printf("    Tipo de node: %s\n\n", t->side);
        return 1;
    } else {
        if (value < t->value && t->left != NULL) {
            left = search(t->left, value);
        } else if(value > t->value && t->right != NULL){
            right = search(t->right, value);            
        } 
        return left || right;
    }    
}

void showTree(Tree* t) {
    if (t == NULL) {
        return;
    }     
    showTree(t->left);
    printf("Elemento: %d | Nivel : %d | Tipo de node: %s\n ", t->value, t->level, t->side);
    showTree(t->right);  
}


//Extra
int doubleNode(Tree* t) {
    int count = 0;
    if (t->left != NULL && t->right!=NULL) {
        ++count;
    } else if(t->left == NULL && t->right == NULL){
        return 0;
    }

    if (t->left != NULL) 
        count += doubleNode(t->left);
    
    if (t->right != NULL) 
        count += doubleNode(t->right);    
    
    return count;
    
}

int countLeafs(Tree* t, int value) {
    if (t->right == NULL && t->left == NULL)
        return value + 1;

    int l = 0, r = 0;
    if (t->left != NULL)
        l = countLeafs(t->left, value);

    if (t->right != NULL)
        r = countLeafs(t->right, value);
    
    return r + l;    
}

int howDeepIs(Tree* t) {
    int l1 = 0, l2 = 0;
    if (t == NULL)
        return 0;

    if (t->left != NULL) 
        ++l1;
     
    if (t->right != NULL) 
        ++l2;

    l1 += howDeepIs(t->left);
    l2 += howDeepIs(t->right);
   
    return l1 >= l2? l1: l2;  
}

void maxAndMin(Tree* t) {
    printf("Maior valor: %d\n", max(t));
    printf("Menor valor: %d\n", min(t));
}

void drawTree(Tree* t) {
    
}