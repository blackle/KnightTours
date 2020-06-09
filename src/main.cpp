#include <assert.h>
#include "Solver.h"
#include "ConstrainedKnightsTour.h"

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	Solver solver;
	ConstrainedKnightsTour cks(8, 8, &solver);
	cks.knights_tour().at(0,0).assume(8*8);
	cks.knights_tour().at(0,7).assume(8*8-1);
	cks.knights_tour().at(7,0).assume(8*8-2);

	std::cerr << "variables: " << solver.var_count() << std::endl;
	std::cerr << "clauses: " << solver.clause_count() << std::endl;
	CMSat::lbool ret = solver.solve();
	assert(ret == CMSat::l_True);
	std::cout << cks.knights_tour() << std::endl;
	//assert that there's no second solution
	solver.exclude_solution();
	ret = solver.solve();
	assert(ret == CMSat::l_False);

	return 0;
}
