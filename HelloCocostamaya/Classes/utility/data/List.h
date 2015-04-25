#pragma once

#include <cstring>
#include "../type.h"

// assert()ä÷êîÇÃíËã`
#include "cocos2d.h"
#define ASSERT(cond) CCASSERT(cond, #cond)

// å≈íËí∑ÇÃëoï˚å¸ÉäÉXÉg
template < class type, int _capacity >
class FixedSizeList {

public:

	struct Element {
		type value;
		Element *prev;
		Element *next;
		Element() : prev(this), next(this) {}
	};

protected:

	Element usingList_;
	Element freeList_;
	Element array_[_capacity];
	s32 length_;

private:

	void _insert(Element* pos, Element* elem)
	{
		elem->prev = pos->prev;
		elem->next = pos;
		elem->prev->next = elem;
		elem->next->prev = elem;
	}

	void _erase(Element* elem)
	{
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
	}

public:

	FixedSizeList() { clear(); }
	virtual ~FixedSizeList() {}

	s32 size() const { return length_; }
	s32 capacity() const { return _capacity; }

	void clear()
	{
		usingList_.next = &usingList_;
		usingList_.prev = &usingList_;
		freeList_.next = &freeList_;
		freeList_.prev = &freeList_;
		for(s32 i = 0; i < _capacity; i++) {
			_insert(&freeList_, &array_[i]);
		}
		length_ = 0;
	}

	bool empty() const
	{
		return length_ <= 0;
	}

	bool full() const
	{
		return _capacity <= length_;
	}

	void push_back(const type &value)
	{
		ASSERT(length_ < _capacity);
		Element* elem = freeList_.prev;
		_erase(elem);
		elem->value = value;
		_insert(&usingList_, elem);
		length_ ++;
	}

	void push_front(const type &value)
	{
		ASSERT(length_ < _capacity);
        Element* elem = freeList_.prev;
        _erase(elem);
        elem->value = value;
        _insert(usingList_.next, elem);
        length_ ++;
	}

	void pop_back()
	{
		ASSERT(0 < length_);
		Element* elem = usingList_.prev;
		_erase(elem);
		_insert(&freeList_, elem);
		length_ --;
	}

	void pop_front()
	{
		ASSERT(0 < length_);
		Element* elem = usingList_.next;
		_erase(elem);
		_insert(&freeList_, elem);
		length_ --;
	}

	type &back()
	{
        ASSERT(usingList_.prev != &usingList_);
        return usingList_.prev->value;
	}

	type &front()
	{
        ASSERT(usingList_.next != &usingList_);
        return usingList_.next->value;
	}

	class iterator {
		friend class FixedSizeList;
	protected:
		FixedSizeList *pFixList;
		Element *elem;
	public:
		iterator() {}
		iterator(FixedSizeList *pFixList, Element* elem) : pFixList(pFixList), elem(elem) {}
		type &operator*() { return elem->value; }
		type *operator->() { return &elem->value; }
		iterator operator++() { return (*this)++; }
		iterator operator--() { return (*this)--; }
		iterator operator ++(int)
		{
			elem = elem->next;
			return *this;
		}
		iterator operator --(int)
		{
			elem = elem->prev;
			return *this;
		}
		bool operator==(const iterator& it)
		{
			return (elem == it.elem);
		}
		bool operator!=(const iterator& it)
		{
			return !(*this==it);
		}
		iterator next(){ return iterator(pFixList, elem->next); }
		iterator prev(){ return iterator(pFixList, elem->prev); }

		// ì¸ÇÍë÷Ç¶
		void swap(iterator it)
		{
			ASSERT(it.pFixList == pFixList);

			Element *elem2 = it.elem;

			Element *elem_prev = elem->prev;
			Element *elem_next = elem->next;
			Element *elem2_prev = elem2->prev;
			Element *elem2_next = elem2->next;

			elem_prev->next = elem2;
			elem_next->prev = elem2;
			elem2_prev->next = elem;
			elem2_next->prev = elem;

			elem->prev = elem2_prev;
			elem->next = elem2_next;
			elem2->prev = elem_prev;
			elem2->next = elem_next;
		}
	};

	iterator begin(){ return iterator(this, usingList_.next); }
	iterator end(){ return iterator(this, &usingList_); }
	iterator rbegin(){ return iterator(this, usingList_.prev); }
	iterator rend(){ return iterator(this, &usingList_); }

	iterator insert(iterator pos, const type& value)
	{
		ASSERT(pos.pFixList == this);
		ASSERT(length_ < _capacity);
		Element *elem = freeList_.prev;
		_erase(elem);
		elem->value = value;
		_insert(pos.elem, elem);
		length_++;
		return iterator(this, elem);
	}

	iterator erase(iterator pos)
	{
		ASSERT(pos.pFixList == this);
		ASSERT(0 < length_);
		Element *tmp = pos.elem->next;
		Element *elem = pos.elem;
		_erase(elem);
		_insert(&freeList_, elem);
		length_--;
		return iterator(this, tmp);
	}

};
