#ifndef HISTORY_H
#define HISTORY_H

#include "globals.h"

class History {
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;

private:
	int m_h_rows;
	int m_h_cols;
	char m_h_grid[MAXROWS][MAXCOLS];
};


#endif