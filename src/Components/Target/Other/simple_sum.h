void matrixAdd(int matrixA[][MAXCOLS], int matrixB[][MAXCOLS], int result[][MAXCOLS], int m, int n)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = matrixA[i][j] + matrixB[i][j];
		}
	}
}
