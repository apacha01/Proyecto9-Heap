/*
 Implement a vector (mutable array with automatic resizing):
 	Practice coding using arrays and pointers, and pointer math to jump to an index instead of using indexing.
 	New raw data array with allocated memory can allocate int array under the hood, just not use its features start with 
 	16,	or if starting number is greater, use power of 2 - 16, 32, 64, 128
		size() - number of items
		capacity() - number of items it can hold
		is_empty()
		at(index) - returns item at given index, blows up if index out of bounds
		push(item)
		insert(index, item) - inserts item at index, shifts that index's value and trailing elements to the right
		prepend(item) - can use insert above at index 0
		pop() - remove from end, return value
		delete(index) - delete item at index, shifting all trailing elements left
		remove(item) - looks for value and removes index holding it (even if in multiple places)
		find(item) - looks for value and returns first index with that value, -1 if not found
		resize(new_capacity) // private function
			when you reach capacity, resize to double the size
			when popping an item, if size is 1/4 of capacity, resize to half
 Time
	O(1) to add/remove at end (amortized for allocations for more space), index, or update
	O(n) to insert/remove elsewhere
 Space
	contiguous in memory, so proximity helps performance
	space needed = (array capacity, which is >= n) * size of item, but even if 2n, still O(n)
*/
//////////////////////////////////////////////////BIBLIOTECAS////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
//////////////////////////////////////////////////DEFINES////////////////////////////////////////////////////////////////
#define resizeFactor 2
#define initialLength 16
//////////////////////////////////////////////////VARIABLES GLOBALES/////////////////////////////////////////////////////
typedef struct Vector
{
	int *p;
	int *_size;
	int *_capacity;
}Vector;
//////////////////////////////////////////////////PROTOTIPOS DE FUNCIONES////////////////////////////////////////////////
//DE LAS CONSIGNAS
int getSize(Vector*);								// returns size
int getCapacity(Vector*);							// returns capacity
bool isEmpty(Vector*);								// true if empty, false otherwise
int valueAt(Vector*, int/*index*/);					// returns value at index
void push(Vector*, int*/*vector*/, int/*value*/);	// inserts value at the end of the array
void insert(Vector*, int/*index*/, int/*value*/);	// inserts value at index. shifts that index's value and trailing elements to right
void prepend(Vector*, int/*value*/);				// inserts value at index 0
int pop(Vector*);									// remove last value and returns it
void erase(Vector*, int/*index*/);					// delete item at index, shifting all trailing elements left
void removeAll(Vector*, int/*value*/);				// remove all matches for value
int find(Vector*, int/*value*/);					// looks for value and returns first index with that value, -1 if not found
void resize(Vector*, int/*new capacity*/);			// resize the array
void init(Vector*);									// initialize the dynamic array (reserves needed memory)

//AUXILIARES
void incrementSize(Vector*);							// increment size and resize if necessary
void decrementSize(Vector*);							// decrement size and resize if necessary
void moveTo(Vector*, int, char);						// moves values to left or right according to given char (for insert & delete).
void ownRealloc(Vector*, int /*new capacity*/);			// realloc but own version
void changeValue(Vector*, int/*index*/, int/*value*/);	// changes value at index with given value
/////////////////////////////////////////////////FUNCIONES///////////////////////////////////////////////////////////////
//AUXILIAR
void init(Vector *v){
	v->p = (int *)calloc(initialLength,sizeof(int));
	v->_size = (v->p)-1;
	v->_capacity = (v->p)-2;

	*v->_size = 0;
	*v->_capacity = initialLength;
}

void incrementSize(Vector *v){
	*v->_size += 1;
	if (getSize(v) == getCapacity(v)) {
		resize(v,(getCapacity(v)*resizeFactor));
	}
}

void decrementSize(Vector *v){
	*v->_size -= 1;
	if (getSize(v) == (getCapacity(v)/4)) {
		resize(v,(getCapacity(v)/resizeFactor));
	}
}

void moveTo(Vector *v, int index, char c){
	if (c == 'r') {
		for (int i = getSize(v); i > index; i--) {
			*(v->p + i) = *(v->p + i-1);
		}
	}
	if (c == 'l') {
		for (int i = index; i < getSize(v) - 1; i++) {
			*(v->p + i) = *(v->p + i + 1);
		}
	}
}

void ownRealloc(Vector *v, int newCapacity){
	Vector vCpy = *v;
	v->p = (int *)calloc(newCapacity, sizeof(int));
	for (int i = 0; i < getSize(&vCpy); i++) {
		*(v->p+i) = *(vCpy.p+i);
	}
}

void changeValue(Vector *v, int index, int value){
	*((v->p)+index) = value;
}

//FOR THE USER
int getSize(Vector *v){
	return *v->_size;
}

int getCapacity(Vector *v){
	return *v->_capacity;
}

bool isEmpty(Vector *v){
	return *v->_size == 0;
}

int valueAt(Vector *v, int index){
	return *((v->p)+index);
}

void push(Vector *v, int item){
	*((v->p)+getSize(v)) = item;
	incrementSize(v);
}

void insert(Vector *v, int index, int item){
	moveTo(v,index,'r');
	*(v->p + index) = item;
	incrementSize(v);
}

void prepend(Vector *v, int item){
	insert(v,0,item);
}

int pop(Vector *v){
	int a = *(v->p+getSize(v)-1);
	*(v->p + getSize(v) - 1) = 0;
	decrementSize(v);
	return a;
}

void erase(Vector *v, int index){
	moveTo(v,index,'l');
	decrementSize(v);
}

void removeAll(Vector *v, int item){
	for (int i = 0; i < getSize(v); i++)
	{
		if (*(v->p+i) == item)
		{
			erase(v,i);
			if (i > 0) {
				i -= 2;
			}
		}
	}
}

int find(Vector *v, int item){
	for (int i = 0; i < getSize(v); i++) {
		if (*(v->p + i) == item)
		{
			return i;
		}
	}
	return -1;
}

void resize(Vector *v, int newCapacity){
	*v->_capacity = newCapacity;
	ownRealloc(v,newCapacity);
}
/////////////////////////////////////////////////FIN PROGRAMA////////////////////////////////////////////////////////////














