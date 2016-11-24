#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

/*****************************************
 * UW User ID:  wzyang
 * Submitted for ECE 250
 * Semester of Submission:  Fall 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "Exception.h"
#include "ece250.h"

enum state {EMPTY, OCCUPIED, DELETED};

template<typename T>
class LinearHashTable {
	private:
		// Member Variables
		int count;
		int power;
		int array_size;
        	int mod;
		T *array;
		state *occupied;


	public:
		LinearHashTable( int = 5 );
		~LinearHashTable();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;


		void insert( T const & );
		bool remove( T const & );
		void clear();
		void print() const;
};


// CONSTRUCTOR


// The constructor takes an argument m and creates a hash table with 2^m bins, indexed from 0 to 2m − 1. The
// default value of m is 5. Notice that you need to allocate and initialize two arrays, one that stores the values
// in the hash table, and the other that stores the status of the bins. 

// EMPTY, OCCUPIED, DELETED
template<typename T >
LinearHashTable<T >::LinearHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
occupied( new state [array_size] )
{

	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = EMPTY;
	}

}


// DESTRUCTOR


// The destructor deletes the memory allocated for the hash table. Notice that the hash table has been
// represented using two arrays, and they both need to be deleted.
template<typename T >
LinearHashTable<T >::~LinearHashTable() {
	delete [] array;
	delete [] occupied;
}


// ACCESSORS


// Return the number of elements currently stored in the hash table. (O(1))
template<typename T >
int LinearHashTable<T >::size() const {
	return count;
}

// Return the number of bins in the hash table. (O(1))
template<typename T >
int LinearHashTable<T >::capacity() const {
	return array_size;
}

// Return the load factor of the hash table. (O(1))
template<typename T >
double LinearHashTable<T >::load_factor() const {
	return (double)(count)/(double)(array_size);
}

// Return true if the hash table is empty, false otherwise. (O(1))
template<typename T >
bool LinearHashTable<T >::empty() const {
	return count == 0;
}

// Return true if object obj is in the hash table and false otherwise. (O(1))
template<typename T >
bool LinearHashTable<T >::member( T const &obj ) const {
    int i = 0;

    int key = static_cast<int>(obj) % array_size;

    // checks if key value is negative
    // if so re-adjust it to be positive
    if (key < 0) {
    	key = (key % array_size) + array_size;
   	}   

   	// checks status if slot to see if it needs to be checked for value
   	// if the key equals the one we need then return true
    while (occupied[key] != EMPTY){
    	key = (static_cast<int>(obj)+i) % array_size;
    	if (key < 0) {
    		key = (key % array_size) + array_size;
    	}   
    	if (occupied[key] != DELETED) {
    		if (array[key] == obj){
    			return true;
    		}    	
    	} 

    	i++;
    }
    return false;
}

// Return the entry in bin n. The behaviour of this function is undefined if the bin
// is not filled. It will only be used to test the class with the expected locations. (O(1))
template<typename T >
T LinearHashTable<T >::bin( int n ) const {
    // Checks if the slot is occupied - if so return the value
    if (occupied[n] == OCCUPIED){
    	return array[n];
    }
    // Unoccupied slots are returned as zero
    else {
    	return 0;
    }
}


// MUTATORS 


// If load factor is less than or equal to 0.75, you have to insert the new
//object into the hash table in the appropriate bin as determined by the hash function and the rules
//of linear probing (O(1)). Otherwise, double the size of hash table, rehash all elements, and then
//insert the new element (O(n)).

template<typename T >
void LinearHashTable<T >::insert( T const &obj ) {
	 // Checks load factor if the array size needs to be double to maintain load factor
	if (load_factor() > 0.75) {
		array_size = array_size*2;
		count = 0;

	 // Create new arrays to hold previous values and then perform a transfer into larger one

		T *oldArray = new T [array_size/2];

		for (int i = 0; i < array_size/2; ++i){
			oldArray[i] = array[i];

		}

		T *newArray = new T [array_size];
		delete [] array;
		array = newArray;

		state *oldOccup = new state [array_size/2];

		for (int i = 0; i < array_size/2; ++i){
			oldOccup[i] = occupied[i];
		}
		state *newOccup = new state [array_size];
		delete [] occupied;
		occupied = newOccup;

		for (int i = 0; i < array_size/2; ++i){
			if (oldOccup[i] == OCCUPIED){
				insert(oldArray[i]);
			}
		}
		delete [] oldArray;
		delete [] oldOccup;
	}
	
	int i = 0;
	int key = 0;
	do 	{
		key = (static_cast<int>(obj) + i) % array_size;
		//checks if negative key and makes positive
    	if (key < 0) {
    		key = (key % array_size) + array_size;
    	}
		i++;
	}
	while(occupied[key] == OCCUPIED);

	array[key] = obj;
	occupied[key] = OCCUPIED;
	count++;

}

// If the load factor is greater than 0.25, you have to remove the object
// from the hash table if it is in the hash table (returning false if it is not) by setting the
// corresponding flag of the bin to “DELETED”. (O(1)). Otherwise, if the load factor is less than
// 0.25 and the current capacity of hash table is not equal to the initial capacity (that was assigned in
// the constructor), you have to shrink the capacity of the hash table to the half of its current size,
// rehash the elements, and remove the input from the table (O(n)).

template<typename T >
bool LinearHashTable<T >::remove( T const &obj ) {
	// Checks load factor if the array size needs to be halved to maintain load factor

	if (load_factor() <= 0.25 && array_size != (1 << power)) {
		array_size = array_size/2;
		count = 0;
		T *oldArray = new T [array_size*2];

		for (int i = 0; i < array_size*2; ++i){
			oldArray[i] = array[i];

		}

	// Create new arrays to hold previous values and then perform a transfer into smaller one
		T *newArray = new T [array_size];
		delete [] array;
		array = newArray;

		state *oldOccup = new state [array_size*2];

		for (int i = 0; i < array_size*2; ++i){
			oldOccup[i] = occupied[i];
		}

		state *newOccup = new state [array_size];

		delete [] occupied;
		occupied = newOccup;

		for (int i = 0; i < array_size*2; ++i){
			if (oldOccup[i] == OCCUPIED){
				insert(oldArray[i]);
			}
		}
		delete [] oldOccup;
		delete [] oldArray;
	}
	
    int i = 0;

    int key = static_cast<int>(obj) % array_size;

    if (key < 0) {
    	key = (key % array_size) + array_size;
    }

    while (occupied[key] != EMPTY){
    	key = (static_cast<int>(obj)+i) % array_size;
    	if (key < 0) {
    		key = (key % array_size) + array_size;
    	}    	
    	if (occupied[key] != DELETED) {
    		if (array[key] == obj){
    			occupied[key] = DELETED;
    			count--;
    			return true;
    		}    	
    	} 

    	i++;
    }

    return false;

}

// Remove all the elements in the hash table. (O(m))

template<typename T >
void LinearHashTable<T >::clear() {
	// Sets all slots to EMPTY
	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = EMPTY;
	}
	count = 0;

}


// TESTER
// A function I can use to print the class in the testing environment.

template<typename T >
void LinearHashTable<T >::print() const{
	for ( int i = 0; i < array_size; ++i ) {
			std::cout << array[i];
	}

}

#endif
