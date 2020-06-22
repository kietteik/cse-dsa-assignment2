// #include "dbLib.h"
#include "main.h"
#include <queue>

//-----------------------utilities-------------------------
void printNSpace(int n);
void printInt(int &data);
void printInteger(int &n);

//-----------------------utilities-------------------------

//--------------------LINKED LIST_-----------------------

template <class T>
struct Link
{
	T data;
	Link<T> *next;
	Link() : next(NULL) {}
	Link(T &a) : data(a), next(NULL) {}
};

template <class T>
class LList
{
public:
	Link<T> *head; // The head pointer of linked list
	size_t _size;  // number of elements in this list
	LList() : head(NULL), _size(0) {}
	~LList()
	{
		this->clean();
	}
	bool isEmpty()
	{
		return head == NULL;
	}
	size_t getSize()
	{
		return _size;
	}
	T &at(int i);
	T &operator[](int i);
	bool find(T &a, int &idx);
	int insert(int i, T &a);
	int remove(int i);
	int append(T &a);
	int prepend(T &a);
	int removeHead();
	int removeTail();
	void reverse();
	void traverse(void (*op)(T &));
	void clean();
	void printAll();
};

template <class T>
T &LList<T>::at(int i)
{
	if (i < 0 || i >= _size)
	{
		throw "Index_out_of_bounds!";
	}
	else
	{
		Link<T> *temp = this->head;
		for (int index = 0; index < i; i++)
		{
			temp = temp->next;
		}
		return temp->data;
	}
}

template <class T>
T &LList<T>::operator[](int i)
{
	if (i < 0 || i >= _size)
	{
		throw "Index_out_of_bounds!";
	}
	else
	{
		Link<T> *temp = this->head;
		for (int index = 0; index < i; i++)
		{
			temp = temp->next;
		}
		return temp->data;
	}
}

template <class T>
int LList<T>::append(T &a)
{
	Link<T> *pNew = new Link<T>(a);
	if (pNew == nullptr)
	{
		return -1;
	}
	else
	{
		Link<T> *temp = this->head;
		if (temp == nullptr)
		{
			pNew->next = this->head;
			this->head = pNew;
			this->_size++;
			return 0;
		}
		else
		{
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			pNew->next = temp->next;
			temp->next = pNew;
		}
		this->_size++;
		return 0;
	}
}

template <class T>
int LList<T>::prepend(T &a)
{
	Link<T> *pNew = new Link<T>(a);
	if (pNew == nullptr)
	{
		return -1;
	}
	else
	{
		pNew->next = this->head;
		this->head = pNew;
		this->_size++;
		return 0;
	}
}

template <class T>
int LList<T>::removeHead()
{
	if (this->head == nullptr)
	{
		return -1;
	}
	else
	{
		Link<T> *temp = this->head;
		this->head = temp->next;
		temp->next = nullptr;
		delete temp;
		this->_size--;
		return 0;
	}
}

template <class T>
int LList<T>::removeTail()
{
	if (this->head == nullptr)
	{
		return -1;
	}
	else
	{
		Link<T> *previous = nullptr;
		Link<T> *temp = this->head;
		if (temp->next == nullptr)
		{
			this->head = temp->next;
			delete temp;
			this->_size--;
			return 0;
		}
		while (temp->next != nullptr)
		{
			previous = temp;
			temp = temp->next;
		}
		delete temp;
		previous->next = nullptr;
		this->_size--;
		return 0;
	}
}

template <class T>
int LList<T>::insert(int i, T &a)
{
	if (i < 0 || (i > this->_size))
	{
		return -1;
	}
	if (i == 0)
	{
		return this->prepend(a);
	}
	else if (i == this->_size)
	{
		return this->append(a);
	}
	else
	{
		Link<T> *temp = this->head;
		Link<T> *newNode = new Link<T>(a);
		for (int index = 0; index < i - 1; index++)
		{
			temp = temp->next;
		}
		Link<T> *storage = temp->next;
		temp->next = newNode;
		newNode->next = storage;
		this->_size++;
		return 0;
	}
}

template <class T>
int LList<T>::remove(int i)
{
	if (this->isEmpty() == true || i < 0 || i >= this->_size)
	{
		return -1;
	}
	if (i == 0)
	{
		return this->removeHead();
	}
	else if (i == this->_size)
	{
		return this->removeTail();
	}
	Link<T> *previous = nullptr;
	Link<T> *temp = this->head;
	for (int index = 0; index < i; index++)
	{
		previous = temp;
		temp = temp->next;
	}
	previous->next = temp->next;
	temp->next = nullptr;
	delete temp;
	this->_size--;
	return 0;
}

