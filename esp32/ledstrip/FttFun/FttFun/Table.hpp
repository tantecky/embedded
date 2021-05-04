#pragma once

#include <cstdio>
#include <cmath>

constexpr float M_PI = 3.14159265358979323846f;

struct Point {
	float Cos;
	float Sin;
	float Cos3;
	float Sin3;
};

class Table
{
	const int N;
	const int M;
	const int Levels;
	Point** table;

public:
	Table(const int n, const int m) : N(n), M(m), Levels(m - 3)
	{
		table = new Point*[Levels];

	}

	void init()
	{
		printf("N:%d M:%d Levels:%d\n", N, M, Levels);

		if (Levels < 1)
		{
			return;
		}

		int n2 = 2;

		for (int k = 1; k < M; k++) {
			n2 <<= 1;
			int n8 = n2 >> 3;

			printf("n2:%d j: ", n2);

			for (int j = 1; j < n8; j++) {
				printf("%d ", j);
			}

			printf("\n");
		}
	}
};