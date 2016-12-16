#pragma once
#include <iterator>
#include <string>
#include <memory>
#include <functional>

template <typename ValueType>
class CStringList
{
	struct Node
	{
		Node(const ValueType & data, Node * prev, std::unique_ptr<Node> && next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		ValueType data;
		Node *prev;
		std::unique_ptr<Node> next;
	};
public:
	CStringList();
	size_t GetSize()const;
	void Append(const ValueType &data);
	void AddToFront(const ValueType &data);
	bool IsEmpty()const;
	void Clear();
	
	CStringList & operator=(const CStringList &other);
	CStringList & operator=(CStringList && other);
	class CIterator : public std::iterator<std::bidirectional_iterator_tag, Node, ptrdiff_t>
	{
		 friend CStringList<ValueType>;
		 CIterator(Node *node, bool isReverse = false);
	public:
		friend bool const operator==(typename CStringList<ValueType>::CIterator const &it1, typename CStringList<ValueType>::CIterator const &it2)
		{
			return it1.m_node == it2.m_node;
		}
		friend bool const operator!=(typename CStringList<ValueType>::CIterator const &it1, typename CStringList<ValueType>::CIterator const &it2)
		{
			return !(it1 == it2);
		}
		CIterator() = default;
		ValueType &operator*()const;
		CIterator &operator++();
		CIterator &operator--();
	private:
		Node *m_node = nullptr;
		bool m_isReverse = false;

	};

	CIterator begin();
	CIterator end();
	const CIterator cbegin()const;
	const CIterator cend()const;

	CIterator rbegin();
	CIterator rend();
	const CIterator crbegin()const;
	const CIterator crend()const;

	CIterator Insert(CIterator &iter, ValueType const &data);
	CIterator Erase(CIterator &iter); 
	ValueType & GetBackElement();
	ValueType & GetFrontElement();
	ValueType const& GetBackElement()const;
	ValueType const& GetFrontElement()const;

