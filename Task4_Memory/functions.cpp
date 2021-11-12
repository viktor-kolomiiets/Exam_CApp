const int IMAGE_COUNT = 11;

template <typename T>
void swap(T* a, T* b)
{
	T temp = *a;
	*a = *b;
	*b = temp;
}

void writeImage(int id, int image[2][4])
{
	//list of posible images
	int imageLibrary[IMAGE_COUNT][2][4]
	{   { 3, 32, 32, 32, 32, 32, 32, 3 },
		{ 4, 32, 32, 32, 32, 32, 32, 4 },
		{ 5, 32, 32, 32, 32, 32, 32, 5 },
		{ 6, 32, 32, 32, 32, 32, 32, 6 },
		{ 30, 30, 30, 30, 31, 31, 31, 31 },
		{ 31, 31, 31, 31, 30, 30, 30, 30 },
		{ 16, 32, 32, 17, 16, 32, 32, 17 },
		{ 32, 17, 16, 32, 32, 17, 16, 32 },
		{ 35, 32, 32, 35, 35, 32, 32, 35 },
		{ 35, 32, 32, 32, 32, 32, 32, 35 },
		{ 32, 32, 32, 35, 35, 32, 32, 32 }
	};

	for (int h = 0; h < 2; h++)
		for (int w = 0; w < 4; w++)
			image[h][w] = imageLibrary[id][h][w];
}
