#ifndef B71C8773_2136_4D4F_9D6D_B1F00570DBC8
#define B71C8773_2136_4D4F_9D6D_B1F00570DBC8

#include <cstdio>
#include <cmath>

constexpr float M_PI_F = 3.14159265358979323846f;

struct Point
{
	float Cos;
	float Sin;
	float Cos3;
	float Sin3;

	void set(const float angle)
	{
		Cos = cosf(angle);
		Sin = sinf(angle);

		const float angle3 = 3.0f * angle;
		Cos3 = cosf(angle3);
		Sin3 = sinf(angle3);
	}
};

class SinCosTable
{
	const int N;
	const int M;
	const int Levels;
	Point **table;

public:
	SinCosTable(const int n, const int m) : N(n), M(m), Levels(m - 3)
	{
		table = new Point *[Levels];
	}

	inline const Point &getPoint(const int k, const int j) const
	{
		return table[k - 3][j - 1];
	}

	void init()
	{
		//printf("N:%d M:%d Levels:%d\n", N, M, Levels);

		if (Levels < 1)
		{
			return;
		}

		int n2 = 2;

		for (int k = 1; k < M; k++)
		{
			n2 <<= 1;
			const int n8 = n2 >> 3;

			if (n8 < 2)
			{
				continue;
			}

			const float e = (M_PI_F * 2) / n2;
			const int level = k - 3;

			//printf("L:%d n2:%d j: ", level, n2);

			table[level] = new Point[n8];

			for (int j = 1; j < n8; j++)
			{
				const float angle = j * e;
				Point &p = table[level][j - 1];
				p.set(angle);
				//printf("%d ", j);
			}

			//printf("\n");
		}
	}
};

extern SinCosTable SinCos;

#endif /* B71C8773_2136_4D4F_9D6D_B1F00570DBC8 */
