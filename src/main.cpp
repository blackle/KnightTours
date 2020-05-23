#include <assert.h>
#include "Solver.h"
#include "SudokuPuzzle.h"

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	Solver solver;
	SudokuPuzzle puzzle(&solver);

	puzzle.at(0,3).assume(8);
	puzzle.at(0,5).assume(1);
	puzzle.at(1,7).assume(4);
	puzzle.at(1,8).assume(3);
	puzzle.at(2,0).assume(5);
	puzzle.at(3,4).assume(7);
	puzzle.at(3,6).assume(8);
	puzzle.at(4,6).assume(1);
	puzzle.at(5,1).assume(2);
	puzzle.at(5,4).assume(3);
	puzzle.at(6,0).assume(6);
	puzzle.at(6,7).assume(7);
	puzzle.at(6,8).assume(5);
	puzzle.at(7,2).assume(3);
	puzzle.at(7,3).assume(4);
	puzzle.at(8,3).assume(2);
	puzzle.at(8,6).assume(6);

	std::cerr << "variables: " << solver.var_count() << std::endl;
	std::cerr << "clauses: " << solver.clause_count() << std::endl;
	CMSat::lbool ret = solver.solve();
	assert(ret == CMSat::l_True);
	std::cout << puzzle << std::endl;
	solver.exclude_solution();
	ret = solver.solve();
	assert(ret == CMSat::l_True);
	std::cout << puzzle << std::endl;

	return 0;
}
