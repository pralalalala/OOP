#pragma once
#pragma once
#include <string>
#include "Classes.h"
#include <type_traits>
#include <ranges>

template<typename T>
class node {
public:

	using undef_type = std::conditional<std::is_same<T, Classes::DK>::value, double, int>;

	T item;
	std::string name;
	node* next;
	node* prev;
};


template<typename T>
class biderectional_iterator // двунаправ(не кольцевой).список
{
private:
	node<T>* item;

public:
	biderectional_iterator() = default;
	biderectional_iterator(const biderectional_iterator& it) = default;
	biderectional_iterator(biderectional_iterator&& it) = default;
	biderectional_iterator(node<T>* a) : item(a) {}
	biderectional_iterator& operator++() {
		item = item->next;
		return *this;
	}
	biderectional_iterator& operator++(int) {
		biderectional_iterator temp(this->item->next);
		return temp;
	}
	biderectional_iterator& operator--() {
		item = item->prev;
		return *this;
	}
	biderectional_iterator& operator--(int) {
		biderectional_iterator temp(this->item->prev);
		return temp;
	}
	biderectional_iterator& operator=(const biderectional_iterator& other) {
		if (this == &other)
		{
			*item = *other.item;
		}
		return *this;
	}

	node<T>& operator*() {
		return *this->item;
	}
	const node<T>& operator*() const {
		return *item;
	}
	node<T>& operator->() {
		return **this;
	}
	const node<T>& operator->() const {
		return **this;
	}

	bool operator==(const biderectional_iterator& other) const {
		return item == other.item;
	}
	bool operator!=(const biderectional_iterator& other) const {
		return !(*this == other);
	}

};

template<typename T>
class MyList
{
private:
	node<T>* head;
	node<T>* tail;
	size_t size;
public:
	using value_type = T;
	using reference = T&;
	using const_reference = const T&;
	using iterator = biderectional_iterator<T>;
	using const_iterator = const iterator;
	using defference_type = signed int;
	using size_type = unsigned int;

	constexpr MyList() = default; // можно вызывать на этапе компил€ции, иначе выполн€етс€ компил€ци€ ссылки на экземпл€р класс шаблон функции "MyList<T>"
	MyList(MyList& a) {
		head = a.head;
		tail = a.tail;
		size = a.size;
	}
	MyList(MyList&& a) {
		head = std::move(a.head); head = nullptr;
		tail = std::move(a.tail); tail = nullptr;
		size = std::move(a.size); size = NULL;
	}
	~MyList() = default;

	MyList& operator=(MyList& a) {
		if (this->begin() != a.begin() and this->end() != a.end() and this->size != a.size) { //двигаеемс€ по списку пока не найдЄм a
			head = a.head;
			tail = a.tail;
			size = a.size;
		}
		return *this;
	}
	MyList& operator=(MyList&& a) { //  уничтожение или move-assings из списка
		if (this->begin() != a.begin() and this->end() != a.end() and this->size != a.size) {
			head = a.head;
			a.head = nullptr;
			tail = a.tail;
			a.tail = nullptr;
		}
		return *this;
	}

	constexpr iterator begin() {
		return head;
	}
	constexpr iterator end() {
		return tail;
	}
	constexpr const_iterator cbegin() {
		return begin();
	}
	constexpr const_iterator cend() {
		return end();
	}
	bool operator==(MyList& a) {
		return (this->begin() == a.begin() and this->end() == a.end() and this->size == a.size);
	}
	bool operator!=(MyList& a) {
		return !this->operator==(a);
	}
	void swap(MyList& a) {
		std::swap(*this, a);
	}
	constexpr size_type current_size() {
		return size;
	}
	size_type max_size() const {
		return sizeof(size_type) / sizeof(T);

	}
	constexpr bool empty() {
		return this->begin() == this->end();
	}

	bool search(std::string name)
	{
		iterator iter = begin();
		for (int i : (0, (int)size)) // должно рабоатть с constexpr
		{
			if (iter.operator*().name == name)
			{
				return true; // Ёлем найден
			}
		}
		return false; // Ёлем не найден
	}

	void push_back(const T& value, std::conditional<std::is_same<T, Classes::DK>::value, double, int> term, std::string name) {
		if (size == 0) { // ≈сли списка нет, то создать
			head = new node<T>();
			head->next = nullptr;
			head->item = value;
			head->name = name;
			head->prev = nullptr;
			head->term = term;
			tail = head;
		}
		else {
			if (size == 1) {
				node<T>* temp = new node<T>();
				head->next = temp;
				temp->prev = head;
				temp->next = nullptr;
				temp->item = value;
				temp->name = name;
				temp->term = term;
				tail = temp;
			}
			else {
				node<T>* temp = new node<T>();
				tail->next = temp;
				temp->prev = tail;
				tail = temp;
				tail->next = nullptr;
				tail->item = value;
				tail->name = name;
			}
		}
	}
};