#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


Matrix::Matrix()
{
	this->row	 = 1;
	this->column = 1;
	this->data	 = new double[1];

	this->data[0] = 0;
}

Matrix::Matrix(int r, int c)
{
	this->row	 = r;
	this->column = c;
	this->data   = new double[r*c]; 
	
	int matrix_num = r * c;
	for (int i = 0; i < matrix_num; i++)
		this->data[i] = 0;
}


Matrix::~Matrix()
{
	delete this->data;
	this->data = NULL;
}

void Matrix::transposeMatrix(Matrix * out)							// 转置矩阵
{
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			*(out->data + i*row + j) = *(data + (j*column) + i);
		}
	}
}



bool Matrix::multiply(Matrix & mat,Matrix* out) {

	if ((row * column) == 1) {
		double temp = *(this->data);
		double* result = new double[mat.row  * mat.column];

		for (int i = 0; i < mat.row*mat.column; i++) {
			*(result+ i) = *(mat.data) * temp;
		}
		out->assign(result);
		return true;
	}

	if (this->column != mat.row) {					//	相乘矩阵行数与本身列数不等 无法进行矩阵运算
		printf("error: 两矩阵无法相乘 \n");
		return false;
	}


	double* array = NULL;
	array = new double[this->row * mat.column];

	for (int i = 0; i < this->row; i++) {
		for (int k = 0; k < mat.column; k++) {
			double buffer = 0;
			for (int j = 0; j < this->column; j++) {
				buffer += (*(data + i * this->column + j)) * (*(mat.data + j * mat.column + k));
			}
			(*(array + i * mat.column + k)) = buffer;
		}
	}


	out->assign(array);

	delete[] array;
	array = NULL;

	return true;
}

bool Matrix::inverseMatrix(Matrix* out)
{
	double buffer = determinant(*(this));
	if (!buffer)
	{
		printf("该矩阵不可逆 \n");
		return false;
	}

	Matrix* adjointMat = new Matrix(row, column);

	this->adjointMatrix(adjointMat);												// 伴随矩阵
	

	buffer = 1.0 / buffer;

	for (int i = 0; i < column * row; i++) {
		*(adjointMat->data + i) = *(adjointMat->data + i) * buffer;
	}

	out->assign(adjointMat->data);
	return true;
}

void Matrix::adjointMatrix(Matrix* out)
{

	double*	bufferArray  = new double[row * column];						// 缓冲区数组
	double* adjointArray = new double[row * column];						// 伴随数组



	if (this->row == 2) {

		double buf[4];
		for (int i = 0; i < 4; i++) {
			buf[i] = *(this->data + i);
		}

		*(adjointArray)		= buf[3];
		*(adjointArray + 1) = buf[1] * -1;
		*(adjointArray + 2) = buf[2] * -1;
		*(adjointArray + 3) = buf[0];
	}


	else {

		Matrix* cofactorMat = new Matrix((row - 1), (column - 1));			// 余子式

		for (int r = 0; r < row; r++) {
			for (int c = 0; c < column; c++) {
				cofactor(r, c, cofactorMat);
				double buffer = determinant(*cofactorMat);

				*(bufferArray + r * column + c) = buffer * pow(-1, r + c);
			}
		}

		for (int i = 0; i < column; i++)
		{
			for (int j = 0; j < row; j++)
			{
				*(adjointArray + i * row + j) = *(bufferArray + (j*column) + i);
			}
		}
	}


	out->assign(adjointArray);

}

void Matrix::characteristicValue()
{
	Matrix* temp = new Matrix(this->row, this->column);
	Matrix* qMat = new Matrix(this->row, this->column);		// 正交矩阵
	Matrix* rMat = new Matrix(this->row, this->column);		// 上三角矩阵
	Matrix* eVal = new Matrix(this->row, 1);				// 获取特征值，将之存储于eValue



	temp->assign(this->data);

	for (int k = 0; k < 50; k++)
	{

		QR(temp, qMat, rMat);					// 进行QR分解法
		rMat->multiply(*qMat, temp);				// 上三角矩阵 * 正交矩阵
	}

	for (int k = 0; k < temp->column; k++)
	{
		eVal->data[k] = temp->data[k * temp->column + k];
	}


	Eig(this, qMat, eVal);

	for (int i = 0; i < eVal->row; i++) {

		printf("特征值 %.3lf 对应的 特征向量 为:\n", eVal->data[i]);

		for (int j = 0; j < qMat->row; j++) {
			printf("   %.3lf   ", qMat->data[i + j * qMat->column]);
		}
		printf("\n\n");
	}


}


