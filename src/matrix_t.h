/*
 * matrix_t.h
 *
 *  Created on: 24.03.2019
 *      Author: Tim
 */

#ifndef MATRIX_T_H_
#define MATRIX_T_H_

class matrix_t
{
private:
	int internal_buffer[4][4];
public:
	matrix_t& operator*(matrix_t& op)
	{
		return *this;
	}

	matrix_t& operator+(matrix_t& op)
	{
		return *this;
	}
};

#endif /* MATRIX_T_H_ */
