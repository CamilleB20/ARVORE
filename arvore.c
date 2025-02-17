#include <stdio.h>
#include <stdlib.h>

//cria o tipo de dado ArvoreNo
typedef struct arvNo ArvoreNo;              

//cria a estrutura de cada nó da árvore
struct arvNo                            
{
  char info;
  ArvoreNo* esquerda;
  ArvoreNo* direita;
};

//cria o tipo de dado Arvore
typedef struct arvore Arvore;           

//cria a estrutura da árvore apontando a raiz do nó
struct arvore
{
  ArvoreNo* raiz;
};

//função que cria o nó
ArvoreNo* criarNo (char elemento, ArvoreNo* esq, ArvoreNo* dir){
  ArvoreNo* p = (ArvoreNo*) malloc(sizeof (ArvoreNo));            //p = ponteiro
  p->info = elemento;
  p->esquerda = esq;
  p->direita = dir;

  return p;
}

//função que cria e aponta para o nó raiz
Arvore* criarArvore (ArvoreNo* r){
  Arvore* a = (Arvore*) malloc(sizeof(Arvore));               //a = ponteiro
  a->raiz = r;

  return a;
}


//função que insere os elementos na árvore
void inserir(Arvore* arvore, char elemento, char lado) {
  if (arvore == NULL) {
    printf("Crie uma árvore primeiro.");
    return;
  };

  if (arvore->raiz == NULL) {
      arvore->raiz = criarNo(elemento, NULL, NULL);
      return;
  }

  ArvoreNo* atual = arvore->raiz;
  ArvoreNo* novo = criarNo(elemento, NULL, NULL);

  if (!novo) {
    printf("É preciso inserir corretamente o elemento que deseja adicionar.");
    return;
  };

  if (lado == 'E' || lado == 'e') {
    if (atual->esquerda == NULL) {
      atual->esquerda = novo;
      return;
    } else {
      printf("Este lado já está preenchido.\n");
      atual = atual->esquerda;
    }
  } else {
    if (atual->direita == NULL) {
      atual->direita = novo;
      return;
    } else {
      printf("Este lado já está preenchido.\n");
      atual = atual->direita;
    }
  }
}


//função que ajuda a remover um nó
static ArvoreNo* removerNo(ArvoreNo* r, char c) {
  if (r == NULL) {
    return r; //se não encontrar o nó
  }
  //Primeiro caso possível: Se quiser remover o nó atual
  if (c == r->info) {
    //quantNóFilhos == 0
    if (r->esquerda == NULL && r->direita == NULL) { 
      free(r);
      return NULL;
    }
    //quantNóFilhos == 1
    if (r->esquerda == NULL) {
      ArvoreNo* temp = r->direita;
      free(r);
      return temp;
    }
    if (r->direita == NULL) {
      ArvoreNo* temp = r->esquerda;
      free(r);
      return temp;
    }
    //quantNóFilhos == 2
    ArvoreNo* sucessor = r->direita; //encontra o sucessor (menor)
    while (sucessor->esquerda != NULL) {
      sucessor = sucessor->esquerda;
    }
    r->info = sucessor->info; //troca o que vamos remover com o sucessor
    r->direita = removerNo(r->direita, sucessor->info); //remove o novo sucessor
  }

  //Segundo caso possível: Qual direção o nó que será removido está
  if (c < r->info) {
    r->esquerda = removerNo(r->esquerda, c);
  } else {
    r->direita = removerNo(r->direita, c);
  }
  return r;
}
//função para remover um nó escolhido
ArvoreNo* remover(Arvore* a, char c) {
  return removerNo(a->raiz, c);
}


//função auxiliar que exibe os elementos da árvore
static void imprime (ArvoreNo* r){
    if (r != NULL){
        printf("%c ", r->info);
        imprime(r->esquerda);
        imprime(r->direita);
    }
}

//função que imprime a árvore a partir da raiz
void imprimeArvore (Arvore* a){
    imprime(a->raiz);
}


//função auxiliar que libera a memória
static void liberarMemoria (ArvoreNo* r){
  if (r != NULL){
    liberarMemoria(r->esquerda);
    liberarMemoria(r->direita);
    free(r);
  }
}

//função que libera a memoria da raiz
void liberarRaiz (Arvore* a){
  liberarMemoria(a->raiz);
  free(a);
}


//função auxiliar que verifica se o elemento está na árvore
static int pertence (ArvoreNo* r, char c){
  if (r == NULL){
    return 0;
  }else{
    return c == r->info || pertence(r->esquerda, c) || pertence(r->direita, c);
  }
}

//função que verifica se o elemento é a raiz
int pertenceRaiz (Arvore* a, char c){
  return pertence(a->raiz, c);
}


//função auxiliar que busca e apresenta o elemento
static ArvoreNo* buscaElemento (ArvoreNo* r, char c){
  if (r == NULL){
    return NULL;
  }else if (c == r->info){
    return r;
  }else{
    ArvoreNo* p = buscaElemento(r->esquerda, c);
    if (p != NULL){
        return p;
    }else{
        return buscaElemento(r->direita, c);
    }
  }    
}

