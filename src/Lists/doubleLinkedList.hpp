//
//  doubleLinkedList.hpp
//  HurricaneEvac
//
//  Created by Daniel  Fernandez on 10/11/19.
//  Copyright © 2019 Daniel  Fernandez. All rights reserved.
//

#ifndef doubleLinkedList_hpp
#define doubleLinkedList_hpp

#include "linkedList.hpp"

enum REM_FLAG { REMOVE_BY_INDEX };

template <class T>
class orderedDoubleLinkedList : public linkedList<T> {
public:
    void insert(const T &element);
    void remove(const T &element);
    void remove(int index, REM_FLAG rem);
    
    linkedListIterator<T> rbegin();
    linkedListIterator<T> rend();
};

template <class T>
void orderedDoubleLinkedList<T>::insert(const T &element) {
    Node<T> *newNode = new Node<T>(element);
    
    if(!linkedList<T>::first) {
        linkedList<T>::first = newNode;
        linkedList<T>::last = newNode;
        linkedList<T>::length++;
    } else {
        Node<T> *current = linkedList<T>::first;
        if(element > linkedList<T>::last->value) {
            newNode->prev = linkedList<T>::last;
            linkedList<T>::last->next = newNode;
            linkedList<T>::last = linkedList<T>::last->next;
            linkedList<T>::length++;
        } else {
            while(current) {
                if(element < current->value) {
                    //insert before current
                    newNode->next = current;
                    newNode->prev = current->prev;
                    current->prev = newNode;
                    if(newNode->prev)
                        current->prev->next = newNode;
                    else
                        linkedList<T>::first = newNode;
                    linkedList<T>::length++;
                    break;
                } else {
                    current = current->next;
                }
            }
        }
    }
}

template <class T>
void orderedDoubleLinkedList<T>::remove(const T &element) {
    
}

template <class T>
linkedListIterator<T> orderedDoubleLinkedList<T>::rbegin() {
    return linkedListIterator<T>(linkedList<T>::last);
}

template <class T>
linkedListIterator<T> orderedDoubleLinkedList<T>::rend() {
    return linkedListIterator<T>(nullptr);
}

template<class T>
void orderedDoubleLinkedList<T>::remove(int index, REM_FLAG rem) {
    if (index < 0 || index >= linkedList<T>::length)
        throw std::out_of_range("Index out of range");
    
    int counter = 0;
    Node<T> *current = linkedList<T>::first;
    
    while (counter < index) {
        current = current->next;
        counter++;
    }
    
    //delete current
    if(current->next) {
        current->next->prev = current->prev;
    } else {
        linkedList<T>::last = current->prev;
    }
    if(current->prev) {
        current->prev->next = current->next;
    } else {
        linkedList<T>::first = current->next;
    }
    delete current;
    linkedList<T>::length--;
}

#endif /* doubleLinkedList_hpp */
