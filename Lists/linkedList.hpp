//
//  linkedList.hpp
//  HurricaneEvac
//
//  Created by Daniel  Fernandez on 10/9/19.
//  Copyright © 2019 Daniel  Fernandez. All rights reserved.
//

#ifndef linkedList_hpp
#define linkedList_hpp

#include <iostream>

template<class T>
struct Node {
    T value;
    Node* next;
    Node* prev;
    Node(T val) : value(val), next(nullptr), prev(nullptr) {}
};

template<class T>
class linkedListIterator {
public:
    void operator++();
    void operator--();
    T operator* ();
    T* getPtr();
    
    bool operator!=(const linkedListIterator<T> &itr);
    bool operator==(const linkedListIterator<T> &itr);
    
    linkedListIterator(Node<T>* itr) : current(itr) {}
    linkedListIterator() : current(nullptr) {}
    linkedListIterator(const linkedListIterator<T> &itr) : current(itr.current) {}
private:
    Node<T>* current;
};


template <class T>
class linkedList {
public:
    int size() { return length; }
    
    T& at (int index);
    T& operator[] (int index) { return at(index); }
    
    virtual void insert(const T &element) = 0;
    virtual void remove(const T &element);
    
    int seqSearch(const T &element);
    
    //iterators
    linkedListIterator<T> begin();
    linkedListIterator<T> end();
    
    linkedList() : length(0), first(nullptr), last(nullptr) {}
protected:
    int length;
    Node<T>* first;
    Node<T>* last;
    
};

//classs linkedListIterator
template<class T>
void linkedListIterator<T>::operator++() {
    if(current)
        current = current->next;
}

template<class T>
void linkedListIterator<T>::operator--() {
    if(current)
        current = current->prev;
}

template <class T>
T linkedListIterator<T>::operator*() {
    if(current)
        return current->value;
    throw std::logic_error("Pointer arror");
}

template<class T>
T* linkedListIterator<T>::getPtr() {
    return &(current->value);
}

template<class T>
bool linkedListIterator<T>::operator!=(const linkedListIterator<T> &itr) {
    return current != itr.current;
}

template<class T>
bool linkedListIterator<T>::operator==(const linkedListIterator<T> &itr) {
    return current == itr.current;
}

//class linkedList
template <class T>
T& linkedList<T>::at (int index) {
    if (index < 0 || index >= length)
        throw std::out_of_range(std::to_string(index));
    Node<T>* current = first;
    
    for(int i = 0; i < index; i++)
        current = current->next;
    
    return current->value;
}

template<class T>
void linkedList<T>::remove(const T &element) {
    if(first) {
        if(first->value == element) {
            Node<T> *temp = first->next;
            delete first;
            first = temp;
            if(!first)
                last = nullptr;
            return;
        }
        if(first->next) {
            Node<T> *previous = first;
            Node<T> *current = first->next;
            
            while(current) {
                if(current->value == element) {
                    Node<T> *temp = current->next;
                    delete current;
                    if(!temp)
                        last = previous;
                    previous->next = temp;
                    return;
                    
                } else {
                    current = current->next;
                    previous = previous->next;
                }
            }
        }
    }
}

template <class T>
linkedListIterator<T> linkedList<T>::begin() {
    return linkedListIterator<T>(first);
}

template <class T>
linkedListIterator<T> linkedList<T>::end() {
    return linkedListIterator<T>(nullptr);
}

template <class T>
int linkedList<T>::seqSearch(const T &element) {
    int counter = 0;
    linkedListIterator<T> itr;
    for (itr = begin(); itr != end(); ++itr) {
        if (*itr == element)
            return counter;
        counter++;
    }
    return -1;
}
#endif /* linkedList_hpp */
