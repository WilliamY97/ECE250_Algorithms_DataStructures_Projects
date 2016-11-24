#include <iostream>

#include "Dynamic_deque_as_array.h"

using namespace std;

int main() {

	cout << "Create Double Ended Queue" << endl;
	Dynamic_deque_as_array a(10);

	cout << "Check size of Dequeue" << endl;
	cout << a.size() << endl;
	cout << a.capacity() << endl;
	cout << a.empty() << endl;

}