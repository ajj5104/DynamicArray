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
	int m_size;

public:
	LinkedList() : p_head(nullptr), p_tail(nullptr), p_current(nullptr), m_size(0) {}

	LinkedList(const LinkedList&) = delete;

	LinkedList& operator=(const LinkedList&) = delete;
	
	Node<T>* CreateNode(const T& val) {
		Node<T>* np = new Node<T>(val);
		return np;
	}
	
	void AddNodeAtHead(const T& val) {
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

		m_size++;
	}
	
	void Clear() {
		Node<T>* ptr_next;
		p_current = p_head;
		while (p_current != nullptr) {
			ptr_next = p_current->next;
			delete(p_current);
			p_current = ptr_next;
		}

		p_head = nullptr;
		if (p_tail != nullptr) p_tail = nullptr;
		if (p_current != nullptr) p_current = nullptr;

		m_size = 0;
	}
	
	void AddNodeAfterCurrent(const T& val) {
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
			np->next = nullptr;
			p_current = np;
			m_size++;
		}
	}
	
	void PushBack(const T& val) {
		Node<T>* np = CreateNode(val);
		if (p_head == nullptr) {
			p_head = np;
			p_tail = np;
		}
		else {
			p_tail->next = np;
			np->prev = p_tail;
			np->next = nullptr;
			p_tail = np;
		}

		m_size++;
	}

	T PopFront() {
		Node<T>* oldHead = p_head;
		T val = oldHead->data;

		p_head = p_head->next;

		if (p_head != nullptr) {
			p_head->prev = nullptr;
		}
		else {
			p_tail = nullptr;
		}

		delete oldHead;
		m_size--;

		return val;
	}

	Node<T>* Head() {
		return p_head;
	}

	int Size() const { return m_size; }

	bool IsEmpty() const { return m_size == 0; }
	
	~LinkedList() {
		Clear();
	}
};