void Matrix::QR(Matrix *A, Matrix *Q, Matrix *R)
{
	Matrix col_A = Matrix(A->row, 1);			//用来存A的每一列
	Matrix col_Q = Matrix(A->row, 1);			//用来存Q的每一列

	if (A->row != A->column)
		printf("A is not a square matrix!");


	int A_size = A->row * A->column;
	int Q_size = Q->row * Q->column;
	int R_size = R->row * R->column;


	if (Q_size != A_size)
	{
		Q->reSet(A->row, A->column);
	}
	else
	{
		Q->reSet(A->row, A->column);
	}

	if (R_size != A_size)
	{
		R->reSet(A->row, A->column);
	}
	else
	{
		R->reSet(A->row, R->column);
	}


	//施密特正交化
	for (int j = 0; j < A->column; j++)
	{
		for (int i = 0; i < A->column; i++)//把A的第j列存入col_A中
		{

			col_A.data[i] = A->data[i * A->column + j];
			col_Q.data[i] = A->data[i * A->column + j];
		}
		for (int k = 0; k < j; k++)//计算第j列以前
		{
			R->data[k * R->column + j] = 0;
			for (int i1 = 0; i1 < col_A.row; i1++)
			{//R=Q'A(Q'即Q的转置) 即Q的第k列和A的第j列做内积


				R->data[k * R->column + j] += col_A.data[i1] * Q->data[i1 * Q->column + k];//Q的第k列
			}
			for (int i2 = 0; i2 < A->column; i2++)
			{
				col_Q.data[i2] -= R->data[k * R->column + j] * Q->data[i2 * Q->column + k];
			}
		}

		double temp = norm2Matrix(&col_Q);
		R->data[j * R->column + j] = temp;
		for (int i3 = 0; i3 < Q->column; i3++)
		{
			//单位化Q
			Q->data[i3 * Q->column + j] = col_Q.data[i3] / temp;
		}
	}


}

double Matrix::norm2Matrix(Matrix * mat)
{
	double norm2_ans = 0.0;
	int matrix_num = mat->row * mat->column;

	for (int i = 0; i < matrix_num; i++)
		norm2_ans += (mat->data[i]) * (mat->data[i]);
	norm2_ans = (double)sqrt(norm2_ans);
	return norm2_ans;
}

void Matrix::reSet(int r, int c)
{
	int matrix_num = r * c;
	for (int i = 0; i < matrix_num; i++)
		this->data[i] = 0;
}


void Matrix::Eig(Matrix *A, Matrix *eigenVector, Matrix *eigenValue)
{
	int num = A->column;
	double eValue;
	Matrix temp = Matrix(A->row, A->column);


	for (int count = 0; count < num; count++)
	{
		eValue = eigenValue->data[count];			// 当前的特征值
		
		for (int i = 0; i < A->row * A->column; i++) {	// 这个每次都要重新复制，因为后面会破坏原矩阵
			temp.data[i] = A->data[i];
		}
													
													
		for (int i = 0; i < temp.row; i++)
		{
			temp.data[i * temp.column + i] -= eValue;
		}
		//将temp化为阶梯型矩阵(归一性)对角线值为一
		for (int i = 0; i < temp.row - 1; i++)
		{
			double coe = temp.data[i * temp.column + i];
			for (int j = i; j < temp.column; j++)
			{
				temp.data[i * temp.column + j] /= coe;//让对角线值为一
			}
			for (int i1 = i + 1; i1 < temp.row; i1++)
			{
				coe = temp.data[i1 * temp.column + i];
				for (int j1 = i; j1 < temp.column; j1++)
				{
					temp.data[i1 * temp.column + j1] -= coe * temp.data[i * temp.column + j1];
				}
			}
		}
		//让最后一行为1
		double sum1 = eigenVector->data[(eigenVector->row - 1) * eigenVector->column + count] = 1;
		for (int i2 = temp.row - 2; i2 >= 0; i2--)
		{
			double sum2 = 0;
			for (int j2 = i2 + 1; j2 < temp.column; j2++)
			{
				sum2 += temp.data[i2 * temp.column + j2] * eigenVector->data[j2 * eigenVector->column + count];
			}
			sum2 = -sum2 / temp.data[i2 * temp.column + i2];
			sum1 += sum2 * sum2;
			eigenVector->data[i2 * eigenVector->column + count] = sum2;
		}
		sum1 = sqrt(sum1);//当前列的模
		for (int i = 0; i < eigenVector->row; i++)
		{
			//单位化
			eigenVector->data[i * eigenVector->column + count] /= sum1;
		}
	}

}







