////////////////////////////////////////////////////////////////////////////////
// test_stringlist.cpp
// Tests single-linked list of ASCIIZ strings
// Melanie Tosik (759476)
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
using namespace std;

#include "stringlist.hpp"

int main() {
	cout << "\n" << "TEST\n\n";

	cout << "Create new list l...\n";
	StringList l;
	cout << "Should be empty in the beginning: ";
	l.print();
	cout << "\n\n";

	cout << "Let's make it a grocery list...\n\n";
	cout << "Butter and sugar at the front...\n";
	l.append_front("butter");
	l.append_front("sugar");
	cout << "Check: ";
	l.print();
	cout << "\n\n";

	cout << "Flour and an egg at the end...\n";
	l.append_back("flour");
	l.append_back("egg");
	cout << "Looks good: ";
	l.print();
	cout << "\n\n";

	cout << "Copy l to l2 so the rest of the family know what's up...\n";
	StringList l2(l);
	cout << "Copying done: ";
	l2.print();
	cout << "\n\n";

	cout << "Let's clear l2 again...\n\n";
	l2.clear();

	cout << "Did that work?\n";
	if (l2.is_empty()) {
		cout << "Empty!\n";
	} else {
		cout << "Not empty!\n"; 
	}
	l2.print();
	cout << "\n\n";

	cout << "... and use assignment instead...\n";
	l2 = l;
	cout << "There it is: ";
	l2.print();
	cout << "\n\n";

	cout << "How many things will we have to carry again?\n";
	cout << l2.length() << "\n\n";

	cout << "Make sure the two lists are the same?\n";
	if (l == l2) {
		cout << "Equal!\n\n";
	} else {
		cout << "Not equal!\n\n"; 
	}

	cout << "Or is l smaller than l2?\n";
	if (l < l2) {
		cout << "Smaller!\n\n";
	} else {
		cout << "Not smaller!\n\n"; 
	}

	cout << "Better get more than one egg though...\n\n";
	l2.clear();
	l2.append_back("sugar");
	l2.append_back("butter");
	l2.append_back("flour");
	l2.append_back("eggs");

	cout << "First list:\t";
	l.print();
	cout << "\n";
	cout << "Second list:\t";
	l2.print();
	cout << "\n\n";

	cout << "Still the same?\n";
	if (l == l2) {
		cout << "Equal!\n\n";
	} else {
		cout << "Not equal!\n\n"; 
	}

	cout << "Or maybe l is smaller than l2 now?\n";
	if (l < l2) {
		cout << "Smaller!\n\n";
	} else {
		cout << "Not smaller!\n\n"; 
	}

	cout << "But then l2 shouldn't be smaller than l, right?\n";
	if (l2 < l) {
		cout << "Smaller!\n\n";
	} else {
		cout << "Not smaller! Phew!\n\n"; 
	}

	cout << "Should I have used the new << operator instead of print()ing all those lists?\n\n";
	cout << l << "\n";
	cout << l2 << "\n\n";
	cout << "Looks like it!\n";
}