template <class T>
void LList<T>::clean()
{
	while (this->head != nullptr)
	{
		this->removeHead();
	}
}

template <class T>
void LList<T>::reverse()
{
	if (this->isEmpty() == true)
	{
		return;
	}
	Link<T> *current = this->head;
	Link<T> *prev = nullptr;
	Link<T> *next = current->next;
	while (current != nullptr)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	this->head = prev;
	return;
}

template <class T>
bool LList<T>::find(T &a, int &idx)
{
	if (this->isEmpty() == true)
	{
		idx = -1;
		return false;
	}
	else
	{
		idx = 0;
		Link<T> *temp = this->head;
		while (temp != nullptr)
		{

			if (temp->data == a)
			{
				return true;
			}
			temp = temp->next;
			idx++;
		}
		idx = -1;
		return false;
	}
}

template <class T>
void LList<T>::traverse(void (*op)(T &))
{
	Link<T> *pTemp = this->head;
	while (pTemp != NULL)
	{
		op(pTemp->data);
		pTemp = pTemp->next;
	}
}

template <class T>
void LList<T>::printAll()
{
	Link<T> *pTemp = this->head;
	while (pTemp != NULL)
	{
		cout << pTemp->data << " ";
		pTemp = pTemp->next;
	}
}

//--------------------LINKED LIST------------------------

//--------------------__AVL TREE__-----------------------
enum BalanceValue
{
	LH = -1,
	EH = 0,
	RH = 1
};

template <class T>
class Node
{
public:
	T data;
	Node<T> *left;
	Node<T> *right;
	BalanceValue balance;

	Node(const T &val)
	{
		data = val;
		left = right = NULL;
		balance = EH;
	}
};

template <class T>
class AVL
{

public:
	Node<T> *root;

	void clearRec(Node<T> *&);
	int getHeightRec(Node<T> *);
	Node<T> *rotateRight(Node<T> *&node);
	Node<T> *rotateLeft(Node<T> *&node);
	Node<T> *leftBalance(Node<T> *&node, bool &taller);
	Node<T> *rightBalance(Node<T> *&node, bool &taller);
	Node<T> *removeLeftBalance(Node<T> *&node, bool &shorter);
	Node<T> *removeRightBalance(Node<T> *&node, bool &shorter);
	//TODO Methods
	Node<T> *insertRec(Node<T> *&node, T &value, bool &taller);
	Node<T> *removeRec(Node<T> *&node, T &value, bool &shorter, bool &success);
	Node<T> *removeInRangeRec(Node<T> *&node, T &value1, T &value2, bool &shorter, bool &success);

	bool checkTimeRangeTravRec(Node<T> *&node, T &value1, T &value2);
	bool checkTimeRangeTrav(T &value1, T &value2);
	Node<T> *findNearestTimeRec(Node<T> *&node, T &value);
	Node<T> *findNearestTime(T &value);
	Node<T> *minNode(Node<T> *&node);

	AVL()
	{
		this->root = NULL;
	}
	~AVL()
	{
		this->clear();
	}

	void clear();
	int getHeight();
	void printTreeStructure();
	// TODO Methods
	void insert(T &value);
	void remove(T &value);
	void removeInRange(T &value1, T &value2);
};

template <class T>
Node<T> *AVL<T>::rotateRight(Node<T> *&node)
{
	// TODO
	Node<T> *temp;
	temp = node->left;
	node->left = temp->right;
	temp->right = node;
	return temp;
}

template <class T>
Node<T> *AVL<T>::rotateLeft(Node<T> *&node)
{
	// TODO
	Node<T> *temp;
	temp = node->right;
	node->right = temp->left;
	temp->left = node;
	return temp;
}

template <class T>
Node<T> *AVL<T>::insertRec(Node<T> *&node, T &value, bool &taller)
{
	// TODO
	if (node == NULL)
	{
		node = new Node<T>(value);
		taller = true;
		return node;
	}
	if (value < node->data)
	{
		node->left = insertRec(node->left, value, taller);
		if (taller)
		{
			if (node->balance == LH)
			{
				node = leftBalance(node, taller);
				taller = false;
			}
			else if (node->balance == EH)
			{
				node->balance = LH;
			}
			else
			{
				node->balance = EH;
				taller = false;
			}
		}
	}
	else if (value.time == node->data.time)
	{
		node->data.BP = value.BP;
		node->data.AP = value.AP;
		taller = false;
		return node;
	}
	else
	{
		node->right = insertRec(node->right, value, taller);
		if (taller)
		{
			if (node->balance == LH)
			{
				node->balance = EH;
				taller = false;
			}
			else if (node->balance == EH)
			{
				node->balance = RH;
			}
			else
			{
				node = rightBalance(node, taller);
				taller = false;
			}
		}
	}
	return node;
}

