/*
 * uWaterloo User ID:  wzyang @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2016
*/

#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;
		int charToNum(char const &);

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;

		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

int Trie::charToNum(char const & character){
	char modified = character;
	modified = tolower(modified);

	if (modified < 97){
	modified += 32;
	}
	return modified - 'a';
}

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor

}

Trie::~Trie() {
    if(root_node != nullptr){
	clear();
	}
	delete root_node;
}


// Returns the number of words in the trie. (O(1))
int Trie::size() const {
	return trie_size;
}

// Return true if the trie is empty (the size is 0). (O(1))
bool Trie::empty() const {
	return (trie_size == 0);
}

Trie_node *Trie::root() const {
	return root_node;
}

// Return true if the word represented by the string is in the
// Trie and false otherwise. If the string contains any characters other than those of the English
// alphabet (‘A’ through ‘Z’ or ‘a’ through ‘z’), throw an illegal_argument exception. (O(n))

bool Trie::member( std::string const &str ) const {

	for (int i = 0; i < str.length(); i++){
		if (!isalpha(str[i])) {
			throw illegal_argument();
		}
	}	

	if ( root_node == nullptr ){
		return false;
	} 

	return root_node -> member(str,0);	

}

// Insert the word represented by str into the tree. If the string contains
// any characters other than those of the English alphabet (‘A’ through ‘Z’ or ‘a’ through ‘z’), throw
// an illegal_argument exception; otherwise if the string is already in the tree, return false;
// otherwise, return true (the insertion was successful). This is done by calling insert on the root, and
// if the root node is null, it will be necessary create an instance of the Trie_node class and assign it
// to the root first. (O(n))

bool Trie::insert( std::string const &str ) {

	//Check for illegal arguments
	//Check if string alrady exists

	for (int i = 0; i < str.length(); i++){
	if (!isalpha(str[i])) {

		throw illegal_argument();
	}

	}	

	if ( root_node == nullptr ){
		root_node = new Trie_node();
	}

	bool result = root_node -> insert(str,0);
	if (result) {
		trie_size++;
	}
	
	return result;
}

// Erase the word represented by str from the tree. If the string contains
// any characters other than those of the English alphabet (‘A’ through ‘Z’ or ‘a’ through ‘z’), throw
// an illegal_argument exception; otherwise if the string is not in the tree, return false; otherwise,
// return true (the erase was successful). If the tree is empty, return false, otherwise this function
// calls erase on the root. If the word erased is the last one in the tree, delete the root node. (O(n))

bool Trie::erase( std::string const &str ) {


	for (int i = 0; i < str.length(); i++){
		if (!isalpha(str[i])) {
			throw illegal_argument();
		}
	}

	if ( empty() ){
	return false;
	}

	if(!member(str)){
		return false;
	}

	bool result = root_node -> erase(str,0,root_node);

	if (result){
		trie_size--;
	}

	return result;
}

// Delete all the nodes in the tree. Again, if the tree is not empty, it should just call
// clear on the root and set the appropriate member variables. (O(N) where N is the number of
// words in the tree)

void Trie::clear() {

    if(root_node != nullptr)
    {
        root_node -> clear();
        trie_size = 0;
    }
    root_node = nullptr;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
