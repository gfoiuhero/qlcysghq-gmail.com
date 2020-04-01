#include<iostream>
#include <vector>
class List
{
	class Element
	{
		int data;
		Element* pNext;
		Element* pPrev;
	
	public:
		Element(int data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	};
	Element* head;
	Element* tail;
	unsigned int size;
public:
	class RIterator
	{
		Element* Temp;
	public:
		RIterator(Element* Temp)
		{
			this->Temp = Temp;
			std::cout << "PItConstructor:\t" << this << std::endl;
		}
		~RIterator()
		{
			std::cout << "PItDesstructor:\t" << this << std::endl;
		}
		RIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		RIterator& operator++(int)
		{
			RIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		const int& operator*()const
		{
			return Temp->data;
		}
		int& operator*()
		{
			return Temp->data;
		}

		bool operator ==(const RIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator !=(const RIterator& other)const
		{
			return this->Temp != other.Temp;
		}

	
	};
	RIterator rend()
	{
		return  nullptr;
	}
	RIterator rbegin()
	{
		return tail;
	}
	const RIterator rbegin()const
	{
		return tail;
	}
	const RIterator rend() const
	{

		return nullptr;
	}



	const Element* get_head() const
	{
		return head;
	}
	Element* get_head()
	{
		return head;
	}
	const Element* get_tail() const
	{
		return tail;
	}
	Element* get_tail()
	{
		return tail;
	}
	unsigned int get_size()const
	{
		return size;
	}
	class Iterator
	{
		Element* Temp;
	public:
	 
		

		Iterator(Element* Temp);
		
		~Iterator();
		


		//		Operators:
		Iterator& operator++();

		Iterator operator++(int);

		const int& operator*()const;

		int& operator*();
		bool operator==(const Iterator& other)const;

		bool operator!=(const Iterator& other)const;

		//////////////////
	};




	const Iterator begin()const;
	const Iterator end() const;
	Iterator begin();
	Iterator end();

	List();
	List(const std::initializer_list<int>& il);
	List(const List& other);
	List(List&& other);
	~List();

	//			Operators:
	List& operator=(List&& other);


	List& operator=(const List& other);

	//			Adding elements:
	void push_front(int data);
	void push_back(int data);
	void insert(int index, int data);
	//			Removing elements:
	void pop_front();
	void pop_back();

	void erase(int index);

	//			Methods:
	void print()const;
	void print_reverse()const;
	
};

List::Iterator::Iterator(Element* Temp)
{
	this->Temp = Temp;
#ifdef DEBUG
	std::cout << "ItConstructor:\t" << this << std::endl;
#endif // DEBUG

}
List::Iterator::~Iterator()
{
#ifdef DEBUG
	std::cout << "ItDestructor:\t" << this << std::endl;
#endif // DEBUG

}

//		Operators:
List::Iterator& List::Iterator::operator++()
{
	Temp = Temp->pNext;
	return *this;
}

List::Iterator List::Iterator::operator++(int)
{
	Iterator old = *this;	//CopyConstructor
	Temp = Temp->pNext;
	return old;
}

const int& List::Iterator::operator*()const
{
	return Temp->data;
}

int& List::Iterator::operator*()
{
	return Temp->data;
}

bool List::Iterator::operator==(const Iterator& other)const
{
	return this->Temp == other.Temp;
}

bool List::Iterator::operator!=(const Iterator& other)const
{
	return this->Temp != other.Temp;
}
List::Element::Element(int data, Element* pNext, Element* pPrev) :data(data), pNext(pNext), pPrev(pPrev)
{
	std::cout << "EConstructor:\t" << this << std::endl;
}
List::Element::~Element()
{
	std::cout << "EDestructor:\t" << this << std::endl;
}
const List::Iterator List::begin()const
{
	return this->head;
}
const List::Iterator List::end() const
{
	return nullptr;
}
List::Iterator List::begin()
{
	return this->head;
}
List::Iterator List::end()
{
	return nullptr;
}





List::List()
{
	head = tail = nullptr;
	size = 0;
	std::cout << "LConstructor:\t" << this << std::endl;
}
List::List(const std::initializer_list<int>& il) :List()
{
	std::cout << typeid(il.begin()).name() << std::endl;
	/*for (int const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}*/
	for (int i : il)
	{
		push_back(i);
	}
}
List::List(const List& other) :List()
{
	/*for (Element* Temp = other.head; Temp; Temp = Temp->pNext)
	{
		push_back(Temp->data);
	}*/
	for (Iterator it = other.head; it != nullptr; it++)
		push_back(*it);
	std::cout << "LCopyConstructor:\t" << this << std::endl;
}
List::List(List&& other)
{
	this->head = other.head;
	this->size = other.size;
	this->tail = other.tail;
	other.head = other.tail = nullptr;
	std::cout << "LMoveConstructor:\t" << this << std::endl;

}
List::~List()
{
	while (head || tail)
	{
		pop_front();
		pop_back();
	}
	std::cout << "LDestructor:\t" << this << std::endl;
}

//			Operators:
List& List::operator=(List&& other)
{
	while (head)pop_front();
	this->head = other.head;
	this->size = other.size;
	this->tail = other.tail;
	other.head = other.tail = nullptr;
	std::cout << "LMoveAssignment:\t" << this << std::endl;
	return*this;
}


List&List:: operator=(const List& other)
{
	if (this == &other)return *this;
	while (head)pop_front();
	for (Element* Temp = other.head; Temp; Temp++)push_back(Temp->data);
	std::cout << "LCopyAssignment:\t" << this << std::endl;
	return *this;
}

//			Adding elements:
void List::push_front(int data)
{
	if (head == nullptr)
	{
		head = tail = new Element(data);
		size++;
		return;
	}
	head = head->pPrev = new Element(data, head);
	size++;
}
void List::push_back(int data)
{
	if (tail == nullptr)
	{
		head = tail = new Element(data);
		size++;
		return;
	}
	tail = tail->pNext = new Element(data, nullptr, tail);
	size++;
}
void List::insert(int index, int data)
{
	if (index > size)throw std::exception("Error: out of range");
	Element* Temp;
	if (index < size / 2)
	{
		Temp = head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = tail;
		for (int i = 0; i < size - 1 - index; i++)Temp = Temp->pPrev;
	}

	/*Element* New = new Element(data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;*/

	Temp->pPrev = Temp->pPrev->pNext = new Element(data, Temp, Temp->pPrev);
	size++;
}
//			Removing elements:
void List::pop_front()
{
	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
		if (size)size--;
		return;
	}
	head = head->pNext;
	delete head->pPrev;
	head->pPrev = nullptr;
	size--;
}
void List::pop_back()
{
	if (head == tail)
	{
		delete tail;
		head = tail = nullptr;
		if (size)size--;
		return;
	}
	tail = tail->pPrev;
	delete tail->pNext;
	tail->pNext = nullptr;
	size--;
}

void List::erase(int index)
{
	if (index >= size)throw std::exception("Error: Out of range");
	if (index == 0)
	{
		pop_front();
		return;
	}
	if (index == size - 1)
	{
		pop_back();
		return;
	}

	Element* Temp;
	if (index < size / 2)
	{
		Temp = head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = tail;
		for (int i = 0; i < size - 1 - index; i++)Temp = Temp->pPrev;
	}

	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
	size--;
}

//			Methods:
void List::print()const
{
	for (Element* Temp = head; Temp != nullptr; Temp = Temp->pNext)
	{
		std::cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->data << "\t" << Temp->pNext << std::endl;
	}
	std::cout << "List size:\t" << size << std::endl;
}
void List::print_reverse()const
{
	for (Element* Temp = tail; Temp != nullptr; Temp = Temp->pPrev)
	{
		std::cout << Temp->pPrev << "\t" << Temp << "\t" << Temp->data << "\t" << Temp->pNext << std::endl;
	}
	std::cout << "List size:\t" << size << std::endl;
}

List operator+(const List& left, const List& right)
{
	List Buf = left;
	for (List::Iterator it = right.begin(); it != right.end(); it++)
	{
		Buf.push_back(*it);

	}
	std::cout << "Global operator +\n";
	return Buf;
}


//#define BASE_CHECK
//#define CONSTRUCTORS_CHECK

void main()
{
	int n;
	std::cout << "Input list size: "; std::cin >> n;
#ifdef BASE_CHECK
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.print_reverse();
	int index;
	int data;
	try
	{
		std::cout << "Input index: "; std::cin >> index;
		//std::cout << "Input value: "; std::cin >> data;
		//list.insert(index, data);
		list.erase(index);
		list.print();
		list.print_reverse();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
#endif // BASE_CHECK

#ifdef CONSTRUCTORS_CHECK
	int arr[] = { 3, 5, 8 };

	List list = { 3, 5, 8, 13, 21 };
	list = list;
	list.print();
	list.print_reverse();

	List list2 = list;
	//list2 = list;
	list2.print();
	list2.print_reverse();
#endif // CONSTRUCTORS_CHECK

	//for (List::Iterator it = list.begin(); it != list.end(); it++)
		//std::cout << *it << "\t";

	List list1 = { 123,555,789 };
	List list2 = { 34,55,89 };
	for (List::Iterator it = list2.begin(); it != list2.end(); it++)
		std::cout << *it << "\t";
	std::cout << std::endl;
	
	List list3;
	list3 = list1 + list2;
	std::cout << std::endl;
	for (List::RIterator rit = list1.rbegin(); rit != list1.rend(); rit++)
	{
		std::cout << *rit << "\t";
	}
	std::cout << std::endl;
}