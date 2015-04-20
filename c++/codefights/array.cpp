#include <vector>
#include <climits>
#include <iostream>
#include <stdio.h>
using namespace std;

/*
You are given 2 numbers a and b where 0 <= a <= b. Imagine you construct an array of all the numbers
from a to b inclusive. You need to count the number of 1's in the binary representations of all the numbers in the array.

Example given a = 2 and b = 7 the array is: [2, 3, 4, 5, 6, 7]. Converting the numbers to binary,
we get [10, 11, 100, 101, 110, 111], which contains 1 + 2 + 1 + 2 + 2 +3 = 11 1s.

First draft:
	Execution time limit exceeded!!!

Second draft:
	in progress
*/

int bit1Count(int a, int b) {
	register unsigned int y, cnt = 0;
	for(; a <= b ; ++a) {
		y = 1;
		while (y & UINT_MAX) {
			if (a & y) cnt++;
			/* Let y overflow) to 0 */
			y <<= 1;
		}
	}
	return cnt;
}

int main(void)
{
	std::cout << bit1Count(2, 7) << '\n';
}