//função que busca e apresenta o elemento no nó raiz
ArvoreNo* buscaRaiz (Arvore* a, char c){
  return buscaElemento(a->raiz, c);
}


//função que ajuda a contar os nós
static int contarNosUm(ArvoreNo* r) {
  if (r == NULL) {
    return 0;
  } else {
    return 1 + contarNosUm(r->esquerda) + contarNosUm(r->direita); //conta o nó atual e os nós das subárvores
}
}
//função contador dos nós totais
int contarNosFinal(Arvore* a) {
  return contarNosUm(a->raiz);
}


//função que ajuda a contar as folhas
static int contarFolhasUm(ArvoreNo* r) {
  if (r == NULL) {
    return 0;
  }
  if (r->esquerda == NULL && r->direita == NULL) { //identificando quem são as folhas
    return 1;
  }
  return contarFolhasUm(r->esquerda) + contarFolhasUm(r->direita); //se não, elas são classificadas como subárvores
}
//função contador de todas as folhas
int contarFolhasFinal(Arvore* a) {
  return contarFolhasUm(a->raiz);
}


//função que ajuda a acharmos a altura da árvore
static int calAlturaUm(ArvoreNo* r) {
  if (r == NULL) {
    return -1;
  }
  int esq = calAlturaUm(r->esquerda);
  int dir = calAlturaUm(r->direita); //calculamos a altura das subárvores esquerda e direita
  return (esq > dir ? esq : dir) + 1;
}
//função que calcula a altura da árvore
int calAlturaFinal(Arvore* a) {
  return calAlturaUm(a->raiz);
}


//função que ajuda a verificar se a árvore é própria
static int propOuImUm(ArvoreNo* r) {
  if (r == NULL) {
    return 1; //se nó == NULL, então própria
  }
  if (r->esquerda == NULL && r->direita == NULL) { // se nó == folha, então própria
    return 1;
  }
  if (r->esquerda == NULL || r->direita == NULL) { // se quantFilhoNo == 1, então imprópria
    return 0;
  }
  return propOuImUm(r->esquerda) && propOuImUm(r->direita); //verificando subárvores
}
//função verica se é própria ou não
int propOuImFinal(Arvore* a) {
  return propOuImUm(a->raiz);
}


void menu() {
  int opcao;

  do {
    printf("\n====== MENU ======\n");
    printf("1 - Criar árvore\n");
    printf("2 - Inserir elemento\n");
    printf("3 - Remover elemento\n");
    printf("4 - Imprimir árvore (Pré-ordem)\n");
    printf("5 - Total de nós\n");
    printf("6 - Total de folhas\n");
    printf("7 - Altura da árvore\n");
    printf("8 - Verificar se a árvore é própria\n");
    printf("9 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
      char elemento;
      char lado;
      Arvore* arvore;

      case 1:
        printf("\nDigite o elemento da raiz: ");
        scanf(" %c", &elemento);

        arvore = criarArvore(criarNo(elemento, NULL, NULL));

        printf("\nÁrvore criada com sucesso: ");
        imprimeArvore(arvore);
        printf("\n");
        break;

      case 2:
        printf("\nDigite o elemento a ser inserido: ");
        scanf(" %c", &elemento);
        printf("\nDigite o lado em que o elemento deve ser inserido ('e' -> esquerda e 'd' -> direita): ");
        scanf(" %c", &lado);
        inserir(arvore, elemento, lado);
        printf("\n Árvore atual: ");
        imprimeArvore(arvore);
        printf("\n");
        break;
      
      case 3:
        printf("Digite o elemento que gostaria de remover: ");
        scanf(" %c", &elemento);
        arvore->raiz = remover(arvore, elemento);
        printf("Árvore atual, sem o elemento removido: ");
        imprimeArvore(arvore);
        printf("\n");
        break;
  
      case 4:
        printf("Árvore (Pré-ordem): ");
        imprimeArvore(arvore);
        printf("\n");
        break;
        
      case 5:
        printf("Total de nós: ");
        contarNosFinal(arvore);
        printf("\n");
        break;
        
      case 6:
        printf("Total de folhas: ");
        contarFolhasFinal(arvore);
        printf("\n");
        break;
          
      case 7:
        printf("Altura da árvore: ");
        calAlturaFinal(arvore);
        printf("\n");
        break;
        
      case 8:
        if (propOuImFinal(arvore)) {
          printf("A árvore é própria\n");
        } else {
          printf("A árvore é imprópria\n");
        }
        break;

      case 9:
        printf("Saindo e liberando espaço na memória...\n");
        //liberarMemoria(arvore->raiz);
        liberarRaiz(arvore);
        break;
    }
  } while (opcao != 9);
}

int main() {
  menu();

  return 0;
}
