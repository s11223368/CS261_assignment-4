/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:Po-Sheng Hsu
 * Email:hsupos@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
  struct dynarray* dy; 
};

struct pnode{ 
  int priority;
  void *value;
};

int pq_priority_comparing(struct pq* pq, int p1, int p2){
  int temp;
  struct pnode* n1 = NULL;
  struct pnode* n2 = NULL;
  if(dynarray_size(pq->dy)){
    n1 = dynarray_get(pq->dy, p1);
    n2 = dynarray_get(pq->dy, p2);
    temp = n1->priority - n2->priority;
    return temp;
  }
  else return -1; 
};

void pq_swap(struct pq* pq, int n1, int n2){ 
  struct priority_value_node* temp1 = NULL;
	struct priority_value_node* temp2 = NULL;
	temp1 = dynarray_get(pq->dy, n1); 
	temp2 = dynarray_get(pq->dy, n2); 
	dynarray_set(pq->dy, n1, temp2); 
	dynarray_set(pq->dy, n2, temp1);
};

void pq_adjust_front(struct pq* pq){ 
	assert(pq);
	int i=0, j=0, root=0, front=0, next=0;
	int size;
	size = dynarray_size(pq->dy);
	while(i<(size-1) / 2){ 
    root = i;
		front = 2 * i + 1;
		next = front + 1;
		j = front;
		if(pq_priority_comparing(pq,front,next) > 0){
			j++;
		}
		if(pq_priority_comparing(pq, root, j) > 0){
			pq_swap(pq, i, j);
			i = j;
		}
		else break;
	}
}

void pq_adjust_back(struct pq* pq){ 
	assert(pq);
	int i, root, leaf;
	i = dynarray_size(pq->dy) - 2;
	while(i > 0){
		leaf = i;
		root = (leaf - 1) / 2;
		if(pq_priority_comparing(pq,root,leaf) > 0){
			pq_swap(pq,leaf,root);
			i = root;
		}
		else  
		break;
	}
}

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
	assert(pq);
	pq->dy = dynarray_create();
	return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
  assert(pq);
  int i;
	struct priority_value_node* node;
	for(i=0;i<dynarray_size(pq->dy);i++){ 
		node = dynarray_get(pq->dy,i);
		free(node);
	}
	dynarray_free(pq->dy);
	free(pq);
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  assert(pq);
	if( dynarray_size(pq->dy) == 0 )	
	return 1; 
	else  
	return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
  assert(pq);
	int size;
	struct pnode* node = malloc(sizeof(struct pnode));
	assert(node);
	node->priority = priority;
	node->value = value;
	dynarray_insert(pq->dy, -1, node); 
	pq_adjust_back(pq);
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
  assert(pq);
	struct pnode* node = NULL;
	if(dynarray_size(pq->dy)){
		node = dynarray_get(pq->dy, 0);
		return node->value;
	}
	return NULL;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq){
  assert(pq);
	struct pnode* node = NULL;
	if(dynarray_size(pq->dy)){
		node = dynarray_get(pq->dy, 0);
		return node->priority;
	}
	return -1;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
  assert(pq);
	struct pnode* node = NULL;
	int* value;
	int size;
	size = dynarray_size(pq->dy);
	if(size){
		node = dynarray_get(pq->dy, 0);
		pq_swap(pq,0,size - 1);
		dynarray_remove(pq->dy,-1);
		value = node->value;
		free(node);
		pq_adjust_front(pq);
		return value;
	}
	
	return NULL;
}
