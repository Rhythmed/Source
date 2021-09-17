#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"


int main(int argc, char** argv) {
	int  row  = 0;
	int	 col  = 0;
	char func = '\0';

	printf("���������뽫Ҫ���в����ľ���� ���������� (�����ûس���ȷ������)\n");
	scanf_s("%d", &row);
	scanf_s("%d", &col);

	printf("�밴˳����������е�Ԫ�� (�����ûس���ȷ������)\n");

	double* arr = new double[row*col];
	for (int i = 0; i < row*col; i++) {
		scanf_s("%lf", (arr + i));
	}
	getchar();

	Matrix* A =new Matrix(row, col);					// ���ɶ�Ӧ����� row�� col�� �������
	A->assign(arr);										// ��ֵ

	system("cls");										// ����




	while (1) {
		printf("��ǰ�ľ���Ϊ:\n");							// ���Ϸ���ʾ ��ǰ����
		A->travel();

		printf("\n\n����������ָ��ִ����Ӧ����:\n");

		printf("  �����������:  \tR\n");
		printf("  ����˷����� ���: \tM\n");
		printf("  ��þ����ת�þ���: \tT\n");
		printf("  ��ľ���������: \tI\n");
		printf("  ��þ����ģ: \tD\n");
		printf("  ��þ��������ֵ: \tC\n");
		printf("  �˳�:  \t\tQ\n");

		scanf_s("%c", &func);
		getchar();

		if (func == 'R') {								// �����������
			int  r = 0;
			int	 c = 0;

			printf("���������뽫Ҫ���в����ľ���� ���������� (�����ûس���ȷ������)\n");
			scanf_s("%d", &r);
			scanf_s("%d", &c);
			printf("�밴˳����������е�Ԫ�� (�����ûس���ȷ������)\n");
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

			printf("���������뽫Ҫ����˷��������� ���������� (�����ûس���ȷ������)\n");
			scanf_s("%d", &r);
			scanf_s("%d", &c);
			printf("�밴˳���������˷���������е�Ԫ�� (�����ûس���ȷ������)\n");
			double* arr = new double[r*c];
			for (int i = 0; i < r*c; i++) {
				scanf_s("%lf", (arr + i));
			}
			getchar();

			Matrix B = Matrix(r , c );
			B.assign(arr);



			system("cls");

			printf("��ǰ�ľ���Ϊ:\n");							// ���Ϸ���ʾ ��ǰ����
			A->travel();

			printf("\n����ĳ�������Ϊ:\n");
			B.travel();



			Matrix* out = NULL;
			if (A->getRow() * A->getColumn() == 1) {
				out = new Matrix(B.getRow(), B.getColumn());
			}else
				out = new Matrix(A->getRow(), B.getColumn());


			if (A->multiply(B, out)) {
				printf("\n��������˽��Ϊ:\n");
				out->travel();
			}

			printf("�س������������\n");
			getchar();

			system("cls");

		}
		if (func == 'T') {
			Matrix out = Matrix(A->getColumn(), A->getRow());
			A->transposeMatrix(&out);
			printf("\nת�þ���Ϊ:\n");
			out.travel();


			printf("�س������������\n");
			getchar();

			system("cls");
		}
		if (func == 'I') {
			Matrix out = Matrix(col, row);
			A->inverseMatrix(&out);
			printf("\n�����Ϊ:\n");
			out.travel();


			printf("�س������������\n");
			getchar();

			system("cls");
		}
		if (func == 'D') {
			
			double result = 0;
			result = Matrix::determinant(*A);

			if (result != ERROR) {
				printf("\n�����ģΪ:\n");
				printf("%.1lf\n", Matrix::determinant(*A));
			}


			printf("�س������������\n");
			getchar();

			system("cls");
		}
		if (func == 'C') {
			A->characteristicValue();

			printf("�س������������\n");
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