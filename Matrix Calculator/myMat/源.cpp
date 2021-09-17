#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"


int main(int argc, char** argv) {
	int  row  = 0;
	int	 col  = 0;
	char func = '\0';

	printf("请依次输入将要进行操作的矩阵的 行数及列数 (依次用回车键确认输入)\n");
	scanf_s("%d", &row);
	scanf_s("%d", &col);

	printf("请按顺序输入矩阵中的元素 (依次用回车键确认输入)\n");

	double* arr = new double[row*col];
	for (int i = 0; i < row*col; i++) {
		scanf_s("%lf", (arr + i));
	}
	getchar();

	Matrix* A =new Matrix(row, col);					// 生成对应输入的 row行 col列 矩阵对象
	A->assign(arr);										// 赋值

	system("cls");										// 清屏




	while (1) {
		printf("当前的矩阵为:\n");							// 最上方显示 当前矩阵
		A->travel();

		printf("\n\n请输入以下指令执行相应操作:\n");

		printf("  重新输入矩阵:  \tR\n");
		printf("  矩阵乘法运算 左乘: \tM\n");
		printf("  求该矩阵的转置矩阵: \tT\n");
		printf("  求改矩阵的逆矩阵: \tI\n");
		printf("  求该矩阵的模: \tD\n");
		printf("  求该矩阵的特征值: \tC\n");
		printf("  退出:  \t\tQ\n");

		scanf_s("%c", &func);
		getchar();

		if (func == 'R') {								// 重新输入矩阵
			int  r = 0;
			int	 c = 0;

			printf("请依次输入将要进行操作的矩阵的 行数及列数 (依次用回车键确认输入)\n");
			scanf_s("%d", &r);
			scanf_s("%d", &c);
			printf("请按顺序输入矩阵中的元素 (依次用回车键确认输入)\n");
			double* arr = new double[r*c];
			for (int i = 0; i < r*c; i++) {
				scanf_s("%lf", (arr + i));
			}
			getchar();

			delete A;
			A = NULL;

			A = new Matrix(r, c);
			A->assign(arr);

			system("cls");
		}
		if (func == 'Q') {
			break;
		}
		if (func == 'M') {
			int  r = 0;
			int	 c = 0;

			printf("请依次输入将要参与乘法运算矩阵的 行数及列数 (依次用回车键确认输入)\n");
			scanf_s("%d", &r);
			scanf_s("%d", &c);
			printf("请按顺序输入参与乘法运算矩阵中的元素 (依次用回车键确认输入)\n");
			double* arr = new double[r*c];
			for (int i = 0; i < r*c; i++) {
				scanf_s("%lf", (arr + i));
			}
			getchar();

			Matrix B = Matrix(r , c );
			B.assign(arr);



			system("cls");

			printf("当前的矩阵为:\n");							// 最上方显示 当前矩阵
			A->travel();

			printf("\n输入的乘数矩阵为:\n");
			B.travel();



			Matrix* out = NULL;
			if (A->getRow() * A->getColumn() == 1) {
				out = new Matrix(B.getRow(), B.getColumn());
			}else
				out = new Matrix(A->getRow(), B.getColumn());


			if (A->multiply(B, out)) {
				printf("\n两矩阵相乘结果为:\n");
				out->travel();
			}

			printf("回车继续矩阵操作\n");
			getchar();

			system("cls");

		}
		if (func == 'T') {
			Matrix out = Matrix(A->getColumn(), A->getRow());
			A->transposeMatrix(&out);
			printf("\n转置矩阵为:\n");
			out.travel();


			printf("回车继续矩阵操作\n");
			getchar();

			system("cls");
		}
		if (func == 'I') {
			Matrix out = Matrix(col, row);
			A->inverseMatrix(&out);
			printf("\n逆矩阵为:\n");
			out.travel();


			printf("回车继续矩阵操作\n");
			getchar();

			system("cls");
		}
		if (func == 'D') {
			
			double result = 0;
			result = Matrix::determinant(*A);

			if (result != ERROR) {
				printf("\n矩阵的模为:\n");
				printf("%.1lf\n", Matrix::determinant(*A));
			}


			printf("回车继续矩阵操作\n");
			getchar();

			system("cls");
		}
		if (func == 'C') {
			A->characteristicValue();

			printf("回车继续矩阵操作\n");
			getchar();

			system("cls");

		}
		
	}


	printf("Press any keys to continue ...");
	getchar();

	delete[] arr;
	arr = NULL;

	delete A;
	A = NULL;

	return 0;
}