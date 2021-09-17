#pragma once

/*
  矩阵类


*/

#define  ERROR -1024.1024f


class Matrix
{
private:
	int		row;						// 矩阵行数
	int		column;						// 矩阵列数
	double* data;						// 矩阵数组指针

public:
	 Matrix();							// 默认构造函数 构造 1 * 1 矩阵
	 Matrix(int r, int c);				// 构造 r 行 c 列矩阵
	~Matrix();							// 析构函数

public:
	void	transposeMatrix(Matrix* out);						// 转置矩阵
	bool    inverseMatrix(Matrix* out);							// 逆矩阵
	void	adjointMatrix(Matrix* out);							// 伴随矩阵

		
	void    characteristicValue();											// 求 矩阵特征值
	void	Eig(Matrix *A, Matrix *eigenVector, Matrix *eigenValue);		// 求 对应 特征值的特征向量

	bool    multiply(Matrix& mat,Matrix* out);								// 矩阵乘法 左乘


public:
	bool    assign(double* value);								// 矩阵数组赋值
	void    travel();											// 矩阵遍历
	int     getRow() { return this->row; }						// 获取矩阵行数
	int     getColumn() { return this->column; }				// 获取矩阵列数

public:
	static double	determinant(Matrix& mat);					// 矩阵对应的行列式
	void            cofactor(int r, int c, Matrix* out);		// 矩阵 mat(r,w) 的余子式

private:

/* 
	函数功能：对一个方阵A进行QR分解
	输入：需要分解的矩阵A、分解后的正交矩阵Q和上三角矩阵R
	输出：无
 */
	void   QR(Matrix *A, Matrix *Q, Matrix *R);


/*
		函数功能：矩阵2阶范数
*/
	double norm2Matrix(Matrix* mat);							// 求矩阵范数2
	void   reSet(int r, int c);									// 矩阵数据重置为0

};