template <class T>
void AVL<T>::insert(T &value)
{
	// TODO
	bool taller = false;
	insertRec(this->root, value, taller);
}

template <class T>
Node<T> *AVL<T>::rightBalance(Node<T> *&node, bool &taller)
{
	// TODO
	Node<T> *rightTree = node->right;
	if (rightTree->balance == RH)
	{
		rightTree->balance = EH;
		node->balance = EH;
		node = rotateLeft(node);
		// node->left->balance = EH; // rightTree->balance = EH;
	}
	else
	{
		Node<T> *leftTree = rightTree->left;
		if (leftTree->balance == RH)
		{
			node->balance = LH;
			rightTree->balance = EH;
		}
		else if (leftTree->balance == EH)
		{
			node->balance = EH;
			rightTree->balance = EH;
		}
		else
		{
			node->balance = EH;
			rightTree->balance = RH;
		}
		leftTree->balance = EH;
		node->right = rotateRight(rightTree);
		node = rotateLeft(node);
	}
	return node;
}

template <class T>
Node<T> *AVL<T>::leftBalance(Node<T> *&node, bool &taller)
{
	// TODO
	Node<T> *leftTree;
	leftTree = node->left;
	if (leftTree->balance == LH)
	{
		leftTree->balance = EH;
		node->balance = EH;
		node = rotateRight(node);
		// node->right->balance = EH; //fix (leftTree->balance = EH)
	}
	else
	{
		Node<T> *rightTree = leftTree->right;
		if (rightTree->balance == LH)
		{
			node->balance = RH;
			leftTree->balance = EH;
		}
		else if (rightTree->balance == EH)
		{
			node->balance = EH;
			leftTree->balance = EH;
		}
		else
		{
			node->balance = EH;
			leftTree->balance = LH;
		}
		rightTree->balance = EH;
		node->left = rotateLeft(leftTree);
		node = rotateRight(node);
	}
	return node;
}

template <class T>
Node<T> *AVL<T>::removeRec(Node<T> *&node, T &value, bool &shorter, bool &success)
{
	// TODO
	if (node == NULL)
	{
		shorter = false;
		success = false;
		return NULL;
	}
	if (value < node->data)
	{
		node->left = removeRec(node->left, value, shorter, success);
		if (shorter)
		{
			node = removeRightBalance(node, shorter);
		}
	}
	else if (value > node->data)
	{
		node->right = removeRec(node->right, value, shorter, success);
		if (shorter)
		{
			node = removeLeftBalance(node, shorter);
		}
	}
	else
	{
		Node<T> *deleteNode = node;
		if (node->right == NULL)
		{
			Node<T> *newNode = node->left;
			success = true;
			shorter = true;
			if (this->root == deleteNode)
			{
				this->root = newNode;
			}
			delete deleteNode;
			return newNode;
		}
		else if (node->left == NULL)
		{
			Node<T> *newNode = node->right;
			success = true;
			shorter = true;
			if (this->root == deleteNode)
			{
				this->root = newNode;
			}
			delete deleteNode;
			return newNode;
		}
		else
		{
			Node<T> *exchPtr = node->left;
			while (exchPtr->right != NULL)
			{
				exchPtr = exchPtr->right;
			}
			node->data = exchPtr->data;
			node->left = removeRec(node->left, exchPtr->data, shorter, success);
			if (shorter)
			{
				node = removeRightBalance(node, shorter);
			}
		}
	}
	return node;
}

template <class T>
void AVL<T>::remove(T &value)
{
	// TODO
	bool shorter = false;
	bool success = false;
	removeRec(this->root, value, shorter, success);
}

