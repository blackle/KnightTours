#include "OneHotConstraint.h"
#include "Solver.h"

void OneHotConstraint::at_least_one(Solver* solver, const VariableList& vars)
{
	solver->add_clause(vars);
}

void OneHotConstraint::at_most_one(Solver* solver, const VariableList& vars)
{
	for (size_t i = 0; i < vars.size(); i++) {
		for (size_t j = i+1; j < vars.size(); j++) {
			solver->add_clause({~vars[i], ~vars[j]});
		}
	}
}

void OneHotConstraint::naive(Solver* solver, const VariableList& vars)
{
	at_most_one(solver, vars);
	at_least_one(solver, vars);
}

void OneHotConstraint::commander(Solver* solver, const VariableList& vars, size_t group_size)
{
	at_least_one(solver, vars);

	if (vars.size() == 1) {
		return;
	} else if (vars.size() < group_size) {
		at_most_one(solver, vars);
		return;
	}
	// assert(vars.size() % group_size == 0);

	VariableList treevars;
	int groups = 0;
	for (size_t i = 0; i < vars.size()/group_size; i++) {
		groups++;
		int idx = group_size*i;
		VariableList group(&vars[idx], &vars[idx]+group_size);
		at_most_one(solver, group);

		auto treevar = commander_variable(solver, group);
		treevars.push_back(treevar);
	}
	for (size_t i = group_size*groups; i < vars.size(); i++) {
		treevars.push_back(vars[i]);
	}

	commander(solver, treevars, group_size);
}

Variable OneHotConstraint::commander_variable(Solver* solver, const VariableList& vars)
{
	auto var = solver->new_var();

	//(a or b or c ...) => var
	for (size_t i = 0; i < vars.size(); i++) {
		solver->add_clause({~vars[i], var});
	}

	//var => (a or b or c ...)
	VariableList clause(vars);
	clause.push_back(~var);
	solver->add_clause(clause);

	return var;
}
