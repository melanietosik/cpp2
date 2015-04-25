////////////////////////////////////////////////////////////////////////////////
// stringlist.hpp
// Single-linked list of ASCIIZ strings
// TH, 20.4.2015
// Melanie Tosik (759476)
////////////////////////////////////////////////////////////////////////////////
 
#include <string>
#include <iostream>
using namespace std;

/// Class StringList implements a single-linked list of ASCIIZ strings
class StringList
{
public:
  /// Default constructor: creates an empty list
  StringList()
  {
    init();
  }

  /// Copy constructor: creates a new list as a copy of an existing one
  StringList(const StringList& src)
  {
    init();
    ListElement* c = src.first;
    for (; c!= 0; c = c->next) {
      append_back(c->content);
    }
  }

  /// Destructor
  ~StringList()
  {
    clear();
  }

  /// Assignment: assigns existing list to another list
  const StringList& operator=(const StringList& src)
  {
    if (this != &src) {
      clear();
      for (ListElement* c = src.first; c != 0; c = c->next) {
        append_back(c->content);
      }
    }
    return *this;  
  }

  /// Equal to: checks if two lists are the same
  friend bool operator==(const StringList& s1, const StringList& s2)
  {
    // Lists can't be equal if they don't contain the same number of elements
    if (s1.length() != s2.length()) return false;
    // Iterate over both lists simultaneously and compare element pairs
    ListElement* c1 = s1.first;
    ListElement* c2 = s2.first;
    for(; c1 != 0; ){
      if (c1->content != c2->content) return false;
      c1 = c1->next;
      c2 = c2->next;
    }
    return true;
  }

  /// Less than: checks if one list is smaller than the other
  // i.e. either one list contains fewer elements than the other
  // or one list is lexicographically "smaller" than the other
  friend bool operator<(const StringList& s1, const StringList& s2)
  {
    // Checks number of elements
    if (s1.length() < s2.length()) return true;
    // Checks lexicographically
    if (s1.length() == s2.length()) {
      ListElement* c1 = s1.first;
      ListElement* c2 = s2.first;
      // Iterate over both lists simultaneously and compare element pairs
      for(; c1 != 0; ){
        if (c1->content > c2->content) return false;
        if (c1->content < c2->content) return true;
        c1 = c1->next;
        c2 = c2->next;
      }
      // If lists are equal, return false
      return false;
    }
    else return false;
  }

  friend ostream& operator<<(ostream& o, const StringList& sl)
  {
    // WIP
    // o << sl.print();
    // return o;

    // For now same as print():
    o << "[";
    ListElement* c = sl.first;
    while (c != 0) {
      if (c != sl.last) 
        o << c->content << ", ";
      else {o << c->content;}
      c = c->next;
    } // while
    o << "]";
    return o;
  }

  /// Appends string s at the beginning of a list
  void append_front(const string& s)
  {
    ListElement* e = new ListElement;
    e->content = s;
    //TODO Redundant, change
    if (is_empty()) {
      first = last = e;
      e->next = 0;
    }
    else {
      e->next = first;
      first = e;
    }
  }
  
  /// Appends string s at the end of a list
  void append_back(const string& s)
  {
    if (is_empty()) {
      // Same as above
      append_front(s);
    }
    else {
      ListElement* e = new ListElement;
      e->content = s;
      e->next = 0;
      last->next = e;
      last = e;
    }
  }
  
  /// WIP
  string head()
  {
  }
  
  /// Removes all elements of a list
  /// Returns memory allocated by new back to the heap
  void clear()
  {
  for(ListElement* c = first; c != 0; c = c->next){
      ListElement* tmp = c;
      delete tmp;
    }
    first = last = 0;
  }
  
  /// Returns the number of elements in a list
  unsigned length() const
  {
    unsigned len = 0;
    for (ListElement* current = first; current != 0; current = current->next) {
      ++len;
    }
    return len;
  }
  
  /// Checks if list is empty
  bool is_empty()
  {
    return first == 0;
  }
    
  /// Prints list on std::cout
  void print()
  {
    cout << "[";
    ListElement* c = first;
    while (c != 0) {
      if (c != last) 
        cout << c->content << ", ";
      else {cout << c->content;}
      c = c->next;
    } // while
    cout << "]";
  }
  
private: // Types
  /// Type of list elements
  struct ListElement 
  {
    string content;  // String content
    ListElement* next;    // Pointer to next list element
  }; // ListElement
 
private:
  void init()
  {
    first = last = 0;
  }

private:
  /// first points to the first list element
  ListElement* first;    
  /// last points to the last list element
  ListElement* last;    
}; // StringList