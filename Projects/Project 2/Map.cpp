#include "Map.h"

Map::Map()
{
	head = nullptr;
	m_size = 0;
	
}

Map::Map(const Map& copy)
{

	Node* curr = copy.head;
	for (int i = 0; i < copy.size(); i++) {
		insert(curr->m_k, curr->m_v);
		curr = curr->next;
	}
	
}

Map::~Map()
{
	Node* curr = head;
	while (curr != nullptr) {
		Node* temp = curr;
		curr = curr->next;
		delete temp;
	}
}

Map& Map::operator=(const Map& equals)
{
	Node* curr = head;
	while (curr != nullptr) {
		Node* temp = curr;
		curr = curr->next;
		delete temp;
		m_size -= 1;
		}
	
	Node* cCurr = equals.head;
	for (int i = 0; i < equals.size(); i++) {
		insert(cCurr->m_k, cCurr->m_v);
		cCurr = cCurr->next;
	}

	return *this;
}

bool Map::empty() const
{
	if (m_size == 0)
		return true;
	return false;
}

int Map::size() const
{
	return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	Node* n = new Node{key, value};
	if (m_size == 0) {
		head = n;
		m_size += 1;
		return true;
	}
	Node* curr = head;
	while (curr->next!=nullptr) {
		if (curr->m_k == key) {
			return false;
		}
		curr=curr->next;
	}
		if (curr->m_k == key) {
		return false;
		}
		curr->next = n;
		n->prev = curr;
		m_size += 1;
		return true;
	
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	Node* curr = head;
	if (m_size == 0) {
		return false;
	}
	while (curr != nullptr) {
		if (curr->m_k == key) {
			curr->m_v = value;
			return true;
			
		}
		
		curr = curr->next;
		
	}
	
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	insert(key, value);
	update(key, value);
	return true;
}

bool Map::erase(const KeyType& key)
{
	if (!contains(key)) {
		return false;
	}
	Node* curr = head;

	if (head->m_k == key) {
		head = curr->next;
		delete curr;
		m_size -= 1;
		return true;
	}
	while (curr->next != nullptr) {
		if (curr->m_k == key) {
			curr->next->prev = curr->prev;
			curr->prev->next = curr->next;
			delete curr;
			m_size -= 1;
			return true;
		}
		curr = curr->next;
	}
	curr->prev->next = nullptr;
	delete curr;
	m_size -= 1;
	return true;
}

bool Map::contains(const KeyType& key) const
{
	Node* curr = head;
	while (curr != nullptr) {
		if (curr->m_k == key) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	if (!contains(key)) {
		return false;
	}
	Node* curr = head;
	while (curr != nullptr) {
		if (curr->m_k == key) {
			value = curr->m_v;
			return true;
		}
		curr = curr->next;
	}
	
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i < 0 || i >= size()) {
		return false;
	}
	Node* curr = head;
	for (int j = 0; j < size(); j++) {
		if (j == i) {
			key = curr->m_k;
			value = curr->m_v;
			return true;
		}
		curr = curr->next;
	}
	
}

void Map::swap(Map& other)
{
	Map temp = other;
	other = *this;
	*this = temp;
}

bool combine(const Map& m1, const Map& m2, Map& result)
{
	for (int i = 0; i < m1.size(); i++) {
		KeyType param_key;
		ValueType param_value;
		m1.get(i, param_key, param_value);
		result.insert(param_key, param_value);
	}
	for (int j = 0; j < m2.size(); j++) {
		KeyType param_key2;
		ValueType param_value2;
		m2.get(j, param_key2, param_value2);
		if (!(result.contains(param_key2))) {
			result.insert(param_key2, param_value2);
		}
		ValueType m1val;
		result.get(param_key2, m1val);
		if (param_value2 != m1val) {
			return false;
		}
	}
	return true;
}

void reassign(const Map& m, Map& result)
{
	Map resultempty;
	result = resultempty;
	if (m.size() == 1 || m.size() == 0) {
		result = m;
	}

	else{
		KeyType headk, tailk;
		ValueType headv, tailv;
		m.get(0, headk, headv);
		m.get(m.size() - 1, tailk, tailv);
		for (int i = 0; i < m.size() - 1; i++) {
			KeyType param_key, param_key2;
			ValueType param_val, param_val2;

			m.get(i, param_key, param_val);
			m.get(i + 1, param_key2, param_val2);
			result.insert(param_key, param_val2);
		}
		result.insert(tailk, headv);
	}

}
