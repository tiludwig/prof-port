void swap(volatile int32_t* a, volatile int32_t* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
