#pragma once
#include "SudokuPuzzle.h"
#include "KnightsTourPuzzle.h"

class Solver;

class KnightsSudoku {
public:
	explicit KnightsSudoku(Solver* s);

	const KnightsTourPuzzle& knights_tour() const;
	const SudokuPuzzle& sudoku() const;

private:
	Solver* m_solver;
	KnightsTourPuzzle m_kt;
	SudokuPuzzle m_sp;
};
