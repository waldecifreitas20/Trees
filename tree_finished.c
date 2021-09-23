#include <stdio.h>
#include <stdlib.h>

#define _HEAD_ "RAIZ"
#define _LEFT_ "ESQUERDA"
#define _RIGHT_ "DIREITA"
#define _DECREASE_ -1
#define _INIT_ 0


typedef struct _tree {
    struct _tree* left,* right,* father;
    int value, level;
    char* side;
}Tree;

//Required
int addLeaf(Tree** t, int value);
int search(Tree* t, int value);
int removeNode(Tree** t, int value);
void showTreeInOrder(Tree* t);
//Extra
int doubleNode(Tree* t);
int countLeafs(Tree* t, int value);
int howDeepIs(Tree* t);
void maxAndMin(Tree* t);
//Aux
Tree* initTree();
void setValuesAtTree(Tree** t);
void showTree(Tree* t);
void decide(Tree** t);


int main() {
    //INICIANDO A ARVORE
    puts("* INICIANDO ARVORE *");
    Tree* t = initTree();
    puts("* ARVORE INICIADA*\n");
    
    //INSERINDO OS VALORES INICIAIS NA ARVORE
    puts("* INSERINDO VALORES *");
    setValuesAtTree(&t);    
    puts("* VALORES INSERIDOS *\n");
    
    //APRESENTANDO OS VALORES
    showTree(t);

    //INSERINDO VALORES NA ARVORE
    puts("* INSERINDO O VALOR INFORMADO PELO USUARIO *");
    int value;
    char response;
    int success;
    do {
        printf("Digite um valor: ");
        scanf("%d", &value);
        getchar();

        success = addLeaf(&t, value);
        if (success == 1) {
            printf("* VALOR %d INSERIDO COM SUCESSO *\n\n", value);
        } else {
            puts("ELEMENTO JA EXISTENTE NA ARVORE!\n");
        }
        printf("Deseja adicionar mais um valor?(s/n)\nR: ");
        scanf("%c", &response);   
    } while (response == 's');
    
    //APRESENTANDO OS VALORES
    showTree(t);
    
    //REMOVENDO O VALORES DA ARVORE
    do {       
        puts("\n* REMOVENDO O VALOR INFORMADO PELO USUARIO*");

        printf("Digite um valor: ");
        scanf("%d",&value);
        getchar();
        success = removeNode(&t, value);
        if (success == 1) {
            printf("* VALOR %d REMOVIDO COM SUCESSO *\n\n", value);            
        } else {
            printf("* %d NAO EXISTE NA ARVORE *\n\n", value);     
        }        
        printf("Deseja remover mais um valor?(s/n)\nR: ");
        scanf("%c", &response); 
    } while (response == 's');
     
    //APRESENTANDO OS VALORES 
    showTree(t);
   
    //BUSCANDO O VALOR NA ARVORE
    do {
        printf("Buscar pelo valor: ");
        scanf("%d", &value);
        getchar();
        int found = search(t, value);
        if (found == 0) {
            printf("* VALOR NAO ENCONTRADO. MOTIVO: %d NAO EXISTE NA ARVORE *\n\n", value);    
        }
        printf("Deseja realizar uma nova busca?(s/n)\nR: ");
        scanf("%c", &response); 
    } while (response == 's');
    
    
    //BUSCANDO NO COM 2 FILHOS
    printf("========== INFORMACOES DA ARVORE ==========\n");
    printf("Total de no's com 2 filhos: %d\n",doubleNode(t));
    
    //NuMERO DE FOLHAS
    printf("Numero de folhas: %d\n",countLeafs(t,_INIT_));
    
    //NuMERO DE NiVEIS
    printf("Numero de niveis: %d\n",howDeepIs(t));
    
    //MAIOR E MENOR VALOR
    maxAndMin(t);
    printf("===========================================\n");
    
    system("pause");
    return 0;
}

//Aux
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
 
