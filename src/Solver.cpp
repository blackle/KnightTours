#include "Solver.h"

Solver::Solver()
	: m_clause_count(0)
{
	m_sat_solver.set_num_threads(10);
}

Variable Solver::new_var()
{
	m_sat_solver.new_var();
	return Variable(m_sat_solver.nVars()-1, false);
}

VariableList Solver::new_vars(const size_t n)
{
	size_t initial = m_sat_solver.nVars();
	m_sat_solver.new_vars(n);

	VariableList vars;
	for (size_t i = initial; i < initial+n; i++) {
		vars.push_back(Variable(i, false));
	}
	return vars;
}

unsigned Solver::var_count() const
{
	return m_sat_solver.nVars();
}

void Solver::add_clause(const VariableList& vars)
{
	m_clause_count++;
	m_sat_solver.add_clause(vars);
}

unsigned Solver::clause_count() const
{
	return m_clause_count;
}

void Solver::assume(const Variable& var)
{
	m_assumptions.push_back(var);
}

CMSat::lbool Solver::solve()
{
	auto retval = m_sat_solver.solve(&m_assumptions);
	m_sat_solver.print_stats();
	return retval;
}

const std::vector<CMSat::lbool>& Solver::get_model() const
{
	return m_sat_solver.get_model();
}

void Solver::exclude_solution() {
	VariableList vars;
	auto model = get_model();
	for (unsigned i = 0; i < var_count(); i++) {
		vars.push_back(Variable(i, model[i] == CMSat::l_True));
	}
	add_clause(vars);
}
