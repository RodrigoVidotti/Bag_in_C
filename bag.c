/*
 * MAC0323 Algoritmos e Estruturas de Dados II
 * 
 * ADT Bag implementada com lista ligada de itens. 
 *  
 *    https://algs4.cs.princeton.edu/13stacks/
 *    https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/bag.html
 * 
 * Os itens desta implementação são genéricos: "shallow copy" dos itens dados.
 *
 *----------------------------------------------------------------------------
 * Object copying
 * https://en.wikipedia.org/wiki/Object_copying
 * 
 * Understanding Deep and Shallow Copy 
 * https://we-are.bookmyshow.com/understanding-deep-and-shallow-copy-in-javascript-13438bad941c
 *
 * Shallow copy is a bit-wise copy of an object. A new object is created that has an 
 * exact copy of the values in the original object. If any of the fields of the object 
 * are references to other objects, just the reference addresses are copied i.e., 
 * only the memory address is copied.
 
 * A deep copy copies all fields, and makes copies of dynamically allocated memory 
 * pointed to by the fields. A deep copy occurs when an object is copied along with the 
 * objects to which it refers.
 *
 */

/* interface para o uso da funcao deste módulo */
#include "bag.h"  

#include <stdlib.h>  /* free() */
#include <string.h>  /* memcpy() */
#include "util.h"    /* emalloc() */

#undef DEBUG
#ifdef DEBUG
#include <stdio.h>   /* printf(): para debuging */
#endif

/*----------------------------------------------------------*/
/* 
 * Estrutura Básica da Bag
 * 
 * Implementação com listas ligada dos itens.
 */

typedef struct link{
    void *item;
    size_t nItem;
    struct link *next;
}node;

typedef node *Node;

struct bag {
    Node head;
    Node current;
    int size;
};

/*------------------------------------------------------------*/
/* 
 * Protótipos de funções administrativas: tem modificador 'static'
 * 
 */

/*-----------------------------------------------------------*/

/*  RECEBE um NODE e devolve ao sistema toda a memoria utilizada.*/
void freeNode(Node node);

/*-----------------------------------------------------------*/
/*
 *  newBag()
 *
 *  RETORNA (referência/ponteiro para) uma bag vazia.
 * 
 */
Bag newBag(){
    Bag bag = emalloc(sizeof(*bag));
    bag->head = NULL;
    bag->current = NULL;
    bag->size = 0;
    return bag;
}

/*-----------------------------------------------------------*/
/*
 *  freeBag(BAG)
 *
 *  RECEBE uma Bag BAG e devolve ao sistema toda a memoria 
 *  utilizada.
 *
 */
void freeBag(Bag bag){
    freeNode(bag->head);
    free(bag);
}

/*------------------------------------------------------------*/
/*
 * OPERAÇÕES USUAIS: add(), size(), isEmpty() e itens().
 */

/*-----------------------------------------------------------*/
/*
 *  add(BAG, ITEM, NITEM)
 * 
 *  RECEBE uma bag BAG e um ITEM e insere o ITEM na BAG.
 *  NITEM é o número de bytes de ITEM.
 *
 *  Para criar uma copia/clone de ITEM é usado o seu número de bytes NITEM.
 *
 */
void add(Bag bag, const void *item, size_t nItem){
    Node oldfirst = bag->head;
    bag->head = emalloc(sizeof(node));
    bag->head->item = emalloc(nItem);
    memcpy(bag->head->item, item, nItem);
    bag->head->nItem = nItem;
    bag->head->next = oldfirst;
    bag->size++;
}

/*-----------------------------------------------------------*/
/* 
 *  SIZE(BAG)
 *
 *  RECEBE uma bag BAG
 * 
 *  RETORNA o número de itens em BAG.
 */
int size(Bag bag){
    return bag->size;
}

/*-----------------------------------------------------------*/
/* 
 *  ISEMPTY(BAG)
 *
 *  RECEBE uma bag BAG.
 * 
 *  RETORNA TRUE se BAG está vazia e FALSE em caso contrário.
 *
 */
Bool isEmpty(Bag bag){
    return bag->size == 0;
}

/*-----------------------------------------------------------*/
/* 
 *  ITENS(BAG, INIT)
 * 
 *  RECEBE uma bag BAG e um Bool INIT.
 *
 *  Se INIT é TRUE,  ITENS() RETORNA uma cópia/clone do primeiro item na lista de itens na BAG.
 *  Se INIT é FALSE, ITENS() RETORNA uma cópia/clone do item sucessor do último item retornado.
 *  Se BAG está vazia ou não há sucessor do último item retornada, ITENS() RETORNA NULL.
 *
 *  Se entre duas chamadas de ITENS() a BAG é alterada, o comportamento é  indefinido. 
 *  
 */
void *itens(Bag bag, Bool init){
    if (isEmpty(bag)) return NULL;
    
    if (init){
        bag->current = bag->head;
    }
    else{
        if (bag->current == NULL || bag->current->next == NULL) return NULL;
        bag->current = bag->current->next;
    }
    
    void *item = emalloc(bag->current->nItem);
    memcpy(item, bag->current->item, bag->current->nItem);

    return item;
}

/*------------------------------------------------------------*/
/* 
 * Implementaçao de funções administrativas
 */
/*-----------------------------------------------------------*/
/*
 *  freeNode(NODE)
 * 
 *  RECEBE um NODE e devolve ao sistema toda a memoria utilizada.
 *
 */
void freeNode(Node node){
    if(node == NULL) return;
    freeNode(node->next);
    free(node->item);
    free(node);
}