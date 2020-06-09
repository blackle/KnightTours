#pragma once
#include "Variable.h"
#include "Solver.h"
#include <iostream>

class NumberedCell
{
public:
	explicit NumberedCell(int len, Solver* s);

	Variable at(int i) const;
	const VariableList& all() const;
	int length() const;

	int to_int() const;
	void assume(int val) const;

	Solver* solver() const;

	friend std::ostream& operator<<(std::ostream& os, const NumberedCell& cell);

private:
	const int m_length;
	Solver* m_solver;
	VariableList m_vars;
};
