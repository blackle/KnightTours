#pragma once
#include "NumberedCell.h"

class DigitCell : public NumberedCell
{
public:
	explicit DigitCell(Solver* s) : NumberedCell(10, s) {}
	static int length() { return 10; }
};
