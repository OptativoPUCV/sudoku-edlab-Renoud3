#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          fscanf (file, "%d", &n->sudo[i][j]);
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  //int f, c, kf, kc, i, j;
  //Node * aux = createNode();
  //f = i;
  //do {
    //for (f = 0 ; f < 9 ; f++) {
      //if (n -> sudo[f][c] == aux -> sudo[i][j]){
        //return 0;
      //}
      //else {
        //i++;
      //}
    //}
  //} while ((f < 9) && (i < 9));
  //c = j;
  //while ((c < 9) && (j < 9)) {
    //for (c = 0 ; c < 9 ; c++) {
      //if (n -> sudo[i][j] == aux -> sudo[f][c]) {
        //return 0;
      //}
      //else {
        //j++;
      //}
    //}
  //}
  
  return 1;
}


List* get_adj_nodes(Node* n){
  int i;
  int j;
  int num;
  List* list=createList();

  for (i = 0 ; i < 9 ; i++) {
    for (j = 0 ; j < 9 ; j++) {
      if (n -> sudo[i][j] == 0) {
        for (num = 1 ; num < 10 ; num++){
          n -> sudo[i][j] = num;
          if (is_valid(n)){
            Node * nuevo = copy(n);
            pushBack(list , nuevo);
          }
        }
        n -> sudo[i][j] = 0;
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){
  int i;
  int j;
  for (i = 0 ; i < 9 ; i++) {
    for (j = 0 ; j < 9 ; j++) {
      if (n -> sudo[i][j] == 0) {
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack * S = createStack();
  push(S , initial);
  cont = 0;
  while (get_size(S) != 0) {
    Node * initial = top(S);
    pop(S);
    if (is_final(initial) == 1) {
      return initial;
    }
    List * ady = get_adj_nodes(initial);
    Node * aux = first(ady);
    while (aux != NULL) {
      push(S , initial);
      aux = next(ady);
    }
    cont++;
    free(initial);
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/