#ifndef STRUCTURE_H
#define STRUCTURE_H

template <class T>
class linked_list {
    private:
        struct node {
            T data;
            node* next;
            node() : next(nullptr) {}
            node(T value) : data(value), next(nullptr) {}
        };
        unsigned int size;
        node* head;
    public:
        linked_list() : size(0), head(nullptr) {}
        ~linked_list();
        void insert_head(T data);
        T delete_head();
        unsigned int length(); 
        bool is_empty();
        void print();
};

template <class T>
linked_list<T>::~linked_list() {
    while (this->head) {
        this->delete_head();
    }
}

template <class T>
void linked_list<T>::insert_head(T data) {
    node* new_node = new node(data);
    new_node->next = this->head;
    this->head = new_node;
    this->size++;
}

template <class T>
T linked_list<T>::delete_head()  {
    T value;
    if (this->head) {
        node* test = this->head;
        value = test->data;
        this->head = this->head->next;
        delete test;
        this->size--;
    }
    return value;
}

template <class T>
unsigned int linked_list<T>::length() {
    return this->size;
}

template <class T>
bool linked_list<T>::is_empty() {
    return this->head ? false : true;
}

template <class T>
void linked_list<T>::print() {
    node* traverse = this->head;
    while (traverse) {
        std::cout << traverse->data << std::endl;
        traverse = traverse->next;
    }
}

#endif