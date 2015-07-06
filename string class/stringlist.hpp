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
  /// Forward declaration
  class ListElement;

  /// const iterator for StringList class
  class StringListIterator
  {
  public:
    /// Constructor, sets current to dummy p
    StringListIterator(const ListElement* p)
    {
      current = p;
    }

    /// Equal to: checks if two lists are the same
    friend bool operator==(const StringList& s1, const StringList& s2)
    {
      return s1.current == s2.current;
    }

    /// Not equal: check if two iterators are not equal
    friend bool operator!=(const StringListIterator& i1, const StringListIterator& i2)
    {
      return !(i1 == i2);
    }

    /// Increment operator
    StringListIterator& operator++()
    {
      if (current != 0)
        current = current->next;
      return *this;
    }
    
    /// Dereference interator and return list element
    const std::string& operator*() const
    {
      return current->content;
    }

    private:
      /// Actual iterator
      const ListElement* current;
  }; /// StringListIterator

  typedef StringListIterator const_iterator;

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
    copy_list(src);
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
      copy_list(src);
    }
    return *this;  
  }

  /// Equal to: checks if two lists are the same
  friend bool operator==(const StringList& s1, const StringList& s2)
  {
    // Lists can't be equal if they don't contain the same number of elements
    if (s1.length() != s2.length()) return false;
    // Iterate over both lists simultaneously and compare element pairs
    const ListElement* e1, *e2;
    for (e1 = s1.first, e2 = s2.first; e1 != 0; e1=e1->next, e2=e2->next) {
      if (e1->content != e2->content) 
        return false;
    }
    return true;
  }

  /// Not equal: check if two lists are not equal
  friend bool operator!=(const StringList& s1, const StringList& s2)
  {
    return !(s1 == s2);
  }

  /// Less than: checks if one list is smaller than the other
  // i.e. either one list contains fewer elements than the other
  // or one list is lexicographically "smaller" than the other
  friend bool operator<(const StringList& s1, const StringList& s2)
  {
    // Compare up to first inequality
    const ListElement* e1, *e2;
    for (e1 = s1.first, e2 = s2.first; e1 != 0 && e2 != 0; e1=e1->next, e2=e2->next) {
      if (e1->content < e2->content) return true;
      if (e2->content < e1->content) return false;
      // Continue searching
    }
    return (e1 == 0 && e2 != 0);
  }

  /// Overload << to easily print lists on std::cout
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
    // Generate new list element and save in e
    ListElement* e = new ListElement(s,first);
    // If list is emtpy, first element is last element
    if (first == 0) 
      last = e;
    // New element becomes first element
    first = e;
    ++len;
  }
  
  /// Appends string s at the end of a list
  void append_back(const string& s)
  {
    if (is_empty()) {
      // Same as above
      append_front(s);
    }
    else {
      ListElement* e = new ListElement(s,0);
      last->next = e;
      last = e;
      ++len;
    }
  }
  
  /// Return head of list
  const std::string& head() const
  {
    static const std::string invalid;
    return (first == 0) ? invalid : first->content;
  }

  // Pretty printing
  std::string& head() 
  {
    static std::string invalid;
    return (first == 0) ? invalid : first->content;
  }

  /// Removes all elements of a list
  /// Returns memory allocated by new back to the heap
  void clear()
  {
    clear_recursive(first);
    //clear_iterative();
    first = last = 0;
    len = 0;
  }
  
  /// Return iterator to beginning of list
  const_iterator begin() const
  {
    return const_iterator(first);
  }
    
  /// Return iterator to end of list
  const_iterator end() const
  {
    return const_iterator(0);
  }
  
  /// Return length of list
  unsigned length() const
  {
    return len;
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
    return out;
  }
  
private: // Types
  /// Type list element
  struct ListElement 
  {
    ListElement(const std::string& s, ListElement* n)
    {
      content = s;
      next = n;
    }
    
    std::string content;  // Current content
    ListElement* next;    // Pointer to next element
  }; // ListElement
 
private:

  void init()
  {
    first = last = 0;
    len = 0;
  }

  /// copy list
  void copy_list(const StringList& l)
  {
    for (ListElement* c = l.first; c != 0; c = c->next) {
      append_back(c->content);
    }
  }
  
  void clear_recursive(ListElement* l)
  {
    if (l != 0) {
      clear_recursive(l->next);
      delete l;
    }
  }

  void clear_iterative()
  {
    for (ListElement* c = first; c != 0;) {
      ListElement* n = c->next;
      delete c;
      c = n;
    }
  }

private:
  /// first points to the first list element
  ListElement* first;    
  /// last points to the last list element
  ListElement* last;
  /// Length of list
  unsigned len;
}; // StringList

/// Print to ostream
std::ostream& operator<<(std::ostream& o, const StringList& l)
{
  return l.print(o);
}