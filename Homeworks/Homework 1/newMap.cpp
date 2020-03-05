#include "newMap.h"


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
	for (int i = 0; i < size_of_MapData; i++) {
		if (MapData[i].m_k == key) {
			value = MapData[i].m_v;
			return true;
		}


	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (0 <= i && i < m_maxVal) {
		key = MapData[i].m_k;
		value = MapData[i].m_v;
		return true;
	}
	else
		return false;
}

void Map::swap(Map& other)
{
	Map temp = other;
	other = *this;
	*this = temp;

}

Map::Map(int max_val)
{
	if (max_val < 0) {
		std::cerr << "Nagative values are not acceptable";
	}
	MapData = new Node[max_val];
	size_of_MapData = 0;
	m_maxVal = max_val;
}

Map::Map(const Map& copy)
{
	size_of_MapData = copy.size_of_MapData;
	m_maxVal = copy.m_maxVal;
	MapData = new Node[copy.m_maxVal];
	for (int i = 0; i < copy.m_maxVal; i++) {
		MapData[i] = copy.MapData[i];
	}
}

Map::~Map()
{
	delete [] MapData;
}

Map& Map::operator=(const Map& equals)
{
	delete[] MapData;
	MapData = new Node[equals.m_maxVal];
	size_of_MapData = equals.size_of_MapData;
	m_maxVal = equals.m_maxVal;
	
	for (int i = 0; i < equals.m_maxVal; i++) {
		MapData[i] = equals.MapData[i];
	}
	return *this;
}
