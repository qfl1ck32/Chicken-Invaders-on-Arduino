#ifndef LinkedList_h
#define LinkedList_h

#include "Arduino.h"

template <class T>
class Node {
   public:
    T data;
    Node *next;

    Node();

    Node(T data);
};

template <class T>
class LinkedList {
   public:
    Node<T> *head;
    Node<T> *last;

    LinkedList() {
        this->head = nullptr;
        this->last = nullptr;

        this->size = 0;
    }

    int8_t size;

    void add(T data);
    T removeHead();

    void sort(int (*cmp)(T &, T &));

    Node<T> *findEndOfSortedString(Node<T> *p, int (*cmp)(T &, T &));
};

template <class T>
Node<T>::Node() {
    data = 0;
    next = nullptr;
}

template <class T>
Node<T>::Node(T data) {
    this->data = data;
    this->next = nullptr;
}

template <class T>
void LinkedList<T>::add(T data) {
    if (this->head == nullptr) {
        this->head = new Node<T>(data);
        this->last = head;
    }

    else {
        this->last->next = new Node<T>(data);
        this->last = this->last->next;
    }

    ++this->size;
}

template <class T>
T LinkedList<T>::removeHead() {
    if (this->size == 0) return T();

    T data = this->head->data;

    if (this->size == 1) {
        delete this->head;

        this->head = nullptr;
        this->last = nullptr;
    }

    else {
        Node<T> *temp = head;
        this->head = this->head->next;
        delete temp;
    }

    --this->size;

    return data;
}

template <class T>
void LinkedList<T>::sort(int (*cmp)(T &, T &)) {
    if (this->size < 2) return;

    for (;;) {
        Node<T> **joinPoint = &this->head;

        while (*joinPoint) {
            Node<T> *a = *joinPoint;
            Node<T> *a_end = findEndOfSortedString(a, cmp);

            if (!a_end->next) {
                if (joinPoint == &this->head) {
                    last = a_end;
                    return;
                } else {
                    break;
                }
            }

            Node<T> *b = a_end->next;
            Node<T> *b_end = findEndOfSortedString(b, cmp);

            Node<T> *tail = b_end->next;

            a_end->next = NULL;
            b_end->next = NULL;

            while (a && b) {
                if (cmp(a->data, b->data) <= 0) {
                    *joinPoint = a;
                    joinPoint = &a->next;
                    a = a->next;
                } else {
                    *joinPoint = b;
                    joinPoint = &b->next;
                    b = b->next;
                }
            }

            if (a) {
                *joinPoint = a;
                while (a->next) a = a->next;
                a->next = tail;
                joinPoint = &a->next;
            } else {
                *joinPoint = b;
                while (b->next) b = b->next;
                b->next = tail;
                joinPoint = &b->next;
            }
        }
    }
}

template <typename T>
Node<T> *LinkedList<T>::findEndOfSortedString(Node<T> *p, int (*cmp)(T &, T &)) {
    while (p->next && cmp(p->data, p->next->data) <= 0) {
        p = p->next;
    }

    return p;
}

#endif
