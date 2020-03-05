#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <string>


using KeyType = std::string;
using ValueType = double;

class Map {
public:
    Map();
    Map(const Map& copy);
    ~Map();
    Map& operator=(const Map& equals);
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
private:
	struct Node {
		KeyType m_k;
		ValueType m_v;
        Node* next = nullptr;
        Node* prev = nullptr;
	};
    Node* head;
    int m_size;
};

bool combine(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);
#endif MAP_H