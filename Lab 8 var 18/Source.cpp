#include <iostream>
#include <windows.h>
#include <iterator>
#include <vector>

using namespace std;

template<typename T>
class forward_list
{
public:
	forward_list();
	~forward_list();

	T& operator[](const int index);
	int getSize() { return Size; }
	void pop_front();
	void clear();
	void push_front(T data);

private:
	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		T data; //���� ����������� ����
		Node(T data = T(), Node* pNext = nullptr) //�� ��������� ��������� �� ��������� ������� ��������� �� NULL
		{
			this->data = data; //����������� �������� ��������� ����� ������ Node
			this->pNext = pNext;
		}
	};
	//���� ������ forward_list
	int Size;
	Node<T>* head;
};


template<typename T>
forward_list<T>::forward_list()
{
	Size = 0;
	head = nullptr;
}

template<typename T>
forward_list<T>::~forward_list()
{
	clear();
}

template<typename T>
void forward_list<T>::pop_front()
{
	Node<T>* temp = head; //������� ��������� ������, ���������� ����� ������ ������
	head = head->pNext; //����������� �������� �� ������ ������ �������, ������ ������ �� ���
	delete temp; //������� ��������� ������
	Size--; //��������� ������ ������ �� �������

}

template<typename T>
void forward_list<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template<typename T>
void forward_list<T>::push_front(T data)
{
	head = new Node<T>(data, head); //�������� � ������ ����� ������� � ����������� �� ������� ������ ������
	Size++;
}

template<typename T>
T& forward_list<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head; //current ��������� �� ������ ������
	while (current != nullptr) //���� current �� ����� ��������� �� ��������� �������
	{
		if (counter == index)
		{
			return current->data; //���� �������� �������� ��������� � �������� ���������� ��������, �� ���������� ���� �������
		}
		current = current->pNext; //�������� �������� ����������� ����� ���������� ��������
		counter++; //������� � ��������� �������� �����
	}
}

void basic()

{

	/* ������� �������� ���������������� ������ �� ����� �����.
	������� �� ������ ��� �������� ����� ������� �������� � �������� ���������. */

	forward_list<short> numbers;
	short amount;
	do
	{
		cout << endl << "Input an amount of elements in list: ";
		cin >> amount;
		cin.clear();
		cin.ignore(std::cin.rdbuf()->in_avail());
		if (amount <= 0)
			cout << "Amount of elements must be greater than 0.";
	} while (amount <= 0);
	vector<short> temp_array(amount);
	cout << endl << "Elements in list in the beginning:" << endl;
	for (int i = 0; i < amount; i++)
	{
		short temp;
		temp = -20 + rand() % 40;
		numbers.push_front(temp);
		cout << temp << " ";
		temp_array[i] = temp;
	}
	for (int i = 0; i < temp_array.size(); i++)
	{
		vector<short>::iterator pos1 = temp_array.begin();
		vector<short>::iterator pos2 = pos1;
		vector<short> indeces;
		short j = 0, k = 0;
		if (temp_array[i] % 2 != 0)
		{
			j++;
			indeces.resize(j);
			indeces[k++] = i;
			if (i + 3 > temp_array.size())
			{
				if (temp_array.back() % 2 != 0 && (temp_array.size() - 1) - indeces[indeces.size() - 1] < 1) //�������� ����� ��������� �������� ������� � �������� ���������� ������������ ��������
					continue;
				else
				{
					temp_array.pop_back();
					break;
				}
			}
			advance(pos1, i + 1);
			advance(pos2, i + 3);
			temp_array.erase(pos1, pos2);
		}
	}
	numbers.clear();
	for (int i = 0; i < temp_array.size(); i++)
		numbers.push_front(temp_array[temp_array.size() - i - 1]);
	cout << endl << endl << "Elements in list in the end:" << endl;
	for (int i = 0; i < numbers.getSize(); i++)
		cout << numbers[i] << " ";
	cout << endl << endl;
}

template <typename T>
class list
{
public:
	list <T>();
	~list <T>();

	int getSize() { return Size; }

