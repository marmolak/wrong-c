#include <vector>
#include <climits>
#include <iostream>
#include <stdio.h>
using namespace std;

int bit1Count(int a, int b) {
	unsigned int y, cnt = 0;
	for(; a <= b ; ++a) {
		y = 1;
		while (y & ~(UINT_MAX + 1)) {
			if (a & y) cnt++;
			y <<= 1;
		}
	}
	return cnt;
}

int main(void)
{
	std::cout << bit1Count(2, 7) << '\n';
}

