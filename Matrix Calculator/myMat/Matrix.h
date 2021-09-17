#pragma once

/*
  ������


*/

#define  ERROR -1024.1024f


class Matrix
{
private:
	int		row;						// ��������
	int		column;						// ��������
	double* data;						// ��������ָ��

public:
	 Matrix();							// Ĭ�Ϲ��캯�� ���� 1 * 1 ����
	 Matrix(int r, int c);				// ���� r �� c �о���
	~Matrix();							// ��������

public:
	void	transposeMatrix(Matrix* out);						// ת�þ���
	bool    inverseMatrix(Matrix* out);							// �����
	void	adjointMatrix(Matrix* out);							// �������

		
	void    characteristicValue();											// �� ��������ֵ
	void	Eig(Matrix *A, Matrix *eigenVector, Matrix *eigenValue);		// �� ��Ӧ ����ֵ����������

	bool    multiply(Matrix& mat,Matrix* out);								// ����˷� ���


public:
	bool    assign(double* value);								// �������鸳ֵ
	void    travel();											// �������
	int     getRow() { return this->row; }						// ��ȡ��������
	int     getColumn() { return this->column; }				// ��ȡ��������

public:
	static double	determinant(Matrix& mat);					// �����Ӧ������ʽ
	void            cofactor(int r, int c, Matrix* out);		// ���� mat(r,w) ������ʽ

private:

/* 
	�������ܣ���һ������A����QR�ֽ�
	���룺��Ҫ�ֽ�ľ���A���ֽ�����������Q�������Ǿ���R
	�������
 */
	void   QR(Matrix *A, Matrix *Q, Matrix *R);


/*
		�������ܣ�����2�׷���
*/
	double norm2Matrix(Matrix* mat);							// �������2
	void   reSet(int r, int c);									// ������������Ϊ0

};

