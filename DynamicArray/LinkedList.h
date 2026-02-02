#pragma once

template <typename T>
struct Node {
	T data;
	Node* next;
	Node* prev;

	Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedList
{
private:
	Node<T>* p_head;
	Node<T>* p_tail;
	Node<T>* p_current;

public:
	LinkedList() : p_head(nullptr), p_tail(nullptr), p_current(nullptr) {}
	
	void SetTestList() {
		Node<T>* a(1);
		Node<T>* b(2);
		Node<T>* c(3);

		p_head = &a;
		p_current = p_head;
		a.next = &b;
		b.prev = &a;
		b.next = &c;
		c.prev = &b;
		p_tail = &c;
	}
	
	Node<T>* CreateNode(T* val) {
		Node<T>* np = new Node<T>(val);
		return np;
	}
	
	void AddNodeAtHead(T* val) {
		Node<T>* newNode = CreateNode(val);
		
		if (p_head == nullptr) {
			p_head = newNode;
			p_tail = newNode;
			p_current = newNode;
		} else {
			newNode->next = p_head;
			newNode->prev = nullptr;

			p_head = newNode;
			p_head->next->prev = newNode;
			p_current = newNode;
		}
	}
	
	void ClearList() {
		if (this == nullptr) return;

		Node<T>* ptr_next;
		p_current = p_head;
		while (p_current != nullptr) {
			ptr_next = p_current->next;
			delete(p_current->data);
			delete(p_current);
			p_current = ptr_next;
		}

		p_head = nullptr;
		if (p_tail != nullptr) p_tail = nullptr;
		if (p_current != nullptr) p_current = nullptr;
	}
	
	int AddNodeAfterCurrent(T* val) {
		if (p_current == nullptr) return AddNodeAtHead(val);
		else {
			Node<T>* np = CreateNode(val);

			if (p_current->next == nullptr) p_tail = np;
			else {
				np->next = p_current->next;
				p_current->next->prev = np;
			}

			p_current->next = np;
			np->prev = p_current;
			p_current = np;
		}
	}
	
	int FindValue(T* val);
	
	~LinkedList() {
		p_current = p_head;
		while (p_current != nullptr) {
			Node<T>* next = p_current->next;
			delete p_current;
			p_current = next;
		}
	}
};