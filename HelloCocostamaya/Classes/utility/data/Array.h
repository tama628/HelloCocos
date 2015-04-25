#pragma once

#include <cstring>
#include "../type.h"

// assert()関数の定義
#include "cocos2d.h"
#define ASSERT(cond) CCASSERT(cond, #cond)

// 固定長の配列互換コンテナ
template < class type, int _capacity >
class FixedSizeArray {

protected:

	type array_[_capacity];
	s32 length_;

public:

	FixedSizeArray() { this->clear(); }
	virtual ~FixedSizeArray() {}

	s32 size() const { return length_; }
	s32 capacity() const { return _capacity; }

	void clear()
	{
		length_ = 0;
	}

	bool empty() const
	{
		return length_ <= 0;
	}

	bool full() const
	{
		return capacity <= length_;
	}

	void push_back(const type &value)
	{
		ASSERT(length_ < _capacity);
		array_[length_] = value;
		length_++;
	}

	void pop_back()
	{
		ASSERT(0 < length_);
		length_--;
	}

	type &back()
	{
		ASSERT(!empty());
		return array_[length_-1];
	}

	const type &back() const
	{
		ASSERT(!empty());
		return array_[length_-1];
	}

	type &front()
	{
		ASSERT(!empty());
		return array_[0];
	}

	type &at(s32 index)
	{
		ASSERT(0 <= index && index < length_);
		return array_[index];
	}

	const type &at(s32 index) const
	{
		ASSERT(0 <= index && index < length_);
		return array_[index];
	}

	type &operator[](s32 index)
	{
		return this->at(index);
	}

	const type &operator[](s32 index) const
	{
		return this->at(index);
	}

	void resize(s32 size, type value)
	{
		ASSERT(0 <= size && size <= _capacity);
		if(size <= length_)
		{
			length_ = size;
		}
		else
		{
			int cnt = size - length_;
			while(0 < cnt--)
			{
				this->push_back(value);
			}
		}
	}

	// イテレータ
	class iterator {
		friend class FixedSizeArray;
	protected:
		FixedSizeArray *pArray;
		s32 index;
	public:
		iterator() {}
		iterator(FixedSizeArray *pArray, s32 index) :  pArray(pArray), index(index) {}
		type &operator*() { return pArray->array_[index]; }
		type *operator->() { return &pArray->array_[index]; }
		iterator operator++() { return (*this)++; }
		iterator operator--() { return (*this)--; }
		iterator operator++(int)
		{
			index++;
			return *this;
		}
		iterator operator--(int)
		{
			index--;
			return *this;
		}
		bool operator==(const iterator &it)
		{
			return (pArray == it.pArray && index == it.index);
		}
		bool operator!=(const iterator &it)
		{
			return !(*this == it);
		}
		iterator next() { iterator tmp = *this; return (++tmp); }
		iterator prev() { iterator tmp = *this; return (--tmp); }
	};

	iterator begin()  { return iterator(this, 0); }
	iterator end()    { return iterator(this, length_); }
	iterator rbegin() { return iterator(this, length_-1); }
	iterator rend()   { return iterator(this, -1); }

	iterator insert(iterator pos, const type& value)
	{
		ASSERT(pos.pArray == this);
		ASSERT(length_ < _capacity);
		ASSERT(0 <= pos.index && pos.index <= length_);
		for(int i = length; pos.index < i; i--) {
			// array_[i] = array_[i-1];
			memcpy(&array_[i], &array_[i-1], sizeof(type));
		}
		array_[pos.index] = value;
		length++;
		return pos;
	}

	iterator erase(iterator pos)
	{
		ASSERT(pos.pArray == this);
		ASSERT(0 <= pos.index && pos.index < length_);
		for(int i = pos.index; i < length_-1; i++) {
			// array_[i] = array_[i+1];
			memcpy(&array_[i], &array_[i+1], sizeof(type));
		}
		length_--;
		return pos;
	}

};

// 可変長の配列互換コンテナ
template < class type >
class VariedSizeArray {

protected:

	type *array_;
	s32 length_;
	s32 capacity_;

public:

	VariedSizeArray() : array_(NULL), length_(0), capacity_(0) {}
	virtual ~VariedSizeArray() { this->clear(); }

