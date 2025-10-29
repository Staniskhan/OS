#include <iostream> 
using namespace std;

// ------------------------------------------------------------------------------
//                              CLASS DECLARATION
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

template <class T>
class myList {
public:
	struct Node
	{
		T info;
		Node* ssylka;
	};
	Node* head = NULL;
public:
	bool isEmpty();
	void pushHead(T);
	void pushTail(T);
	void changeElement(Node*, T);
	Node* findValueByData(T);
	T findValueByPtr(Node*);
	void deleteElement(T);
	void showList();
	void showLikeString();
	T getFirst();
	T getLast();
	static void reverseList(myList<T>&);
};

// ------------------------------------------------------------------------------
//                      INITIALIZATION OF METHODS OF CLASS
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

template <typename T>
bool myList<T>::isEmpty() {
	if (head == NULL) return 1;
	return 0;
}

template<typename T>
void myList<T>::pushHead(T data) {
	Node* newhead = new Node;
	newhead->info = data;
	if (head != NULL) {
		newhead->ssylka = head;
		head = newhead;
	}
	else {
		newhead->ssylka = NULL;
		head = newhead;
	}
}

template <typename T>
void myList<T>::pushTail(T data) {
	Node* next = new Node;
	if (head == NULL) {
		head = new Node();
		head->ssylka = NULL;
		head->info = data;
	}
	else {
		Node* next = head;
		while (next->ssylka != NULL) {
			next = next->ssylka;
		}
		next->ssylka = new Node;
		next->ssylka->ssylka = NULL;
		next->ssylka->info = data;
	}
}


template <typename T>
void myList<T>::changeElement(Node* curr, T data) {
	curr->info = data;
}


template <typename T>
typename myList<T>::Node* myList<T>::findValueByData(T data) {
	Node* curr = head;
	while (curr != NULL) {
		if (curr->info == data) return curr;
		curr = curr->ssylka;
	}
	return NULL;
}


template <typename T>
T myList<T>::findValueByPtr(Node* curr) {
	if (curr == NULL) return 0;
	return curr->info;
}


template <typename T>
void myList<T>::deleteElement(T data) {
	Node* curr = findValueByData(data);
	Node* save = head;
	if (curr == head) {
		save = save->ssylka;
		delete head;
		head = save;
	}
	else {
		while (save->ssylka != curr) {
			save = save->ssylka;
		}
		save->ssylka = curr->ssylka;
		delete curr;
	}

}


template <typename T>
void myList<T>::showList() {
	Node* curr = head;
	if (head == NULL) cout << "THE LIST IS EMPTY" << endl;
	else {
		cout << endl << "(";
		cout << curr->info;
		while (curr->ssylka != NULL) {
			curr = curr->ssylka;
			cout << ", " << curr->info;
		}
		cout << ")";
		cout << endl;
	}
}


template <typename T>
void myList<T>::showLikeString() {
	Node* curr;
	curr = head;
	if (head == NULL) cout << "THE LIST IS EMPTY" << endl;
	else {
		cout << curr->info;
		while (curr->ssylka != NULL) {
			curr = curr->ssylka;
			cout << curr->info;
		}
	}

}

template <typename T>
T myList<T>::getFirst() {
	if (head != NULL) return head->info;
}


template <typename T>
T myList<T>::getLast() {
	if (head != NULL) {
		Node* curr = head;
		while (curr->ssylka != NULL) {
			curr = curr->ssylka;
		}
		return curr->info;
	}
}


template <typename T>
static void myList<T>::reverseList(myList<T>& list)
{
	head->ssylka
	if (head->ssylka)
	{
		
	}
}

//========================================================================

template <typename T>
myList<T> reverseList(myList<T>)
{
	if (head->ssylka)
}