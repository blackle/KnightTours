#include "SudokuCell.h"
#include "OneHotConstraint.h"
#include "Solver.h"
#include <assert.h>
#include <iomanip>

SudokuCell::SudokuCell(Solver* s)
	: m_solver(s)
	, m_vars(s->new_vars(length()))
{
	OneHotConstraint::naive(m_solver, all()); //todo: is this the most efficient encoding
}

Variable SudokuCell::at(size_t i) const
{
	return m_vars.at(i);
}

const VariableList& SudokuCell::all() const
{
	return m_vars;
}

uint8_t SudokuCell::to_int() const
{
	auto model = m_solver->get_model();
	for (size_t i = 0; i < length(); i++) {
		if (model[m_vars[i].var()] == CMSat::l_True) {
			return i;
		}
	}
	return -1;
}

void SudokuCell::assume(uint8_t val) const
{
	for (size_t i = 0; i < length(); i++) {
		m_solver->assume(at(i) ^ (i != val));
	}
}

Solver* SudokuCell::solver() const
{
	return m_solver;
}

std::ostream& operator<<(std::ostream& os, const SudokuCell& cell)
{
	os << (int)cell.to_int() + 1;
	return os;
}
