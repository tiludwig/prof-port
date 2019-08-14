


void productMatrix(volatile int32_t array1[][MAXCOLS], volatile int32_t array2[][MAXCOLS], int32_t array3[][MAXCOLS], int m, int n)
{

	int i, j, k;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			array3[i][j] = 0;
			for (k = 0; k < n; k++)
			{
				array3[i][j] = array3[i][j] + array1[i][k] * array2[k][j];
			}
		}
	}
}