	// コピーコンストラクタ
	VariedSizeArray(const VariedSizeArray &src) : array_(NULL), length_(0), capacity_(0)
	{
		*this = src;
	}

	VariedSizeArray &operator=(const VariedSizeArray &src)
	{
		this->clear();
		array_ = new type[src.capacity_];

		for(int i = 0; i < src.length_; i++)
		{
			array_[i] = src[i];
		}

		length_ = src.length_;
		capacity_ = src.capacity_;

		return *this;
	}

	s32 size() const { return length_; }
	s32 capacity() const { return capacity_; }

	void clear()
	{
		length_ = 0;
		capacity_ = 0;

		// Bufferの解放
		delete[] array_;
		array_ = NULL;
	}

	bool empty() const
	{
		return length_ <= 0;
	}

	bool full() const
	{
		return capacity_ <= length_;
	}

	void push_back(const type &value)
	{
		if(length_ < capacity_)
		{
			array_[length_] = value;
			length_++;
		}
		else
		{
			// Bufferを拡張
			capacity_++;
			type *buf = new type[capacity_];

			for(int i = 0; i < length_; i++)
			{
				buf[i] = array_[i];
			}

			delete[] array_;
			array_ = buf;

			array_[length_] = value;
			length_++;
		}
	}

	void pop_back()
	{
		ASSERT(0 < length_);
		length_--;
	}

	type &back()
	{
		ASSERT(!empty());
		return array_[length_-1];
	}

	type &front()
	{
		ASSERT(!empty());
		return array_[0];
	}

	type &at(s32 index)
	{
		ASSERT(0 <= index && index < length_);
		return array_[index];
	}
	
	type &at(s32 index) const
	{
		ASSERT(0 <= index && index < length_);
		return array_[index];
	}

	type &operator[](s32 index)
	{
		return this->at(index);
	}
	
	type &operator[](s32 index) const
	{
		return this->at(index);
	}

	void resize(s32 size, type value)
	{
		ASSERT(0 <= size);

		type *buf = new type[size];

		for(int i = 0; i < size; i++)
		{
			i < length_ ?
			buf[i] = array_[i] :
			buf[i] = value ;
		}

		delete[] array_;
		array_ = buf;
		length_ = size;
		capacity_ = size;
	}

	// イテレータ
	class iterator {
		friend class VariedSizeArray;
	protected:
		VariedSizeArray *pArray;
		s32 index;
	public:
		iterator() {}
		iterator(VariedSizeArray *pArray, s32 index) :  pArray(pArray), index(index) {}
		type &operator*() { return pArray->array_[index]; }
		type *operator->() { return &pArray->array_[index]; }
		iterator operator++() { return (*this)++; }
		iterator operator--() { return (*this)--; }
		iterator operator++(int)
		{
			index++;
			return *this;
		}
		iterator operator--(int)
		{
			index--;
			return *this;
		}
		bool operator==(const iterator &it)
		{
			return (pArray == it.pArray && index == it.index);
		}
		bool operator!=(const iterator &it)
		{
			return !(*this == it);
		}
		iterator next() { iterator tmp = *this; return (++tmp); }
		iterator prev() { iterator tmp = *this; return (--tmp); }
	};

	iterator begin()  { return iterator(this, 0); }
	iterator end()    { return iterator(this, length_); }
	iterator rbegin() { return iterator(this, length_-1); }
	iterator rend()   { return iterator(this, -1); }

	iterator insert(iterator pos, const type& value)
	{
		ASSERT(pos.pArray == this);
		ASSERT(length_ < capacity_);
		ASSERT(0 <= pos.index && pos.index <= length_);
		for(int i = length; pos.index < i; i--) {
			// array_[i] = array_[i-1];
			memcpy(&array_[i], &array_[i-1], sizeof(type));
		}
		array_[pos.index] = value;
		length++;
		return pos;
	}

	iterator erase(iterator pos)
	{
		ASSERT(pos.pArray == this);
		ASSERT(0 <= pos.index && pos.index < length_);
		for(int i = pos.index; i < length_-1; i++) {
			// array_[i] = array_[i+1];
			memcpy(&array_[i], &array_[i+1], sizeof(type));
		}
		length_--;
		return pos;
	}

};
