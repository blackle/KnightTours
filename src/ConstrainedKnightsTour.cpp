#include "ConstrainedKnightsTour.h"

ConstrainedKnightsTour::ConstrainedKnightsTour(int width, int height, Solver* s)
	: m_solver(s)
	, m_width(width)
	, m_height(height)
	, m_kt(width, height, s)
	, m_db1(width, height, s)
	, m_db2(width, height, s)
{
	//tie decimals to positions
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int d = 0; d < width*height; d++) {
				int d1 = (d+1) % 10;
				int d2 = ((d+1) / 10) % 10;
				// s->add_clause({~m_db1.at(i,j).at(d1), m_kt.at(i,j).at(d)});
				s->add_clause({m_db1.at(i,j).at(d1), ~m_kt.at(i,j).at(d)});
				// s->add_clause({~m_db2.at(i,j).at(d2), m_kt.at(i,j).at(d)});
				s->add_clause({m_db2.at(i,j).at(d2), ~m_kt.at(i,j).at(d)});
			}
			for (int dd = 0; dd < DigitCell::length(); dd++) {
				VariableList c1;
				VariableList c2;
				c1.push_back(~m_db1.at(i,j).at(dd));
				c2.push_back(~m_db2.at(i,j).at(dd));
				for (int dk = 0; dk < width*height; dk++) {
					int d1 = (dk+1) % 10;
					int d2 = ((dk+1) / 10) % 10;
					if (d1 == dd) c1.push_back(m_kt.at(i,j).at(dk));
					if (d2 == dd) c2.push_back(m_kt.at(i,j).at(dk));
				}
				s->add_clause(c1);
				s->add_clause(c2);
			}
		}
	}
	//adjacent cells cannot share a digit
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			constrain(i, j);
		}
	}
}

void ConstrainedKnightsTour::constrain(int x, int y) {
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 1; j++) {
			int offset = j*2-1;
			int xx = x + (i==0)*offset;
			int yy = y + (i==1)*offset;
			if (xx < 0 || xx >= m_width || yy < 0 || yy >= m_height) continue;

			//skip corners
			if ((xx==0&&yy==0)|(x==0&&y==0)) continue;
			if ((xx==m_width-1&&yy==0)|(x==m_width-1&&y==0)) continue;
			if ((xx==0&&yy==m_height-1)|(x==0&&y==m_height-1)) continue;

			for (int d = 0; d < DigitCell::length(); d++) {
				m_solver->add_clause({~m_db1.at(x,y).at(d), ~m_db1.at(xx,yy).at(d)});
				if (d != 0) {
					m_solver->add_clause({~m_db2.at(x,y).at(d), ~m_db2.at(xx,yy).at(d)});
					m_solver->add_clause({~m_db1.at(x,y).at(d), ~m_db2.at(xx,yy).at(d)});
				}
			}
		}
	}
}

const KnightsTourPuzzle& ConstrainedKnightsTour::knights_tour() const
{
	return m_kt;
}

const DigitBoard& ConstrainedKnightsTour::digits_1() const
{
	return m_db1;
}

const DigitBoard& ConstrainedKnightsTour::digits_2() const
{
	return m_db2;
}
