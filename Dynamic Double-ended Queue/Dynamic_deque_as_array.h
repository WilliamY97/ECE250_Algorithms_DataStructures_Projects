#ifndef DYNAMIC_DEQUE_AS_ARRAY_H
#define DYNAMIC_DEQUE_AS_ARRAY_H

/*
Name: William Yang
UW User ID: wzyang
ECE 250 with Professor Tahvildari
*/

#include "ece250.h"
#include "Exception.h"


class Dynamic_deque_as_array
{
	private:
		/*Encapsulated data*/

		//point to array
		int* array;

		int _head;
		int _tail;
		int _count;
		int array_size;

	public:
		Dynamic_deque_as_array( int = 10 );
		~Dynamic_deque_as_array();


		int head() const;
		int tail() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void enqueue_head( const int & );
		void enqueue_tail( const int & );
		void double_array();
		int dequeue_head();
		int dequeue_tail();
		void clear();
};

/* Constructor takes argument as the capacity of the array
and allocates memory for that array. The default capacity
(or # of entries) is 10. If the arguement n is less than one
, use and array size of 1. Other class members should be assigned
appropriate values */
Dynamic_deque_as_array::Dynamic_deque_as_array( int n) {
	// returns greater of input 1 to n of array size
	array_size = std::max(1,n);
	// create array and initialize head and tail to index 0
	array = new int [array_size];
	_head = 0;
	_tail = 0;
	_count = 0;

}



// Destructor: Deletes memory allocated for array
Dynamic_deque_as_array::~Dynamic_deque_as_array() {

	// deletes array
	delete [] array;
}


// Accessors

// Size: Return the number of elements currently stored in deque
// O(1) Time
int Dynamic_deque_as_array::size() const {
	return _count;
}

// Capacity: Return the cpacity of deque in
// O(1) Time
int Dynamic_deque_as_array::capacity() const {
	return array_size;
}

// Empty: Return true if deque is empty, false otherwise
// O(1) Time
bool Dynamic_deque_as_array::empty() const {
	// 
	return (_count == 0);
}

// Head: Return integer at head of the deque
// O(1) it may throw underflow exception 
int Dynamic_deque_as_array::head() const {

	if (!empty()) {
		return array[_head];

	}

	else {
		throw underflow();
	}

}

// Head: Return integer at tail of the deque
// O(1) it may throw underflow exception 
int Dynamic_deque_as_array::tail() const {

	if (!empty()) {
		return array[_tail];

	}

	else {
		throw underflow();
	}

}


// Mutators

/* Enqueue head: Insert new item at the head of the deque
If the array is full, create new array with size 2n 
(where n is current size of array) and copy elements from
current array to the new array in O(N)
*/

void Dynamic_deque_as_array::double_array() {
	// instantiates new array with double the size of old one
	int newSize = array_size*2;
	int * newArray = new int[newSize];

	// copies over values from old array into new one from tail to head
	for (int i=0;i < array_size; i++) {

		newArray[i] = array[_tail];	
		_tail = (_tail + 1) % array_size;
	} 

	// delete old array and set array to new one
	delete [] array;
	array = newArray;

	// set array size to the new double size and put tail on 0 and head
	// on the farthest right of array
	array_size = newSize;
	_tail = 0;
	_head = _count - 1;

}


void Dynamic_deque_as_array::enqueue_head( const int &obj ) {

	// If it's the first value to be added to the array
	// the head index will not need to move
	if (_count == 0) {
		_head = 0;
		_tail = 0;
		array[_head] = obj;
		_count ++;
		return;
	}
	// If max size is reached - double array size
	else if (_count == array_size) {
		double_array();
	}

	// Increase count of the values in the array and
	// shift head index to right - wraps around array if at the end
	_count ++;
	_head = ((_head + 1 + array_size) % array_size);
	array[_head] = obj;

}

/* Enqueue tail: Insert a new item at the tail of the deque 
in O(1). If the array is full, create a new array with size 2n
(where n is current size of the array) and copy the elements from
current array to the new array in O(n)
*/
void Dynamic_deque_as_array::enqueue_tail( const int &obj ) {

	// If it's the first value to be added to the array
	// the tail index will not need to move
	if (_count == 0) {
		_head = 0;
		_tail = 0;
		array[_tail] = obj;
		_count ++;
		return;
	}
	// If max size is reached - double array size
	else if (_count == array_size) {
		double_array();
	}

	// Increase count of the values in the array and
	// shift head index to left - wraps around array if at the end
	_count ++;
	_tail = ((array_size + _tail - 1) % array_size);
	array[_tail] = obj;

}

/* Dequeue head: Remove the element at the head of the deque 
in O(1). This may throw an underflow exception.
*/
int Dynamic_deque_as_array::dequeue_head() {

	// If nothing in array throw underflow
	if (_count==0){
		throw underflow();
	}

	// Returns value at head and shifts head index left - wraps
	// around if at the end of the array
	int value = array[_head];
    _head = ((array_size + _head - 1) % array_size);
    _count--;
    return value;

}

/* Dequeue tail: Remove the element at the tail of the deque
in O(1). This may throw an underflow exception.
*/
int Dynamic_deque_as_array::dequeue_tail() {

	// If nothing in array throw underflow
	if (_count==0){
		throw underflow();
	}

	// Returns value at tail and shifts tail index right - wraps
	// around if at the end of the array
	int value = array[_tail];
    _tail = (_tail + 1 + array_size) % array_size;;
    _count--;
    return value;

}

/* Clear: Remove all elements from the deque in O(1) 
*/
void Dynamic_deque_as_array::clear() {
	_head = _tail = 0;
    _count = 0;
}

#endif