void setValuesAtTree(Tree** t) {
    int i = 0;
    int vet[] = {
        86, 11, 7, 35, 170, 2, 
        120, 21, 88, 152, 31, 12, 
        181, 28, 134, 70, 1, 85, 
        25, 77, 10, 128, 198
    }; 
    for (i = 0; i < sizeof(vet)/sizeof(int); i++) {       
        addLeaf(t, vet[i]);
    }

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

int howManyChildren(Tree* t) {
    int children = 0;
    if (t->left != NULL) {
        ++children;
    }
    if (t->right != NULL) {
        ++children;
    }
    return children;
}

Tree* getSubstituteNode(Tree* t) {
    if (t->left == NULL)
        return t;
    return getSubstituteNode(t->left);    
}

void updateLevel(Tree** t, int action) {
    (*t)->level += action;
    if ((*t)->left != NULL) {
        updateLevel(&(*t)->left, action);
    }
    if ((*t)->right != NULL) {
        updateLevel(&(*t)->right, action);
    }
    
    
}

void noChild(Tree** t) {
    free(*t);
    *t = NULL;
}

void oneChild(Tree** t) {
    Tree* subs;
    if ((*t)->left != NULL) {
        subs = (*t)->left;
    } else {
        subs = (*t)->right;
    }
    updateLevel(&subs, _DECREASE_); 
    Tree* father = (*t)->father;
    if (father->left == (*t)) {
        father->left = subs;
    } else {
        father->right = subs;
    }
    subs->father = father;
}

void twoChild(Tree** t) {    
    Tree* subs = getSubstituteNode((*t)->right);
    (*t)->value = subs->value;
    decide(&subs);    
}

void decide(Tree** t) {
    switch (howManyChildren(*t)) {
        case 0:
            noChild(t);
            break;
        case 1:;
            oneChild(t);
            break;                
        case 2:;
            twoChild(t);
            break;            
        default:
            break;
    }
}

void showTree(Tree* t) {
    void showTreeInOrder(Tree* t);
    puts("========================== VALORES DA ARVORE =========================\n");
    showTreeInOrder(t);
    puts("======================================================================\n");
}


//Required
int addLeaf(Tree** t, int value) {
    Tree* node = newNode(value);
    int success = 1;
    if ((*t)->value == NULL) {          
        node->level = 0;
        node->side = _HEAD_;
        node->father = node;
        *t = node;   
    } else {
        if ((*t)->value < value) {
            if ((*t)->right == NULL) {
                node->level = (*t)->level + 1; 
                node->side = _RIGHT_; 
                node->father = *t;              
                (*t)->right = node;
            } else {
                success = addLeaf(&(*t)->right, value);
            }           
        } else if ((*t)->value > value) {
            if ((*t)->left == NULL) {
                node->level = (*t)->level + 1;  
                node->side = _LEFT_;     
                node->father = *t;         
                (*t)->left = node;
            } else {             
                success = addLeaf(&(*t)->left, value);
            }           
        } else {
            return 0;
        }
    
    }    
    return success;
}

int removeNode(Tree** t, int value) {
    int success = 0;
    if ((*t)->value > value && (*t)->left != NULL) {
        success = removeNode(&(*t)->left, value);
    } else if((*t)->value < value && (*t)->right != NULL) {
        success = removeNode(&(*t)->right, value);        
    } else if((*t)->value == value) {
        decide(t);     
        success = 1;        
    }      
    return success;
}

int search(Tree* t, int value) {
    int left = 0, right = 0;
    if (t->value == value) {
        puts("\nElemento encontrado!\n");
        printf("    Valor: %d\n", t->value);
        printf("    Nivel: %d\n", t->level);
        printf("    Elemento Pai: %d\n", t->father->value);
        printf("    Orientacao na subavore: %s\n\n", t->side);
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

void showTreeInOrder(Tree* t) {
    if (t == NULL) {
        return;
    }     
    showTreeInOrder(t->left);
    printf("Elemento: %d | Nivel : %d | Tipo de node: %s | Elemento Pai: %d\n ", t->value, t->level, t->side, t->father->value);
    showTreeInOrder(t->right);  
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

int countLeafs(Tree* t, int leafs) {
    if (t->right == NULL && t->left == NULL)
        return leafs + 1;

    int l = 0, r = 0;
    if (t->left != NULL)
        l = countLeafs(t->left, leafs);

    if (t->right != NULL)
        r = countLeafs(t->right, leafs);
    
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