template <class T>
Node<T> *AVL<T>::removeInRangeRec(Node<T> *&node, T &value1, T &value2, bool &shorter, bool &success)
{
	// TODO
	if (node == NULL)
	{
		shorter = false;
		success = false;
		return NULL;
	}
	if (value2 < node->data)
	{
		node->left = removeInRangeRec(node->left, value1, value2, shorter, success);
		if (shorter)
		{
			node = removeRightBalance(node, shorter);
		}
	}
	else if (value1 > node->data)
	{
		node->right = removeInRangeRec(node->right, value1, value2, shorter, success);
		if (shorter)
		{
			node = removeLeftBalance(node, shorter);
		}
	}
	else
	{
		Node<T> *deleteNode = node;
		if (node->right == NULL)
		{
			Node<T> *newNode = node->left;
			success = true;
			shorter = true;
			if (this->root == deleteNode)
			{
				this->root = newNode;
			}
			delete deleteNode;
			return newNode;
		}
		else if (node->left == NULL)
		{
			Node<T> *newNode = node->right;
			success = true;
			shorter = true;
			if (this->root == deleteNode)
			{
				this->root = newNode;
			}
			delete deleteNode;
			return newNode;
		}
		else
		{
			Node<T> *exchPtr = node->left;
			while (exchPtr->right != NULL)
			{
				exchPtr = exchPtr->right;
			}
			node->data = exchPtr->data;
			node->left = removeRec(node->left, exchPtr->data, shorter, success);
			if (shorter)
			{
				node = removeRightBalance(node, shorter);
			}
		}
	}
	return node;
}

template <class T>
void AVL<T>::removeInRange(T &value1, T &value2)
{
	// TODO
	bool shorter = false;
	bool success = false;
	removeInRangeRec(this->root, value1, value2, shorter, success);
}

template <class T>
Node<T> *AVL<T>::removeRightBalance(Node<T> *&node, bool &shorter)
{
	// TODO
	if (node->balance == LH)
	{
		node->balance = EH;
	}
	else if (node->balance == EH)
	{
		node->balance = RH;
		shorter = false;
	}
	else
	{
		Node<T> *rightTree = node->right;
		if (rightTree->balance == LH)
		{
			Node<T> *leftTree = rightTree->left;
			if (leftTree->balance == LH)
			{
				rightTree->balance = RH;
				node->balance = EH;
			}
			else if (leftTree->balance == EH)
			{
				node->balance = EH;
				rightTree->balance = EH;
			}
			else
			{
				node->balance = LH;
				rightTree->balance = EH;
			}
			leftTree->balance = EH;
			node->right = rotateRight(rightTree);
			node = rotateLeft(node);
		}
		else
		{
			if (rightTree->balance != EH)
			{
				node->balance = EH;
				rightTree->balance = EH;
			}
			else
			{
				node->balance = RH;
				rightTree->balance = LH;
				shorter = false;
			}
			node = rotateLeft(node);
		}
	}
	return node;
}

template <class T>
Node<T> *AVL<T>::removeLeftBalance(Node<T> *&node, bool &shorter)
{
	// TODO
	if (node->balance == RH)
	{
		node->balance = EH;
	}
	else if (node->balance == EH)
	{
		node->balance = LH;
		shorter = false;
	}
	else
	{
		Node<T> *leftTree = node->left;
		if (leftTree->balance == RH)
		{
			Node<T> *rightTree = leftTree->right;
			if (rightTree->balance == RH)
			{
				leftTree->balance = LH;
				node->balance = EH;
			}
			else if (leftTree->balance == EH)
			{
				node->balance = EH;
				leftTree->balance = EH;
			}
			else
			{
				node->balance = RH;
				leftTree->balance = EH;
			}
			rightTree->balance = EH;
			node->left = rotateLeft(leftTree);
			node = rotateRight(node);
		}
		else
		{
			if (leftTree->balance != EH)
			{
				node->balance = EH;
				leftTree->balance = EH;
			}
			else
			{
				node->balance = LH;
				leftTree->balance = RH;
				shorter = false;
			}
			node = rotateRight(node);
		}
	}
	return node;
}

template <class T>
int AVL<T>::getHeightRec(Node<T> *node)
{
	if (node == NULL)
		return 0;
	int lh = this->getHeightRec(node->left);
	int rh = this->getHeightRec(node->right);
	return (lh > rh ? lh : rh) + 1;
}

template <class T>
int AVL<T>::getHeight()
{
	return this->getHeightRec(this->root);
}

template <class T>
void AVL<T>::clearRec(Node<T> *&node)
{
	if (node != NULL)
	{
		this->clearRec(node->left);
		this->clearRec(node->right);
		delete node;
		node = NULL;
	}
}

template <class T>
void AVL<T>::clear()
{
	this->clearRec(this->root);
}

