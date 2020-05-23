#include <assert.h>
#include "Solver.h"
#include "SudokuPuzzle.h"

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	Solver solver;
	SudokuPuzzle puzzle(&solver);

	std::cerr << "variables: " << solver.var_count() << std::endl;
	std::cerr << "clauses: " << solver.clause_count() << std::endl;
	CMSat::lbool ret = solver.solve();
	assert(ret == CMSat::l_True);
	std::cout << puzzle << std::endl;

	return 0;
}
