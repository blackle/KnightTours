#include "KnightsSudoku.h"

KnightsSudoku::KnightsSudoku(Solver* s)
	: m_solver(s)
	, m_kt(s)
	, m_sp(s)
{
	for (size_t i = 0; i < SudokuCell::length(); i++) {
		for (size_t j = 0; j < SudokuCell::length(); j++) {
			for (size_t t = 0; t < SudokuCell::length(); t++) {
				VariableList clause;
				clause.push_back(~m_sp.at(i,j).at(t));
				for (size_t s = 0; s < SudokuCell::length(); s++) {
					clause.push_back(m_kt.at(i,j).at(s*SudokuCell::length()+t));
				}
				s->add_clause(clause);
			}
			for (size_t t = 0; t < ChessCell::length(); t++) {
				s->add_clause({~m_kt.at(i,j).at(t), m_sp.at(i,j).at(t % SudokuCell::length())});
			}
		}
	}
}

const KnightsTourPuzzle& KnightsSudoku::knights_tour() const
{
	return m_kt;
}

const SudokuPuzzle& KnightsSudoku::sudoku() const
{
	return m_sp;
}
