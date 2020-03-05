#include "History.h"
#include "globals.h"

#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
	m_h_rows = nRows;
	m_h_cols = nCols;

	for (int i = 1; i <= m_h_rows; i++) {
		for (int j = 1; j <= m_h_cols; j++) {
			m_h_grid[i][j] = '.';
		}
	}
	
}

bool History::record(int r, int c)
{
	if (!(r >= 1 && r <= m_h_rows && c >= 1 && c <= m_h_cols)) {
	return false;
	}

	if (m_h_grid[r][c] == '.') {
		m_h_grid[r][c] = 'A';
	}
	else if (m_h_grid[r][c] < 'Z') {
		m_h_grid[r][c] += 1;
	}
	return true;
}

void History::display() const
{
	clearScreen();

	for (int i = 1; i <= m_h_rows; i++) {
		for (int j = 1; j <= m_h_cols; j++) {
			cout << m_h_grid[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