	void clear();
	void push_front(T data);
	void push_back(T data);
	void pop_front();
	void pop_back();
	void InsertBefore(T data, int index);
	void erase(int index);

	T& operator [] (const int index);

private:
	template <typename T>
	class Node
	{
	public:
		T data;
		Node* pNext;
		Node* pPrev;
		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};
	int Size;
	Node <T>* head;
	Node <T>* tail;
};

template <typename T> list <T>::list()
{
	head = nullptr;
	tail = nullptr;
	Size = 0;
}

template <typename T> list <T>::~list()
{
	clear();
}

template<typename T>
void list<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template <typename T>
void list <T>::push_front(T data)
{
	if (Size > 1)
	{
		Node <T>* temp = head; //��������� �� ������ ������
		head = new Node <T>(data, head); //� ������ ������ ��������� �������
		temp->pPrev = head; //��������, ������� ����� temp, ������������� ������ �� ������ ������
	}
	else if (Size == 1)
	{
		head = new Node <T>(data, head); //��������� �������
		tail->pPrev = this->head; //���������� ������� � tail = head
	}
	else if (Size == 0)
	{
		head = tail = new Node <T>(data, head, tail); //��������� ����� �������, ���������� "�������" � "������� ������"
	}
	Size++;
}

template <typename T>
void list <T>::push_back(T data)
{
	if (Size > 1)
	{
		Node <T>* temp = tail; //��������� �� ����� ������
		tail = new Node <T>(data, nullptr, tail);
		temp->pNext = tail;
	}
	else if (Size == 1)
	{
		tail = new Node <T>(data, nullptr, tail);
		head->pNext = this->tail;
	}
	else if (Size == 0)
	{
		head = tail = new Node <T>(data, head, tail);
	}
	Size++;
}

template <typename T>
void list <T>::pop_front()
{
	if (Size > 1)
	{
		Node <T>* temp = head;
		head = head->pNext;
		delete temp;
	}
	else if (Size == 1)
	{
		Node <T>* temp = head;
		head = tail = head->pNext;
		delete temp;
	}
	Size--;
}

template <typename T>
void list <T>::pop_back()
{
	if (Size > 1)
	{
		Node <T>* temp = tail; //������� ��������� ������, ���������� ������ �� tail 
		tail = tail->pPrev; //tail ����������� ������ �� �������, ������ ����� ���
		delete temp;
	}
	else if (Size == 1)
	{
		Node <T>* temp = tail;
		head = tail = tail->pPrev; //���� � ������ 1 �������, �� head = tail
		delete temp;
	}
	Size--;
}

template <typename T>
void list <T>::InsertBefore(T data, int index)
{
	if (index == 0)
		push_front(data);
	else
	{
		Node<T>* current = this->head;
		for (int i = 0; i < index - 1; i++) //���� ����������� ���� current �� ����� ��������� �� �������, �������������� �������� � ��������� ��������
		{
			current = current->pNext; //�������� �������� ����������� ����� ����������
		}
		Node<T>* newNode = new Node<T>(data, current->pNext, current); //��������� �������
		current->pNext = newNode; //����������� ���� "�����" ������� �������� ����� �� ����� �������
		Node<T>* next = newNode->pNext; //��������� next ����������� ����� ���������� ��������, ����� ������������ � ������
		next->pPrev = newNode; //����������� �������� � next ������������ ����� �� ����������� �������
	}
	Size++;
}

template <typename T>
void list <T>::erase(int index)
{
	if (index == 0)
		pop_front();
	else if (index + 1 < Size)
	{
		Node<T>* current = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->pNext;
		}
		Node<T>* toDelete = current->pNext; //���������� ��������� ����������� ������ �� ��������� ������� ����� �������� ���������
		current->pNext = toDelete->pNext; //���������� ��������� ����������� ����� �� ��������� ������� ���������� ��������� ((current->pNext)->pNext)
		Node<T>* next = toDelete->pNext;
		delete toDelete; //������� ��������� ���������
		next->pPrev = current; //����������� �������� next ���������� ����� �� ������� �������
	}
	Size--;
}