double Matrix::determinant(Matrix & mat)
{
	if (mat.row != mat.column)
	{
		printf("该矩阵不为方阵 无法求对应行列式\n");
		return ERROR;
	}

	double result = 0;									// 行列式结果

	if (mat.row == 1) {
		return *(mat.data);
	}

	if (mat.row == 2)									// 为 2阶 矩阵
	{
		result = (*(mat.data)) * (*(mat.data + 3)) - (*(mat.data + 1)) * (*(mat.data + 2));	// 即 a11*a22 - a12*a21
		return result;

	}
	else
	{

		Matrix cofacMat = Matrix(mat.row - 1, mat.column - 1);			// 矩阵 mat 对应的 余子式

		for (int i = 0; i < mat.column; i++)
		{
			mat.cofactor(0, i, &cofacMat);		
			result += (pow(-1,i)) * (*(mat.data + i)) * determinant(cofacMat);

		}
		return result;
	}
}

//void Matrix::cofactor(int n, Matrix * out)
//{
//	int num = 0;
//	int r = this->row - 1;
//	int c = this->column - 1;
//	double* array = new double[r*c];
//
//	/*
//	  矩阵A = 1 ，2 ，3 ，4 ，			保存在数组中为 数组A = 1，2，3，4，5，6，7，8，9，10，11，12，13，14，15，16
//			  5 ，6 ，7 ，8 ，
//			  9 ，10，11，12，
//			  13，14，15，16。
//
//
//	则 A(1,1) 的余子式为  6 ，7 ，8 ，		即 从数组 A[5] 开始 如果数组下标与该矩阵列数 的余 为 1 则跳过
//						  10，11，12，							否则依次赋给新矩阵数组
//						  14，15，16。
//	*/
//
//
//
//
//
//
//
//	for (int i = column; i < row * column; i++)
//	{
//		if (i % column == n)
//		{
//			i = i + 1;
//			(*(array + num)) = (*(data + i));
//		}
//		else
//		{
//			(*(array + num)) = (*(data + i));
//		}
//		num++;
//	}
//
//	out->assign(array);
//
//	delete[] array;
//	array = NULL;
//
//}

void Matrix::cofactor(int r, int c, Matrix * out)			// 返回 第r行 w列 的代数余子式 
{
	/*
		 将第r行依次与上一行交换 直至为第一行
		 则其代数余子式 即求 新矩阵 newMat(1,w) 的代数余子式
	*/


	double* in = new double[column * row];					// 拷贝矩阵中的数据
	for (int i = 0; i < column*row; i++) {
		*(in + i) = *(data + i);
	}


	double* array = new double[this->column];				// 创建一维数组 存储 第r行 矩阵行向量
	for (int i = 0; i < column; i++) {
		*(array + i) = *(in + r * column + i);
	}


	for (; r > 0; r--) {									// 将上一行 矩阵行向量 赋给当前行
		for (int j = 0; j < column; j++) {
			*(in + r * column + j) = *(in + (r - 1)*column + j);
		}
	}
	
	for (int i = 0; i < column; i++) {						// 最后将array 赋值 给第一行
		*(in + i) = *(array + i);
	}

	delete[] array;
	array = NULL;



	/*
	  矩阵A = 1 ，2 ，3 ，4 ，			保存在数组中为 数组A = 1，2，3，4，5，6，7，8，9，10，11，12，13，14，15，16
			  5 ，6 ，7 ，8 ，
			  9 ，10，11，12，
			  13，14，15，16。


	则 A(1,1) 的余子式为  6 ，7 ，8 ，		即 从数组 A[5] 开始 如果数组下标与该矩阵列数 的余 为 1 则跳过
						  10，11，12，							否则依次赋给新矩阵数组
						  14，15，16。
	*/



	int num = 0;
	int m	= this->row - 1;
	int n	= this->column - 1;
	array = new double[m*n];

	for (int i = column; i < row * column; i++)
	{
		if (i % column == c)
		{
			i = i + 1;
			(*(array + num)) = (*(in + i));
		}
		else
		{
			(*(array + num)) = (*(in + i));
		}
		num++;
	}

	out->assign(array);

	delete[] array;
	array = NULL;

	delete[] in;
	in = NULL;
}

bool Matrix::assign(double* value) {
	if (!value)
		return false;
	for (int i = 0; i < (row * column); i++) {
		*(data + i) = *(value + i);
	}
	return true;
}

void Matrix::travel() {
	printf("Matrix: \n");
	for (int i = 0; i < this->row * this->column; i++) {
		printf("%4.1lf\t", *(this->data + i));
		if ((i + 1) % (this->column) == 0)
			printf("\n");
	}
}