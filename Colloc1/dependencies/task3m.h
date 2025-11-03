#include <iostream> 
#include <initializer_list>
using namespace std;

// ------------------------------------------------------------------------------
//                              CLASS DECLARATION
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

template <class T>
class myList {
private:
	struct Node
	{
		T info;
		Node* ssylka;
	};
	Node* head = NULL;
public:
	myList();
	myList(initializer_list<T>);
	bool isEmpty();
	void pushHead(T);
	void pushTail(T);
	void changeElement(T, T);
	//T findDataByAdress(Node*);
	void deleteElement(T);
	void showList();
	void showLikeString();
	T getFirst();
	T getLast();
	void clear();
	void reverse();
private:
	void reverseList(Node*);
	//Node* findAdressByData(T);
};

// ------------------------------------------------------------------------------
//                      INITIALIZATION OF METHODS OF CLASS
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

template <typename T>
myList<T>::myList() {};


template <typename T>
myList<T>::myList(initializer_list<T> list)
{
	for (T val : list)
	{
		pushTail(val);
	}

}


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
void myList<T>::changeElement(T data1, T data2) {
	Node* curr = head;
	while (curr != NULL) {
		if (curr->info == data1) curr->info = data2;
		curr = curr->ssylka;
	}
}


//template <typename T>
//typename myList<T>::Node* myList<T>::findAdressByData(T data) {
//	Node* curr = head;
//	while (curr != NULL) {
//		if (curr->info == data) return curr;
//		curr = curr->ssylka;
//	}
//	return NULL;
//}


//template <typename T>
//T myList<T>::findDataByAdress(Node* curr) {
//	if (curr == NULL) return 0;
//	return curr->info;
//}


template <typename T>
void myList<T>::deleteElement(T data) {
	//Node* curr = findAdressByData(data);
	//Node* save = head;
	//if (curr == head) {
	//	save = save->ssylka;
	//	delete head;
	//	head = save;
	//}
	//else {
	//	while (save->ssylka != curr) {
	//		save = save->ssylka;
	//	}
	//	save->ssylka = curr->ssylka;
	//	delete curr;
	//}
	if (head != NULL)
	{
		if (head->ssylka == NULL)
		{
			if (head->info == data)
			{
				delete[] head;
			}
		}
		else
		{
			Node* curr = head;
			while (curr->ssylka != NULL)
			{
				if (curr->ssylka->info == data)
				{
					Node* save = curr->ssylka;
					curr->ssylka = curr->ssylka->ssylka;
					delete[] save;
				}
				else
				{
					curr = curr->ssylka;
				}
			}
		}
	}
	
}


//template <typename T>
//void myList<T>::deleteElement(Node* element)
//{
//	if (element->ssylka == NULL)
//	{
//		delete[] element;
//	}
//	else if (element == head)
//	{S
//		head = head->ssylka;
//		delete[] element;
//	}
//	else
//	{
//		Node* save = element->ssylka;
//		element->info = element->ssylka->info;
//		element->ssylka = element->ssylka->ssylka;
//		delete[] save;
//	}
//}


template <typename T>
void myList<T>::showList() {
	Node* curr = head;
	if (head == NULL) cout << "THE LIST IS EMPTY!";
	else {
		cout << "{";
		cout << curr->info;
		while (curr->ssylka != NULL) {
			curr = curr->ssylka;
			cout << ", " << curr->info;
		}
		cout << "}";
	}
}


template <typename T>
void myList<T>::showLikeString() {
	Node* curr;
	curr = head;
	if (head == NULL) cout << "THE LIST IS EMPTY!";
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
void myList<T>::reverseList(Node* el)
{
	if (el->ssylka->ssylka == NULL)
	{
		head = el->ssylka;
		el->ssylka->ssylka = el;
	}
	else
	{
		reverseList(el->ssylka);
		el->ssylka->ssylka = el;
	}
}


template <typename T>
void myList<T>::clear()
{
	if (head != NULL)
	{
		Node* save;
		while (head != NULL)
		{
			save = head->ssylka;
			delete[] head;
			head = save;
		}
	}
}


template <typename T>
void myList<T>::reverse()
{
	if (head != NULL && head->ssylka != NULL)
	{
		Node* save = head;
		reverseList(head);
		save->ssylka = NULL;
	}
}