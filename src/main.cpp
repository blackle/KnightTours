#include <assert.h>
#include "Solver.h"
#include "KnightsSudoku.h"

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	Solver solver;
	KnightsSudoku ks(&solver);
	// ks.sudoku().at(0,0).assume(1);
	// ks.knights_tour().at(0,0).assume(1);
	// ks.knights_tour().at(2,2).assume(17);
	// ks.knights_tour().at(6,6).assume(65);
	// ks.knights_tour().at(5,3).assume(33);
	// ks.knights_tour().at(3,5).assume(49);
	// ks.knights_tour().at(8,8).assume(81);
	// ks.knights_tour().at(1,1).assume(5);
	// ks.knights_tour().at(0,5).assume(40);
	// ks.knights_tour().at(5,0).assume(30);
	// ks.knights_tour().at(4,1).assume(46);
	// ks.knights_tour().at(4,5).assume(48);
	// ks.knights_tour().at(7,3).assume(13);
	// ks.knights_tour().at(6,5).assume(10);
	// ks.knights_tour().at(0,4).assume(35);
	// ks.knights_tour().at(8,4).assume(69);
	// ks.knights_tour().at(4,8).assume(11);
	// ks.knights_tour().at(4,0).assume(3);
	// ks.knights_tour().at(4,4).assume(13);

	std::cerr << "variables: " << solver.var_count() << std::endl;
	std::cerr << "clauses: " << solver.clause_count() << std::endl;
	CMSat::lbool ret = solver.solve();
	assert(ret == CMSat::l_True);
	std::cout << ks.knights_tour() << std::endl;
	std::cout << ks.sudoku() << std::endl;
	solver.exclude_solution();
	ret = solver.solve();
	assert(ret == CMSat::l_True);
	std::cout << ks.knights_tour() << std::endl;
	std::cout << ks.sudoku() << std::endl;

	return 0;
}