template <typename T>
T& list <T>::operator[] (const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

void medium()

{

	/* ������� �������� ��������������� ������ �� ��������.
	������� �� ������ ������� ����� ������� ������� &. */

	list<char> characters;
	short amount;
	do
	{
		cout << endl << "Input an amount of characters in list: ";
		cin >> amount;
		cin.clear();
		cin.ignore(std::cin.rdbuf()->in_avail());
		if (amount <= 0)
			cout << "Amount of characters must be greater than 0.";
	} while (amount <= 0);
	cout << endl << "Your string in the beginning:" << endl;
	for (int i = 0; i < amount; i++)
	{
		char temp;
		temp = 35 + rand() % 15;
		characters.push_back(temp);
		cout << temp;
	}
	for (int i = 0; i < characters.getSize(); i++)
	{
		if (characters[i] == '&')
			characters.erase(i + 1);
	}
	cout << endl << endl << "Your string in the end :" << endl;
	for (int i = 0; i < characters.getSize(); i++)
		cout << characters[i];
	cout << endl << endl;
}

void hard()

{

	/* ��� �������� ���������� ������, ������, ��������� � ������� �������� �������� ����� ������ P1, P2 � P3. ����� ���� ���� �����.
	������� ��������� InsertBefore(L,D), ������� ��������� ����� ������� �� ��������� D ����� ������� ��������� ������ L.
	����������� ������� ���������� �������. � ������� ���� ��������� �������� ���� ������ �����
	� �������� ������ � ������� ����� ������ ��� �������, ���������� � �������� ���������. */

	list<short> L;
	vector<short> D(5);
	short amount, current, * P1, * P2, * P3;
	do
	{
		cout << endl << "Input an amount of elements in list: ";
		cin >> amount;
		cin.clear();
		cin.ignore(std::cin.rdbuf()->in_avail());
		if (amount <= 0)
			cout << "Amount of elements must be greater than 0.";
	} while (amount <= 0);
	cout << endl << "Elements in list in the beginning:" << endl;
	for (int i = 0; i < amount; i++)
	{
		short temp;
		temp = -20 + rand() % 40;
		L.push_back(temp);
		cout << temp << " ";
	}
	for (int i = 0; i < D.size(); i++)
	{
		D[i] = -20 + rand() % 40;;
	}
	do
	{
		cout << endl << endl << "Select current element (from 1 to " << amount << "): ";
		cin >> current;
		if (current <= 0 || current > amount)
			cout << "Selected element is out of range.";
	} while (current <= 0 || current > amount);
	P1 = &L[0];
	P2 = &L[L.getSize() - 1];
	P3 = &L[current - 1];
	cout << endl << "Old address of P1 (Beginning): " << P1;
	cout << endl << "Old address of P2 (End): " << P2;
	cout << endl << "Old address of P3 (Current): " << P3;
	for (int i = 0; i < D.size(); i++)
		L.InsertBefore(D[i], current - 1);
	P1 = &L[0];
	P2 = &L[L.getSize() - 1];
	P3 = &L[current - 1];
	cout << endl << endl << "Elements in list in the end:" << endl;
	for (int i = 0; i < L.getSize(); i++)
		cout << L[i] << " ";
	cout << endl << endl << "New address of P1 (Beginning): " << P1;
	cout << endl << "New address of P2 (End): " << P2;
	cout << endl << "New address of P3 (Current): " << P3;
	cout << endl << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	short number;
	cout << "Variant 18." << endl;
	do
	{
		cout << "What task do you like to run?" << endl;
		cout << "1 - Basic level" << endl;
		cout << "2 - Medium level" << endl;
		cout << "3 - High level" << endl;
		cout << "0 - Exit" << endl;
		cout << "Input a number please : ";
		while (!(cin >> number))
		{
			cout << "Input a number please : ";
			cin >> number;
			cin.clear();
			cin.ignore(std::cin.rdbuf()->in_avail());
		}
		switch (number)
		{
		case 1:
			basic();
			break;
		case 2:
			medium();
			break;
		case 3:
			hard();
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Task doesn't exist." << endl << endl;
			break;
		}
	} while (number != 0);
	return 0;
}