#pragma once
#include <iostream>
#include "Queue.h"
#include "QueueExceptions.h"

template<class T>
class QueueList : Queue<T> {
private:
	struct Node {
		T value_;
		Node* next_;
		Node(T value, Node* next = nullptr) : value_(value), next_(next) {}
	};
	Node* head_;
	Node* tail_;
	int length_;
public:
	QueueList() : head_(nullptr), tail_(nullptr), length_(0) {}

	void enQueue(const T& e) override {
		Node* new_node = new Node(e);
		if (isEmpty()) {
			head_ = new_node;
			tail_ = head_;
		}
		else {
			tail_->next_ = new_node;
			tail_ = tail_->next_;
		}
		length_++;
	}

	T deQueue() override {
		if (isEmpty())
			throw QueueUnderFlow();
		Node* node = head_;
		T out = head_->value_;
		head_ = head_->next_;
		length_--;
		delete node;
		return out;
	}

	bool isEmpty() override {
		return length_ == 0;
	}

	void print() {
		Node* node = head_;
		while (node) {
			std::cout << node->value_ << ' ';
			node = node->next_;
		}
		std::cout << '\n';
	}

	~QueueList() {
		if (!isEmpty()) {
			Node* node = head_;
			Node* next;
			while (!isEmpty()) {
				next = node->next_;
				delete node;
				length_--;
				node = next;
			}
		}
	}
};