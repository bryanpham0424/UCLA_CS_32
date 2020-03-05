#include "Map.h"

Map::Map()
{
	size_of_MapData = 0;
}

bool Map::empty() const
{
	return size_of_MapData == 0;
}

int Map::size() const
{
	return size_of_MapData;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i < size_of_MapData; i++) {
		if (MapData[i].m_k == key) {
			return false;
		}
	}
	MapData[size_of_MapData].m_k = key;
	MapData[size_of_MapData].m_v = value;
	size_of_MapData += 1;
	return true;
	
	
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i < size_of_MapData; i++) {
		if (MapData[i].m_k == key) {
			MapData[i].m_v = value;
			return true;
		}
		
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	if (update(key, value) || insert(key, value))
		return true;
	else
		return false;
}

bool Map::erase(const KeyType& key)
{
	Node reset_node;
	for (int i = 0; i < size_of_MapData; i++) {
		if (MapData[i].m_k == key) {
			for (int j = i; j < size_of_MapData; j++) {
				MapData[j] = MapData[j + 1];
				
			}
			MapData[size_of_MapData] = reset_node;
			return true;
		}
		
	}
	
	return false;
	
}

bool Map::contains(const KeyType& key) const 
{
	for (int i = 0; i < size_of_MapData; i++) {
		if (MapData[i].m_k == key)
			return true;
		
	}
	return false;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	for (int i = 0; i< size_of_MapData; i++) {
		if (MapData[i].m_k == key) {
			value = MapData[i].m_v;
			return true;
		}
	

	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const 
{
	if (0 <= i && i < DEFAULT_MAX_ITEMS) {
		key = MapData[i].m_k;
		value = MapData[i].m_v;
		return true;
	}
	else
		return false;
}

void Map::swap(Map& other)
{
	int tempsize = size_of_MapData;
	size_of_MapData = other.size_of_MapData;
	other.size_of_MapData = tempsize;

	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
		
		Node temp;
		temp = MapData[i];
		MapData[i] = other.MapData[i];
		other.MapData[i] = temp;

	}
	
}
