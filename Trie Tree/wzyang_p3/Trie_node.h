/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  wzyang @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    - Isaac Sy
 *****************************************/

#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
using namespace std;
#include <string>
#include <cctype>
#include "ece250.h"

class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		static int const CHARACTERS = 26;
		int charToNum(char const & ) const;

	public:
		Trie_node();
		Trie_node *child( int ) const;

		bool member( std::string const &, int ) const;

		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *& );
		void clear();

		friend class Trie;

		// if ptr is a pointer to a Trie_node object
		// in one of the friendly classes, you should:
		//    use   ptr->next_   to modify it
		//    use   ptr->next()      to access it
};

int Trie_node::charToNum(char const & character) const {
	char modified = character;

	modified = tolower(modified);

	if (modified < 97){
	modified += 32;
	}
	return modified - 'a';
}

Trie_node::Trie_node():
children( ),
is_terminal( false ) {
	// empty constructor
}

Trie_node *Trie_node::child( int n ) const {
	if ( children[n] == nullptr ) {
		return nullptr;
	} else {
		return children[n];
	}
}

bool Trie_node::member( std::string const &str, int depth ) const {
	char character = str[depth];
	int Cindex = charToNum(character);

	// (Base Case) If the depth is the length of the str then return true
	if ((depth) == str.length()){

		if (is_terminal){
			return true;
		}
		else{
			return false;	
		}
	}

	// If current character slot is not empty then call member on it
	if (children == nullptr){
		return false;
	}
	else if (children[Cindex] == nullptr){
		return false;
	}
	// If it is empty then return false since the str is not a member
	else {
		return children[Cindex] -> member(str, depth + 1);
	}
}

bool Trie_node::insert( std::string const &str, int depth ) {
	char character = str[depth];

	// If node's children is not initialized then create slots for it
	if ( children == nullptr ) {
		children = new Trie_node*[26];
		for (int i = 0; i < 26; i++) {
			children[i] = nullptr;
		}
	}

	// Initializes parameters for future conditions
	bool lastCharacter = (depth+1 == str.length());
	int Cindex = charToNum(character);

	// If the slot is empty then insert a new node into that location 
	if ( children[Cindex] == nullptr ) {
		children[Cindex] = new Trie_node();
	}
	
	// Base Case (Checks if we're looking at last character)
	if (lastCharacter) {
		if (children[Cindex] -> is_terminal == true){
			return false;
		}
		else {
		children[Cindex] -> is_terminal = true;	
			return true;	
		}
	}

	return children[Cindex] -> insert(str, depth + 1);
	
}

bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {

	char character = str[depth];
	int Cindex = charToNum(character);
	bool terminalDel = false;

	if (is_terminal && (depth == str.length())){
		if (this -> children){
			for(int i = 0; i < 26; i++)
			{
				if(this->children[i] != nullptr){
					is_terminal = false;
					return true;
				}
			}

		}
			delete[] this -> children;
			delete this;
			ptr_to_this = nullptr;
			return true;
	}
	else {
			terminalDel = children[Cindex] -> erase(str,depth+1,children[Cindex]);
	}

	if (terminalDel == true){

		if(is_terminal){
			return true;
		}

		for(int i = 0; i < 26; i++)
		{	
			if(this->children[i] != nullptr){
				return true;
			}
		} 
			delete[] this -> children;
			delete this;
			ptr_to_this = nullptr;
			return true;
	}
	else {
		return false;
	}
}

void Trie_node::clear() {

	//Does the node have children slots initialized?
	if(this -> children)
	{		
		// Go thorugh each child slot
		for(int i = 0; i < 26; i++)
		{	
			//Go through each child and call clear
			if(this->children[i]){
				this->children[i]->clear();
			}
		}		

		//Deletes each of the children array
		delete[] this->children;
	}

	//Deletes this node
	delete this;
	return;

}


// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
