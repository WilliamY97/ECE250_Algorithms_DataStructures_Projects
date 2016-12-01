
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?


struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
	
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	// An array of pointers that keeps a pointer to each node entry in the linked lists
	ll_entry** nodes;
	/* An array of pointers that keeps the information for each sets. This information
	includes the pointers to head and tail of the set as well as an integer that keeps the size of the set. */
	set_info** sets;
	// A variable that saves the current number of sets.
	int set_counter;
	// A variable that saves the initial number of sets
	int initial_num_sets;
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
};

/* Constructs a disjoint sets data structures with n sets each containing one element
(therefore the total number of elements in n). */
Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]), 
sets (new set_info*[n]), 
set_counter(n),
initial_num_sets(n) {
	// initialize the sets
	for (int i = 0; i < initial_num_sets; i++) {
		nodes[i] = new ll_entry();
		sets[i] = new set_info();

		nodes[i] -> content = i;
		nodes[i] -> next = nullptr;

		sets[i] -> head = nodes[i];
		sets[i] -> tail = nodes[i];
		sets[i] -> size = 1;

		nodes[i] -> ptr_to_info = sets[i];
	}



}

// Cleans up any allocated memory.
Disjoint_set::~Disjoint_set() {
	// deallocate memory


	for (int i = 0; i < initial_num_sets; i++){
		delete nodes[i];
		delete sets[i];	
	}

	delete[] nodes;
	delete[] sets;
}

// Returns the representative of the set that the input belongs to.
int Disjoint_set::find_set(int item) const{
	// should it be? return nodes[item]->ptr_to_info->head->content 
	return nodes[item]->ptr_to_info->head->content;
}

// Returns the number of sets.
int Disjoint_set::num_sets() const {
	return set_counter;
}

/* Unites the dynamic sets that contain node_index1 and node_index2.*/
void Disjoint_set::union_sets(int node_index1, int node_index2) {
	


	if (node_index1 == node_index2)
		return;
	

	set_info* si1 = nodes[node_index1]->ptr_to_info;
	set_info* si2 = nodes[node_index2]->ptr_to_info;



	// ni1: the index of the larger set, ni2: the index of the smaller index
	int ni1 = si1->size >= si2->size ? node_index1 : node_index2; 
	int ni2 = si1->size < si2->size ? node_index1 : node_index2;


	si1 = nodes[ni1]->ptr_to_info;
	si2 = nodes[ni2]->ptr_to_info;



	ll_entry* si2_nodes = nodes[ni2] -> ptr_to_info -> head;
	set_info* si2_info = nodes[ni2] -> ptr_to_info;




	// Set tail of bigger set si1 to point to head of smaller set si2
	si1 -> tail -> next = si2_nodes;


	// The small sets tail is now the tail of the big set
	si1 -> tail = si2_info -> tail;



	//iterate through the shorter list and modify the pointers
	// make pointers point to new set
	while (si2_nodes != nullptr) {
		//cout << ni1 << endl;
		//Set info pointer of si1 to equal info of set two

		si2_nodes -> ptr_to_info = si1;
		si2_nodes = si2_nodes -> next;

		ni1++;

	}



	// do we need to modify anything else?
	set_counter--;
	// delete the set_info entry that no longer exists
	
	//cout << "sI" << endl;

	//delete si2_info;

	
}


#endif
