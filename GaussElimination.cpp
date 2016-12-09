// :D :) :D :) :D :) :D :) :D :) :D :) :D :)

#include"Header.h"


void SolveMatrix(double**A, int N, double *& Ans)// A multi dimentional array (matrix) N number of equations Ans empty array will be returned with ans
{
	int row = 0, coloum = 0;
	double temp1, temp2;
	while (row < N)
	{
		int j = row + 1;
		while (A[row][coloum] == 0 && j < N) //for zero 
		{
			swaprows(A, row, j); // exchange zero in row by number 
			j++;

		}

		temp1 = A[row][coloum];
		if (temp1 == 0) {
			Ans = NULL;
			return;
		}

		for (int i = 0; i <= N; i++)// get one
		{
			if (A[row][i] != 0) // to avoid -0 result
				A[row][i] /= temp1;
			else continue;

		}

		swaprows(A, 0, row); // always eliminate with first row

		for (int i = 1; i<N; i++)
		{
			temp2 = A[i][coloum];
			for (int j = 0; j<N + 1; j++)
				A[i][j] -= temp2*A[0][j];
		}
		swaprows(A, 0, row); // put the row again in his place
		row++; coloum++;
	}
	Ans = new double[N];
	for (int i = 0; i < N; i++)
	{
		double temp; // for rounding numbers 5 numbers after floating piont{ accurate} :D
		temp = A[i][N] * pow(10, 5);
		if ((abs(temp - int(temp))) > 0.5)
		{
			if (temp > 0)
				Ans[i] = ceil(temp);
			else Ans[i] = floor(temp);
		}
		else {
			if (temp > 0)
				Ans[i] = floor(temp);
			else Ans[i] = ceil(temp);

		}
		Ans[i] = Ans[i] / pow(10, 5);
	}

	DeallocateMatrix(A, N);
	return;
}

void swaprows(double**a, int row1, int row2)
{
	double *temp;
	temp = a[row1];
	a[row1] = a[row2];
	a[row2] = temp;
}


void DeallocateMatrix(double**Z, int num)
{
	for (int i = 0; i < num; i++)
		delete[] Z[i];
	delete[] Z;

}
