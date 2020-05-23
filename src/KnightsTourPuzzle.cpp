#include "KnightsTourPuzzle.h"
#include "OneHotConstraint.h"

KnightsTourPuzzle::KnightsTourPuzzle(Solver* s)
	: m_solver(s)
{
	for (size_t i = 0; i < ChessCell::length(); i++) {
		ChessCell cell(m_solver);
		m_cells.push_back(cell);
	}
	//each cell unique
	for (size_t i = 0; i < ChessCell::length(); i++) {
		VariableList items;
		for (auto cell = m_cells.begin(); cell != m_cells.end(); cell++) {
			items.push_back(cell->at(i));
		}
		OneHotConstraint::commander(m_solver, items, 3); 
	}
	//knights tour jump constraint
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			for (size_t t = 0; t < ChessCell::length(); t++) {
				constrain_knight_movement(i,j,t,t+1);
				constrain_knight_movement(i,j,t,t-1);
			}
		}
	}
}

ChessCell KnightsTourPuzzle::at(size_t i, size_t j) const {
	return m_cells.at(i*9 + j);
}

std::ostream& operator<<(std::ostream& os, const KnightsTourPuzzle& kt)
{
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			os << " " << kt.at(i, j);
		}
		os << std::endl;
	}
	return os;
}

void KnightsTourPuzzle::constrain_knight_movement(int i, int j, int t, int tnew) {
	if (tnew == (int)ChessCell::length() || tnew < 0) return;
	VariableList clause;
	for (int b = 0; b < 8; b++) {
		int xsgn = (b & 1) == 0 ? -1 : 1;
		int ysgn = (b & 2) == 0 ? -1 : 1;
		int xstp = (b & 4) == 0 ? 1 : 2;
		int ystp = (b & 4) == 0 ? 2 : 1;
		int x = i + xstp*xsgn;
		int y = j + ystp*ysgn;
		if (x < 0 || x >= 9) continue;
		if (y < 0 || y >= 9) continue;
		clause.push_back(at(x,y).at(tnew));
	}
	clause.push_back(~at(i,j).at(t));
	m_solver->add_clause(clause);
}
