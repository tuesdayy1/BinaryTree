#pragma once
#include <iostream>

template<class T>
class Stack {
private:
    struct Node {
        T value_;
        Node* prev_;
        Node(T value, Node* prev = nullptr) : value_(value), prev_(prev) {}
    };
    Node* top_;

public:
    Stack() : top_(nullptr) {}

    void push(T value) {
        top_ = new Node(value, top_);
    }

    T pop() {
        T value = top_->value_;
        Node* del = top_;
        top_ = top_->prev_;
        delete del;
        return value;
    }

    bool isEmpty() {
        return top_ == nullptr;
    }

    ~Stack() {
        while (top_) {
            Node* del = top_;
            top_ = top_->prev_;
            delete del;
        }
    }
};