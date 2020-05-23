#pragma once
#include <cryptominisat5/cryptominisat.h>
#include "Variable.h"
#include "OneHotConstraint.h"
#include "Solver.h"
#include <vector>
#include <iostream>
#include <assert.h>
#include <iomanip>

template<int L>
class NumberedCell
{
public:
	explicit NumberedCell(Solver* s);

	Variable at(size_t i) const;
	const VariableList& all() const;
	static size_t length() { return L; }

	uint8_t to_int() const;
	void assume(uint8_t val) const;

	Solver* solver() const;

	template<int I>
	friend std::ostream& operator<<(std::ostream& os, const NumberedCell<I>& cell);

private:
	Solver* m_solver;
	VariableList m_vars;
};

template<int L>
NumberedCell<L>::NumberedCell(Solver* s)
	: m_solver(s)
	, m_vars(s->new_vars(length()))
{
	OneHotConstraint::commander(m_solver, all(), 3); //todo: is this the most efficient encoding
}

template<int L>
Variable NumberedCell<L>::at(size_t i) const
{
	return m_vars.at(i);
}

template<int L>
const VariableList& NumberedCell<L>::all() const
{
	return m_vars;
}

template<int L>
uint8_t NumberedCell<L>::to_int() const
{
	auto model = m_solver->get_model();
	for (size_t i = 0; i < length(); i++) {
		if (model[m_vars[i].var()] == CMSat::l_True) {
			return i + 1;
		}
	}
	return -1;
}

template<int L>
void NumberedCell<L>::assume(uint8_t val) const
{
	val--;
	for (size_t i = 0; i < length(); i++) {
		m_solver->assume(at(i) ^ (i != val));
	}
}

template<int L>
Solver* NumberedCell<L>::solver() const
{
	return m_solver;
}

template<int L>
std::ostream& operator<<(std::ostream& os, const NumberedCell<L>& cell)
{
	os << std::setw(L > 10 ? 3 : 1) << (int)cell.to_int();
	return os;
}