template <class T>
void AVL<T>::printTreeStructure()
{
	int height = this->getHeight();

	if (this->root == NULL)
	{
		cout << "NULL\n";
		return;
	}
	queue<Node<T> *> q;
	q.push(root);
	Node<T> *temp;
	int count = 0;
	int maxNode = 1;
	int level = 0;
	int space = pow(2, height);
	printNSpace(space / 2);
	while (!q.empty())
	{
		temp = q.front();
		q.pop();

		if (temp == NULL)
		{
			cout << " ";
			q.push(NULL);
			q.push(NULL);
		}
		else
		{

			// cout << temp->data.time << "-" << temp->data.BP;
			cout << temp->data.time;
			q.push(temp->left);
			q.push(temp->right);
		}
		printNSpace(space);
		count++;
		if (count == maxNode)
		{
			cout << endl;
			count = 0;
			maxNode *= 2;
			level++;
			space /= 2;
			printNSpace(space / 2);
		}
		if (level == height)
			return;
	}
}

template <class T>
bool AVL<T>::checkTimeRangeTravRec(Node<T> *&node, T &value1, T &value2)
{
	if (node == NULL)
	{
		return false;
	}
	else if (value2 < node->data)
	{
		return checkTimeRangeTravRec(node->left, value1, value2);
	}
	else if (value1 > node->data)
	{
		return checkTimeRangeTravRec(node->right, value1, value2);
	}
	else
	{
		return true;
	}
}

template <class T>
bool AVL<T>::checkTimeRangeTrav(T &value1, T &value2)
{
	return checkTimeRangeTravRec(this->root, value1, value2);
}

template <class T>
Node<T> *AVL<T>::findNearestTimeRec(Node<T> *&node, T &value)
{
	if (node == NULL)
	{
		return NULL;
	}
	else if (value < node->data)
	{
		if (node->left == NULL)
		{
			return NULL;
		}
		else
		{
			return findNearestTimeRec(node->left, value);
		}
	}
	else if (value > node->data)
	{
		if (node->right == NULL)
		{
			return node;
		}
		else if (value < node->right->data && node->right->left == NULL)
		{
			return node;
		}
		else if (value < minNode(node->right->left)->data)
		{
			return node;
		}
		else
		{
			return findNearestTimeRec(node->right, value);
		}
	}
	else
	{
		return node;
	}
}

template <class T>
Node<T> *AVL<T>::findNearestTime(T &value)
{
	return findNearestTimeRec(this->root, value);
}

template <class T>
Node<T> *AVL<T>::minNode(Node<T> *&node)
{
	if (node->left == NULL)
		return node;
	else
		return minNode(node->left);
}

//--------------------__AVL TREE__-----------------------

struct TimeUnit
{
	int time;
	float BP, AP;
	bool operator<(const TimeUnit &b)
	{
		return (this->time < b.time);
	};
	bool operator>(const TimeUnit &b)
	{
		return (this->time > b.time);
	};
	bool operator==(const TimeUnit &b)
	{
		return (this->time == b.time);
	};
};

struct Exchange
{
	string QC;
	string BC;
	AVL<TimeUnit> tree;
	Exchange(string bc, string qc) : QC(qc), BC(bc) {}
	~Exchange(){};
};
void printExchange(Exchange &n);

struct openDetail
{
	float lot;
	float oMoney;
};

class eList : public LList<Exchange>
{

public:
	bool firstSet;
	int mn;
	float lv;
	map<int, openDetail> openTradeList;

	Link<Exchange> *findExch(string bc, string qc)
	{
		Link<Exchange> *pTemp = this->head;
		while (pTemp != NULL)
		{
			if (pTemp->data.BC == bc && pTemp->data.QC == qc)
			{
				return pTemp;
			}
			pTemp = pTemp->next;
		}
		return NULL;
	}
};

class ProcessData
{
public:
	static const int MAXSIZECODE = 8;
	static int split(string line, string *&sp);

public:
	eList mainlist;
	ProcessData();
	~ProcessData();
	int process(string line);
	int insert(const string *sp, const int n);
	int update(const string *sp, const int n);
	int del(const string *sp, const int n);
	int sd(const string *sp, const int n);
	int cd(const string *sp, const int n);
	int sl(const string *sp, const int n);
	int ob(const string *sp, const int n);
	int os(const string *sp, const int n);
	int cb(const string *sp, const int n);
	int cs(const string *sp, const int n);
};