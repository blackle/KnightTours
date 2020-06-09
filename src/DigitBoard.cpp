#include "DigitBoard.h"
#include "OneHotConstraint.h"

DigitBoard::DigitBoard(int width, int height, Solver* s)
	: m_width(width)
	, m_height(height)
	, m_solver(s)
{
	for (int i = 0; i < width*height; i++) {
		DigitCell cell(m_solver);
		m_cells.push_back(cell);
	}
}

int DigitBoard::width() const
{
	return m_width;
}

int DigitBoard::height() const
{
	return m_height;
}

DigitCell DigitBoard::at(int i, int j) const {
	return m_cells.at(i + j*m_width);
}

std::ostream& operator<<(std::ostream& os, const DigitBoard& db)
{
	for (int j = 0; j < db.height(); j++) {
		for (int i = 0; i < db.width(); i++) {
			os << " " << (db.at(i, j).to_int() - 1);
		}
		os << std::endl;
	}
	return os;
}

