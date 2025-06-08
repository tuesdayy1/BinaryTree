#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H
#include "Stack.h"
#include "QueueList.h"

template <class T>
class BinarySearchTree {
private:
    struct Node {
        T key_;
        Node* left_;
        Node* right_;
        Node* p_;
        Node(T key, Node* left=nullptr, Node* right=nullptr, Node* p=nullptr) :
            key_(key), left_(left), right_(right), p_(p) {}
    };
    Node* root_;

    void clear(Node* node) {
        if (!node) return;
        clear(node->left_);
        clear(node->right_);
        delete node;
    }

    void print(Node* node) {
        if (!node) return;
        std::cout << node->key_;
        if (node->left_ || node->right_) {
            std::cout << "(";
            if (node->left_) print(node->left_);
            std::cout << ", ";
            if (node->right_) print(node->right_);
            std::cout << ')';
        }
    }

    int getNumberOfNodes(Node* node) {
        if (!node) return 0;
        return 1 + getNumberOfNodes(node->left_) + getNumberOfNodes(node->right_);
    }

    int getHeight(Node* node) {
        if (!node) return 0;
        int leftHeight = getHeight(node->left_);
        int rightHeight = getHeight(node->right_);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    void inorderWalk(Node* node) {
        if (!node) return;

        inorderWalk(node->left_);
        std::cout << node->key_ << ' ';
        inorderWalk(node->right_);
    }

public:
    BinarySearchTree() : root_(nullptr) {}

    BinarySearchTree(BinarySearchTree& other) = delete;

    BinarySearchTree& operator=(BinarySearchTree& other) = delete;

    BinarySearchTree(BinarySearchTree&& other) noexcept : root_(other.root_) {
        other.root_ = nullptr;
    }

    BinarySearchTree& operator=(BinarySearchTree&& other) {
        if (this != &other) {
            clear();
            root_ = other.root_;
            other.root_ = nullptr;
        }
        return *this;
    }

    ~BinarySearchTree() {
        clear(root_);
    }
    
    void clear() {
        clear(root_);
        root_ = nullptr;
    }

    bool searchIterative(const T& key) {
        if (!root_) return 0;
        Stack<Node*> s;
        s.push(root_);

        while (!s.isEmpty()) {
            Node* curr = s.pop();

            if (curr->key_ == key) return 1;

            if (curr->left_) s.push(curr->left_);
            if (curr->right_) s.push(curr->right_);
        }

        return 0;
    }

    bool insert(const T& key) {
        if (!root_) {
            root_ = new Node(key);
            return 1;
        }
        Node* node = root_;
        Node* prev = nullptr;
        while (node) {
            if (key > node->key_) {
                prev = node;
                node = node->right_;
            }
            else if (key < node->key_) {
                prev = node;
                node = node->left_;
            }
            else {
                return 0;
            }
        }
        if (key > prev->key_) {
            prev->right_ = new Node(key);
            prev->right_->p_ = prev;
        }
        else {
            prev->left_ = new Node(key);
            prev->left_->p_ = prev;
        }
        return 1;
    }

    void print() {
        print(root_);
        std::cout << '\n';
    }

    bool remove(const T& key) {
        if (!root_) return 0;
        Node* node = root_;
        while (node && node->key_ != key) {
            if (key > node->key_)
                node = node->right_;
            else if (key < node->key_)
                node = node->left_;
        }
        if (!node) return 0;
        if (!node->left_ && !node->right_) {
            if (root_->key_ == key) {
                delete root_;
                root_ = nullptr;
            }
            else {
                Node* parent = node->p_;
                if (parent->left_ == node) {
                    parent->left_ = nullptr;
                }
                else {
                    parent->right_ = nullptr;
                }
                delete node;
            }
        }
        else if (node->left_ && node->right_) {
            Node* min = node->right_;
            while (min->left_)
                min = min->left_;
            if (min->right_) {
                if (min->p_->left_ == min)
                    min->p_->left_ = min->right_;
                else
                    min->p_->right_ = min->right_;
                min->right_->p_ = min->p_;
            }
            else {
                if (min->p_->left_ == min)
                    min->p_->left_ = nullptr;
                else
                    min->p_->right_ = nullptr;
            }
            node->key_ = min->key_;
            delete min;
        }
        else {
            if (root_->key_ == key) {
                Node* child = (root_->left_ ? root_->left_ : root_->right_);
                root_ = child;
                root_->p_ = nullptr;
                delete node;
            }
            else {
                Node* child = (node->left_ ? node->left_ : node->right_);
                Node* parent = node->p_;
                if (parent->left_ == node) {
                    parent->left_ = child;
                }
                else {
                    parent->right_ = child;
                }
                child->p_ = parent;
                delete node;
            }
        }
        return 0;
    }

    int getNumberOfNodes() {
        return getNumberOfNodes(root_);
    }

    int getHeight() {
        return getHeight(root_);
    }

    void inorderWalkIterative() {
        Stack<Node*> s;
        Node* node = root_;
        while (node || !s.isEmpty()) {
            while (node) {
                s.push(node);
                node = node->left_;
            }
            node = s.pop();
            std::cout << node->key_ << ' ';
            node = node->right_;
        }
        std::cout << '\n';
    }

    void inorderWalk() {
        inorderWalk(root_);
        std::cout << '\n';
    }

    void walkByLevels() {
        if (!root_) return;
        QueueList<Node*> q;
        q.enQueue(root_);
        while (!q.isEmpty()) {
            Node* curr = q.deQueue();
            std::cout << curr->key_ << ' ';
            if (curr->left_) q.enQueue(curr->left_);
            if (curr->right_) q.enQueue(curr->right_);
        }
        std::cout << '\n';
    }

    bool isSimilar(const BinarySearchTree& other) {
        Stack<Node*> s, s_other;
        Node* node1 = root_;
        Node* node2 = other.root_;
        while ((node1 || !s.isEmpty()) && (node2 || !s_other.isEmpty())) {
            while (node1) {
                s.push(node1);
                node1 = node1->left_;
            }
            while (node2) {
                s_other.push(node2);
                node2 = node2->left_;
            }
            node1 = s.pop();
            node2 = s_other.pop();
            if (node1->key_ != node2->key_) return 0;
            node1 = node1->right_;
            node2 = node2->right_;
        }

        return (node1 == nullptr && s.isEmpty() && node2 == nullptr && s_other.isEmpty());
    }
};
#endif