#pragma once

template <typename T>
struct Node {
	T data;	// the value being stored in a node
	Node* next;	// a pointer to the next node in the list
	Node* prev;	// a pointer to the previous node in the list

	Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedList
{
private:
	Node<T>* p_head;	// a pointer to the first node in the linked list
	Node<T>* p_tail;	// a pointer to the last node in the linked list
	Node<T>* p_current;	// a pointer to the most recently accessed node in the linked list
	int m_size;	// the size of the linked list

public:
	LinkedList() : p_head(nullptr), p_tail(nullptr), p_current(nullptr), m_size(0) {}

	LinkedList(const LinkedList&) = delete;

	LinkedList& operator=(const LinkedList&) = delete;
	
	/// <summary>
	/// Helper function to create a new node in the linked list
	/// </summary>
	/// <param name="val">The value to be stored in the new node</param>
	/// <returns>A newly created node</returns>
	Node<T>* CreateNode(const T& val) {
		Node<T>* np = new Node<T>(val);
		return np;
	}
	
	/// <summary>
	/// Adds a node to the head of the linked list
	/// </summary>
	/// <param name="val">The value to be stored in the new node</param>
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
	
	/// <summary>
	/// Frees the memory of all the nodes in the linked list
	/// </summary>
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
	
	/// <summary>
	/// Adds a node after whatever the most recently accessed node was
	/// </summary>
	/// <param name="val">The value to be stored in the new node</param>
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
	
	/// <summary>
	/// Adds a new node to the end of the linked list
	/// </summary>
	/// <param name="val">The value to be stored in the new node</param>
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

	/// <summary>
	/// Removes the value at the head of the linked list and returns its value
	/// </summary>
	/// <returns>The value stored by the removed node</returns>
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

	/// <summary>
	/// Helper function to get the head node of the linked list
	/// </summary>
	/// <returns>p_head node</returns>
	Node<T>* Head() {
		return p_head;
	}

	/// <summary>
	/// Allows you to get the number of elements in the linked list
	/// </summary>
	/// <returns>The size of the linked list</returns>
	int Size() const { return m_size; }

	/// <summary>
	/// Checks if the list is empty
	/// </summary>
	/// <returns>True/False</returns>
	bool IsEmpty() const { return m_size == 0; }
	
	/// <summary>
	/// Class destructor
	/// </summary>
	~LinkedList() {
		Clear();
	}
};