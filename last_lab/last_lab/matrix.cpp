#include "matrix.h"

Matrix::Matrix(uint32_t rows, uint32_t columns)
	: std::vector<Row>(rows, Row(columns))
	, rows_(rows)
	, columns_(columns)
{

}

Matrix::Matrix(std::initializer_list<Row> matrix)
	: std::vector<Row>(matrix)
	, rows_(matrix.size())
	, columns_(matrix.begin()->size())
{

}

const Matrix Matrix::operator*(const Matrix& obj) const
{
	Matrix res(rows_, obj.columns_);

	for (uint32_t j = 0; j < res.rows_; j++)
	{
		for (uint32_t i = 0; i < res.columns_; i++)
		{
			for (uint32_t k = 0; k < columns_; k++)
			{
				res[j][i] += (*this)[j][k] * obj[k][i];
			}
		}
	}

	return res;
}