//
//  unorderedLinkedList.hpp
//  Banking
//
//  Created by Daniel  Fernandez on 10/14/19.
//  Copyright © 2019 Daniel  Fernandez. All rights reserved.
//

#ifndef unorderedLinkedList_hpp
#define unorderedLinkedList_hpp

#include "linkedList.hpp"

template <class T>
class unorderedLinkedList : public linkedList<T> {
public:
    void insert(const T &element);
    void removeFrom(int start);
    
    T& last() { return linkedList<T>::last->value; }
    
    unorderedLinkedList(): linkedList<T>() {}
    unorderedLinkedList(const unorderedLinkedList &list);
};

template <class T>
void unorderedLinkedList<T>::insert(const T &element) {
    Node<T> *newNode = new Node<T>(element);
    if(linkedList<T>::first) {
        linkedList<T>::last->next = newNode;
        linkedList<T>::last = linkedList<T>::last->next;
        linkedList<T>::length++;
    } else {
        linkedList<T>::first = newNode;
        linkedList<T>::last = linkedList<T>::first;
        linkedList<T>::length++;
    }
        
}

template<class T>
void unorderedLinkedList<T>::removeFrom(int start) {
    if (start >= 0 && start < linkedList<T>::length) {
        if (linkedList<T>::length > 0) {
            if(linkedList<T>::length == 1 || start == 0) {
                delete linkedList<T>::first;
                linkedList<T>::first = nullptr;
                linkedList<T>::last = nullptr;
                linkedList<T>::length = 0;
            } else {
                
                Node<T> *current = linkedList<T>::first;
                for(int i = 0; i < start - 1; i++)
                    current = current->next;
                
                delete current->next;
                current->next = nullptr;
                linkedList<T>::last = current;
                linkedList<T>::length = start;
                
            }
        }
    }
}

template <class T>
unorderedLinkedList<T>::unorderedLinkedList(const unorderedLinkedList &list) {
    Node<T> *current = list.first;
    
    while(current) {
        insert(current->value);
        current = current->next;
    }
}

#endif /* unorderedLinkedList_hpp */
