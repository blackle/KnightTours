#include "NumberedCell.h"
#include "OneHotConstraint.h"
#include <iomanip>

NumberedCell::NumberedCell(int len, Solver* s)
	: m_length(len)
	, m_solver(s)
	, m_vars(s->new_vars(len))
{
	OneHotConstraint::commander(m_solver, all(), 2); //todo: is this the most efficient encoding
}

Variable NumberedCell::at(int i) const
{
	return m_vars.at(i);
}

const VariableList& NumberedCell::all() const
{
	return m_vars;
}

int NumberedCell::length() const
{
	return m_length;
}

int NumberedCell::to_int() const
{
	auto model = m_solver->get_model();
	for (int i = 0; i < length(); i++) {
		if (model[m_vars[i].var()] == CMSat::l_True) {
			return i + 1;
		}
	}
	return -1;
}

void NumberedCell::assume(int val) const
{
	val--;
	for (int i = 0; i < length(); i++) {
		m_solver->assume(at(i) ^ ((int)i != val));
	}
}

Solver* NumberedCell::solver() const
{
	return m_solver;
}

std::ostream& operator<<(std::ostream& os, const NumberedCell& cell)
{
	os << std::setw(cell.length() > 10 ? 2 : 1) << cell.to_int();
	return os;
}
