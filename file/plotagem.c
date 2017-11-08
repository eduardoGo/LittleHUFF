#include <stdio.h>
#include <stdlib.h>

//TAD DE FILA de prioridade

#define MAX_HEAP_SIZE 1201

typedef struct Node node;
typedef struct Queue queue;
typedef struct HEAP heap;

struct Node{
	int item;
	int priority;
	struct Node *next;
};

struct Queue {
	node *head;
	node *tail;
};

struct HEAP
{
	int size;
	int data[MAX_HEAP_SIZE];
};

void swap(int *x, int *y){ 
   int temp;
   temp=*x;
   *x=*y;
   *y=temp;
}

heap* create_heap()
{
	heap *new = (heap*) malloc(sizeof(heap));
	new->size = 0;
	int i;
	for(i = 0; i < MAX_HEAP_SIZE; ++i)
	{
		new->data[i] = -1;
	}
	return new;
}

int get_parent_index(heap *heap, int i)
{
	return i/2;
}
int get_left_index(heap *heap, int i)
{	
	return 2*i;
}
int get_right_index(heap *heap, int i)
{
	return 2*i + 1;
}
int item_of(heap *heap, int i)
{
	return heap->data[i];
}

int enqueue_H(heap *heap, int item)
{
	int cont = 1;
	if(heap->size >= MAX_HEAP_SIZE)
	{
		printf("Heap full\n");
	}
	else
	{
		++heap->size;
		heap->data[heap->size] = item;
		
		int key_index = heap->size;
		int parent_index = get_parent_index(heap,heap->size);

		while (parent_index >= 1 && heap->data[key_index] > heap->data[parent_index]) 
		{
			cont++;
			swap(&heap->data[key_index], &heap->data[parent_index]);
			
			key_index = parent_index;
			
			parent_index = get_parent_index(heap, key_index);

		}
	}
	return cont;
}
void max_heapify(heap *heap, int i)
{
	int largest;
	int left_index = get_left_index(heap, i);
	int right_index = get_right_index(heap, i);
	if (left_index <= heap->size &&
		heap->data[left_index] > heap->data[i]) {
		largest = left_index;
	}
	else 
	{
		largest = i;
	}
	if (right_index <= heap->size && heap->data[right_index] > heap->data[largest])
	{ 
		largest = right_index;
	}
	if (heap->data[i] != heap->data[largest])
	{
		swap(&heap->data[i], &heap->data[largest]);
		max_heapify(heap, largest);
	}
}

int dequeue_H(heap *heap)
{
	if (heap->size == 0)
	{

		printf("Heap underflow");
		return -1;
	} 
	else
	{
		int item = heap->data[1];

		heap->data[1] = heap->data[heap->size];

		heap->size--;

		max_heapify(heap, 1);

		return item;
	}
}

queue* create_queue()
{
	queue *new_queue = (queue*) malloc(sizeof(queue));
	new_queue->head = NULL;
	new_queue->tail = NULL;

	return new_queue;
}

int is_empty(queue *a)
{
	return a->head == NULL;
}

int enqueue(queue *queue, int item,int p)
{
	node *new_node = (node*) malloc(sizeof(node));
	new_node->item = item;
	new_node->priority = p;
	int cont = 1;
	
	if(is_empty(queue) || p > queue->head->priority)
	{
		new_node->next = queue->head;
		queue->head = new_node;

	}
	else
	{
		node *current = queue->head;
		while((current->next != NULL) && (current->next->priority > p))
		{
			cont++;
			current = current->next; 
		}
		new_node->next = current->next;
		current->next = new_node;
	}

	return cont;
}

node* dequeue(queue * queue)
{
	node *node = queue->head;
	queue->head = queue->head->next;
	return node; //Dps de usar dê um free
}

int main()
{
	int i,answer,aux,limite;
	queue *queue = create_queue();
	heap *heap = create_heap();
	FILE *file_with_heap;
	FILE *file_without_heap;
	FILE *y;

	file_with_heap = fopen("file_with_heap", "wb");
	file_without_heap = fopen("file_without_heap", "wb");
	y = fopen("y", "wb");


	printf("Quantidade de valores ?\n");
	scanf("%d", &limite);

	for(i = 1; i <= limite; ++i)
	{
		aux = rand() % limite;
		fprintf(y, "%d,", i);
		fprintf(file_without_heap, "%d,", enqueue(queue,aux,aux));
		fprintf(file_with_heap, "%d,", enqueue_H(heap,aux));
	}
	
	return 0;
}
