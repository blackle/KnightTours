#include "KnightsTourPuzzle.h"
#include "OneHotConstraint.h"

KnightsTourPuzzle::KnightsTourPuzzle(int width, int height, Solver* s)
	: m_width(width)
	, m_height(height)
	, m_solver(s)
{
	for (int i = 0; i < m_width*m_height; i++) {
		NumberedCell cell(m_width*m_height, m_solver);
		m_cells.push_back(cell);
	}
	//each cell unique
	for (int i = 0; i < m_width*m_height; i++) {
		VariableList items;
		for (auto cell = m_cells.begin(); cell != m_cells.end(); cell++) {
			items.push_back(cell->at(i));
		}
		OneHotConstraint::commander(m_solver, items, 2); 
	}
	//knights tour jump constraint
	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < m_height; j++) {
			for (int t = 0; t < m_width*m_height-4; t++) {
				constrain_knight_movement(i,j,t,t+1);
				constrain_knight_movement(i,j,t,t-1);
			}
		}
	}
}

int KnightsTourPuzzle::width() const
{
	return m_width;
}

int KnightsTourPuzzle::height() const
{
	return m_height;
}

NumberedCell KnightsTourPuzzle::at(int i, int j) const {
	return m_cells.at(i + j*m_width);
}

std::ostream& operator<<(std::ostream& os, const KnightsTourPuzzle& kt)
{
	for (int j = 0; j < kt.height(); j++) {
		for (int i = 0; i < kt.width(); i++) {
			os << " " << kt.at(i, j);
		}
		os << std::endl;
	}
	return os;
}

void KnightsTourPuzzle::constrain_knight_movement(int i, int j, int t, int tnew) {
	// tnew = (tnew+m_width*m_height)%(m_width*m_height); //uncomment for closed tour
	if (tnew == m_width*m_height || tnew < 0) return;
	VariableList clause;
	for (int b = 0; b < 8; b++) {
		int xsgn = (b & 1) == 0 ? -1 : 1;
		int ysgn = (b & 2) == 0 ? -1 : 1;
		int xstp = (b & 4) == 0 ? 1 : 2;
		int ystp = (b & 4) == 0 ? 2 : 1;
		int x = i + xstp*xsgn;
		int y = j + ystp*ysgn;
		if (x < 0 || x >= m_width) continue;
		if (y < 0 || y >= m_height) continue;
		clause.push_back(at(x,y).at(tnew));
	}
	clause.push_back(~at(i,j).at(t));
	m_solver->add_clause(clause);
}
