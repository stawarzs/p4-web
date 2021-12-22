#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL
using namespace std;


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const{
    if (first == nullptr){
      return true;
    } else {
      return false;
    }
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const{
    return sizeList;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    return first -> datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){
    return last -> datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){
    //create a new node
    Node *p = new Node;
    p -> datum = datum;
    p -> next = first;
    first = p;
    sizeList +=1;
}

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){
    Node *p = new Node;
    p-> datum = datum;
    p -> next  = nullptr;
    p -> prev = last;

    //special case 
      //if list was already empty
      if(empty()) {first = last = p;}
      else {
        last -> next = p;
        p -> next = nullptr;
        last = p;
      }

    sizeList += 1;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front(){
    if(first == nullptr){
      sizeList = 0;
      last = nullptr;
      return;
    }

    if (sizeList ==1){
      sizeList = 0;
      delete first;
      last = nullptr;
      first = nullptr;
      return;
    }
    
    else{
    Node *toDelete = first;
    first = first -> next;
    if (first != nullptr){
      first -> prev = nullptr;
    }
    delete toDelete;
    sizeList -=1;
    }
    
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back(){
    if(sizeList == 1){
      sizeList = 0;
      delete first;
      last = nullptr;
      first = nullptr;
      return;
    }
    Node *toDelete = last;
    last = last -> prev;
    last -> next = nullptr;
    sizeList -=1;
    delete toDelete;
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){
    
    while (!empty()){
      pop_front();
    }

  }

  
  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

  //make a node default constructor here 
  List() : first(nullptr) {}

  //make a destructor here
    ~List(){
      //implement pop all as a helper function
      //to remove all the elements
      //https://www.youtube.com/watch?v=HjS3KVo0grM
      pop_all();
    }

  //make a copy constructor here
    List(const List &other)
      : first(nullptr), last(nullptr) {
        //implement push_all as a helper function
        //to copy back all elements
        //https://www.youtube.com/watch?v=HjS3KVo0grM
        push_all(other);
      }


    List& operator=(const List &rhs){
      if (this == &rhs){
        return *this;
      }
      pop_all();
      push_all(rhs);
      return *this;
    }
    
private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  int sizeList = 0;

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){
    assert(empty());
    for (Node *np = other.first; np; np = np -> next){
      push_back(np->datum);
    }
  }

  void pop_all(){
    while (!empty()){
      pop_front();
    }
  }

  void push_all(const List &other){
    for (Node *np = other.first; np; np = np -> next){
      push_back(np->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List
    friend class List;
    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    Iterator() : node_ptr(nullptr) {}
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    T & operator*() const {
      assert(node_ptr);
      return node_ptr -> datum;
    }

    Iterator& operator++(){
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    bool operator==(Iterator rhs) const {
      return node_ptr == rhs.node_ptr;
    }

    bool operator!=(Iterator rhs) const {
      return !(node_ptr == rhs.node_ptr);
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here

    // construct an Iterator at a specific position
    Iterator(Node *p)
      : node_ptr(p) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
    
    // if i is end :: pop back
    if (i.node_ptr == last){
      pop_back();
    }  

     // if i is front :: push front 
    else if (i == begin()){
      pop_front();
    }

    else{
    /*change next, then prev of prior 
    then subsequent */
    (i.node_ptr -> prev) -> next  = (i.node_ptr -> next);
    (i.node_ptr -> next) -> prev  = (i.node_ptr -> prev);
    delete i.node_ptr;
    sizeList -=1;
    }
  

  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){
    
    // if i is end :: push back
    if (i == end()){
      push_back(datum);
    } 

    // if i is front :: push front 
    else if (i == begin()){
      push_front(datum);
    }

    else{
    //give datum a node
    Node *p = new Node{};
    
    //add middle, then prev, then next
    //set up needed values for middle node
    p -> datum = datum;
    p -> next = i.node_ptr; 
    p -> prev = i.node_ptr -> prev;
    
    //previous node
    (p -> prev) -> next = p;

    //next node
    (p -> next) -> prev = p;
    sizeList +=1;
    }
  
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
