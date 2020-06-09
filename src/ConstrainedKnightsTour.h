#pragma once
#include "DigitBoard.h"
#include "KnightsTourPuzzle.h"

class Solver;

class ConstrainedKnightsTour {
public:
	explicit ConstrainedKnightsTour(int width, int height, Solver* s);

	const KnightsTourPuzzle& knights_tour() const;
	const DigitBoard& digits_1() const;
	const DigitBoard& digits_2() const;

private:
	Solver* m_solver;
	const int m_width;
	const int m_height;
	KnightsTourPuzzle m_kt;
	DigitBoard m_db1;
	DigitBoard m_db2;
	void constrain(int x, int y);
};
