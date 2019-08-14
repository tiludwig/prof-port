void transposeMatrix(volatile int32_t input[][MAXCOLS], int32_t result[][4])
{
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			result[i][j] = input[i][j];
		}
	}
}
