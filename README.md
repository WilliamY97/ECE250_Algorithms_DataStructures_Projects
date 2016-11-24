# ECE250_Projects
A series of four lab projects I developed during the course **ECE250 - Algorithms and Data Structures** at the University of Waterloo.

## Project Descriptions

**1. Dynamic Double-ended Queue**

The goal of this project was to design and implement a dynamic deque data structure. A deque is a
queue that stores elements in an ordered list and allows insertions and deletions at both ends in
O(1) time and is able to increase its size if necessary in O(n).

**2. Open Addressing - Linear Hashing**

The goal of this project was to design and implement a hash table data structure. A hash table is a data
structure where values are mapped to an entry of a table using a hash function. For this project, linear
probing is used to resolve collision. The advantage of the hash table data structure is that it can achieve
constant expected time for insert and remove operations (O(1)).

**3. Trie Tree**

In this project I implemented a trie data structure using recursive programming. A trie is a 26-ary
tree where the root node represents an empty string “” and if the kth (k going from 0 to 25) sub-tree is not
a null sub-tree, it represents a string that is the concatenation of string represented by the parent and the
kth letter of the alphabet (where a is the 0th letter, b is the 1st letter, and so on). Each node may or may not
indicate that it is a terminal entry for a word. While a trie could be used to store hyphenated and
capitalized words together with those with apostrophes, we will restrict ourselves to words made up of the
twenty-six letters of the English alphabet.

**4. Minimum Spanning Tree (MST) - Kruskal's Algorithm**

TBD