	~CStringList();
private:
	void ResetList();
	size_t m_size = 0;
	std::unique_ptr<Node> m_imaginaryLastItem = nullptr;
	std::unique_ptr<Node> m_imaginaryFirstItem = nullptr;
	Node *m_firstNode = nullptr;
	Node *m_lastNode = nullptr;
};

template <typename ValueType>
CStringList<ValueType>::CStringList()
{
}

template <typename ValueType>
CStringList<ValueType>::~CStringList()
{
	while (m_imaginaryFirstItem)
	{
		auto tmp = move(m_imaginaryFirstItem->next);
		m_imaginaryFirstItem.reset();
		m_imaginaryFirstItem = move(tmp);
	}
	m_lastNode = nullptr;
}

template<typename ValueType>
inline void CStringList<ValueType>::ResetList()
{
	m_imaginaryFirstItem = make_unique<Node>(ValueType(), nullptr, make_unique<Node>(ValueType(), nullptr, nullptr));
	m_firstNode = m_imaginaryFirstItem->next.get();
	m_lastNode = m_firstNode;
	m_imaginaryLastItem = make_unique<Node>(ValueType(), m_lastNode, nullptr);
	m_lastNode->next = move(m_imaginaryLastItem);
}


template <typename ValueType>
size_t CStringList<ValueType>::GetSize() const
{
	return m_size;
}

template <typename ValueType>
void CStringList<ValueType>::Append(const ValueType & data)
{
	unique_ptr<Node> newNode;
	try
	{
		if (IsEmpty())
		{
			ResetList();
		}
		newNode = make_unique<Node>(data, m_lastNode, nullptr);
	}
	catch (...)
	{
		throw;
	}
	Node *newLastNode = newNode.get();
	m_imaginaryLastItem = move(m_lastNode->next);
	m_imaginaryLastItem->prev = newLastNode;
	if (m_lastNode->prev)
	{
		newNode->next = move(m_imaginaryLastItem);
		m_lastNode->next = move(newNode);
	}
	else
	{
		newNode->next = move(m_imaginaryLastItem);
		m_imaginaryFirstItem->next = move(newNode);
		m_firstNode = m_imaginaryFirstItem->next.get();
		m_firstNode->prev = m_imaginaryFirstItem.get();
	}
	m_lastNode = newLastNode;
	++m_size;
}

template <typename ValueType>
void CStringList<ValueType>::AddToFront(const ValueType & data)
{
	std::unique_ptr<Node> newNode;
	try
	{
		if (IsEmpty())
		{
			ResetList();
		}
		newNode = make_unique<Node>(data, nullptr, nullptr);
	}
	catch (...)
	{
		throw;
	}
	if (m_size != 0)
	{
		m_firstNode->prev = newNode.get();
		newNode->next = move(m_imaginaryFirstItem->next);
	}
	else
	{
		m_imaginaryLastItem = move(m_lastNode->next);
		m_lastNode = newNode.get();
		m_imaginaryLastItem->prev = m_lastNode;
		m_lastNode->next = move(m_imaginaryLastItem);
	}
	newNode->prev = m_imaginaryFirstItem.get();
	m_imaginaryFirstItem->next = move(newNode);
	m_firstNode = m_imaginaryFirstItem->next.get();
	++m_size;
}

template <typename ValueType>
bool CStringList<ValueType>::IsEmpty()const
{
	return m_size == 0;
}

template <typename ValueType>
void CStringList<ValueType>::Clear()
{
	while (m_imaginaryFirstItem)
	{
		auto tmp = move(m_imaginaryFirstItem->next);
		m_imaginaryFirstItem.reset();
		m_imaginaryFirstItem = move(tmp);
	}
	m_size = 0;
	ResetList();
}

template <typename ValueType>
ValueType & CStringList<ValueType>::GetBackElement()
{
	if (IsEmpty())
	{
		throw runtime_error("List is empty.");
	}

	return  m_lastNode->data;
}

template <typename ValueType>
ValueType & CStringList<ValueType>::GetFrontElement()
{
	if (IsEmpty())
	{
		throw runtime_error("List is empty.");
	}

	return m_firstNode->data;
}

template <typename ValueType>
ValueType const & CStringList<ValueType>::GetBackElement()const
{
	if (IsEmpty())
	{
		throw runtime_error("List is empty.");
	}

	return  m_lastNode->data;
}

template <typename ValueType>
ValueType const & CStringList<ValueType>::GetFrontElement()const
{
	if (IsEmpty())
	{
		throw runtime_error("List is empty.");
	}

	return m_firstNode->data;
}

template <typename ValueType>
CStringList<ValueType>::CIterator::CIterator(Node *node, bool isReverse)
	: m_node(node)
	, m_isReverse(isReverse)

{
};

template<typename ValueType>
CStringList<ValueType> & CStringList<ValueType>::operator=(CStringList && other)
{

}

template<typename ValueType>
CStringList<ValueType> & CStringList<ValueType>::operator=(const CStringList & other)
{
	if (!other.IsEmpty())
	{
		CStringList<ValueType> lst;
		try
		{
			lst.ResetList();
			lst.m_imaginaryLastItem = move(lst.m_lastNode->next);
			auto tempPtr = other.m_firstNode;
			lst.m_firstNode->data = tempPtr->data;
			auto current = lst.m_firstNode;
			while (tempPtr->next->next)
			{
				tempPtr = tempPtr->next.get();
				current->next = make_unique<Node>(tempPtr->data, current, nullptr);
				current = current->next.get();
			}
			lst.m_imaginaryLastItem->prev = current;
			current->next = move(lst.m_imaginaryLastItem);
			lst.m_lastNode = current;
			lst.m_size = other.m_size;
		}
		catch (...)
		{
			throw;
		}
		Clear();
		ResetList();
		m_imaginaryLastItem = move(m_lastNode->next);
		m_imaginaryFirstItem->next = std::move(lst.m_imaginaryFirstItem->next);
		m_firstNode = m_imaginaryFirstItem->next.get();
		m_lastNode = lst.m_lastNode;
		m_imaginaryLastItem->prev = m_lastNode;
		m_lastNode->next = move(m_imaginaryLastItem);
		m_size = lst.m_size;
	}
	else
	{
		Clear();
	}
	return *this;
}

template <typename ValueType>
ValueType & CStringList<ValueType>::CIterator::operator*()const
{
	if (!m_node || (!m_node->next))
	{
		throw std::runtime_error("Iterator as invalid.");
	}

	return m_node->data;
}

template <typename ValueType>
typename CStringList<ValueType>::CIterator & CStringList<ValueType>::CIterator::operator++()
{
	if (!m_node || (!m_node->next && !m_isReverse) || (!m_node->prev && m_isReverse))
	{
		throw (std::runtime_error("Iterator has not icrementable."));
	}
	m_isReverse ? m_node = m_node->prev : m_node = m_node->next.get();

	return *this;
}

template <typename ValueType>
typename CStringList<ValueType>::CIterator & CStringList<ValueType>::CIterator::operator--()
{
	if (!m_node || (!m_node->prev && !m_isReverse) || (!m_node->next && m_isReverse))
	{
		throw (std::runtime_error("Iterator has not decrementable."));
	}
	m_isReverse ? m_node = m_node->next.get() : m_node = m_node->prev;

	return *this;
}

template <typename ValueType>
typename CStringList<ValueType>::CIterator CStringList<ValueType>::begin()
{
	return CIterator(m_firstNode);
}

template <typename ValueType>
typename CStringList<ValueType>::CIterator CStringList<ValueType>::end()
{
	return m_lastNode ? CIterator(m_lastNode->next.get()) : CIterator(m_imaginaryLastItem.get());
}

template <typename ValueType>
typename const CStringList<ValueType>::CIterator CStringList<ValueType>::cbegin()const
{
	return CIterator(m_firstNode);
}

template <typename ValueType>
typename const CStringList<ValueType>::CIterator CStringList<ValueType>::cend()const
{
	return CIterator(m_lastNode->next.get());
}

template <typename ValueType>
typename CStringList<ValueType>::CIterator CStringList<ValueType>::rbegin()
{
	return CIterator(m_lastNode, true);
}

template <typename ValueType>
typename CStringList<ValueType>::CIterator CStringList<ValueType>::rend()
{
	return CIterator(m_imaginaryFirstItem.get(), true);
}

template <typename ValueType>
typename const CStringList<ValueType>::CIterator CStringList<ValueType>::crbegin()const
{
	return CIterator(m_lastNode, true);
}

template <typename ValueType>
typename const CStringList<ValueType>::CIterator CStringList<ValueType>::crend()const
{
	return CIterator(m_imaginaryFirstItem.get(), true);
}

template <typename ValueType>
typename CStringList<ValueType>::CIterator CStringList<ValueType>::Insert(CIterator &iter, ValueType const &data)
{
	auto iterNode = iter.m_node;
	if (iterNode == m_firstNode)
	{
		AddToFront(data);
	}
	else if ((iterNode == m_lastNode->next.get()))
	{
		Append(data);
	}
	else
	{
		if (!iterNode)
		{
			throw invalid_argument("Iterator is not valid.");
		}
		unique_ptr<Node> newNode;
		try
		{
			newNode = make_unique<Node>(data, move(iterNode->prev)
				, move(make_unique<Node>(iterNode->data, nullptr, move(iterNode->next))));
		}
		catch (...)
		{
			if (newNode->prev)
			{
				iterNode->prev = move(newNode->prev);
			}
			if (newNode->next)
			{
				iterNode->next = move(newNode->next->next);
			}
			throw;
		}
		newNode->next->prev = newNode.get();
		iter.m_node = newNode->next.get();
		newNode->prev->next = move(newNode);
		++m_size;
	}
	return iter;
}

template <typename ValueType>
typename CStringList<ValueType>::CIterator CStringList<ValueType>::Erase(CIterator & iter)
{
	if (!(iter.m_node) || (IsEmpty()) || (iter.m_node == m_lastNode->next.get()))
	{
		throw runtime_error("Dont erase it, because iter is null.");
	}
	if (iter.m_node == m_firstNode)
	{
		if (m_size > 1)
		{
			m_imaginaryFirstItem->next = move(m_firstNode->next);
			m_firstNode = m_imaginaryFirstItem->next.get();
			m_firstNode->prev = m_imaginaryFirstItem.get();
			iter = begin();
		}
		else
		{
			ResetList();
			iter = end();
		}
	}
	else if (iter.m_node == m_lastNode)
	{
		m_imaginaryLastItem = move(m_lastNode->next);
		m_lastNode = m_lastNode->prev;
		m_lastNode->next = move(m_imaginaryLastItem);
		iter = m_lastNode->next.get();
	}
	else
	{
		auto next = move(iter.m_node->next);
		auto prev = iter.m_node->prev;
		next->prev = prev;
		prev->next = move(next);
		iter = prev->next.get();
	}
	--m_size;

	return iter;
}