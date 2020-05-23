#include "SudokuPuzzle.h"
#include "OneHotConstraint.h"

SudokuPuzzle::SudokuPuzzle(Solver* s)
	: m_solver(s)
{
	for (size_t i = 0; i < SudokuCell::length(); i++) {
		for (size_t j = 0; j < SudokuCell::length(); j++) {
			SudokuCell cell(m_solver);
			m_cells.push_back(cell);
		}
	}

	//constraints
	for (size_t i = 0; i < SudokuCell::length(); i++) {
		std::vector<SudokuCell> column;
		std::vector<SudokuCell> row;
		std::vector<SudokuCell> box;
		for (size_t j = 0; j < SudokuCell::length(); j++) {
			column.push_back(at(i,j));
			row.push_back(at(j,i));
			size_t box_x = (i % 3)*3 + (j % 3);
			size_t box_y = (i / 3)*3 + (j / 3);
			box.push_back(at(box_x,box_y));
		}
		constrain_cells(column);
		constrain_cells(row);
		constrain_cells(box);
	}
}

SudokuCell SudokuPuzzle::at(size_t i, size_t j) const {
	return m_cells.at(i*SudokuCell::length() + j);
}

std::ostream& operator<<(std::ostream& os, const SudokuPuzzle& sp)
{
	for (size_t i = 0; i < SudokuCell::length(); i++) {
		if (i % 3 == 0) os << " -------------------------" << std::endl;
		for (size_t j = 0; j < SudokuCell::length(); j++) {
			if (j % 3 == 0) os << " |";
			os << " " << sp.at(i, j);
		}
		os << " |" << std::endl;
	}
	os << " -------------------------" << std::endl;
	return os;
}

void SudokuPuzzle::constrain_cells(const std::vector<SudokuCell>& cells)
{
	for (size_t i = 0; i < SudokuCell::length(); i++) {
		VariableList items;
		for (auto cell = cells.begin(); cell != cells.end(); cell++) {
			items.push_back(cell->at(i));
		}
		OneHotConstraint::naive(m_solver, items); 
	}
}
