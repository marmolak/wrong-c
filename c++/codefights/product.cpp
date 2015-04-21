#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

/*
Given an array of non-negative integers, find the sum of the digits of the maximum product of consecutive elements of L, k length.
 
Example: sumDigProduct(["100", "300", "700", "0", "1", "30"], 3) = 3

Input (L) → array.string :
array of integers represented as strings. 
6
0 <= L[i] <= 10^60 

1 <= length <= 100
Input (k) → integer :
integer not exceeding the size L
Output → integer :
sum of the digits of máximum product

Example:
sumDigProduct(["100", "300", "700", "0", "1", "30"], 3) the max product of length 3 is: 100 x 300 x 700 = 21000000. Take the sum of digits: 2+1+0+0+0+0+0 +0 = 3
*/

struct big_number {
	long long num1;
	long long num2;
	long long num3;
	long long num4;
};

int sumDigProduct(std::vector< std::string > L, int k) {
	unsigned long long max = 0;

	if ( k > L.size() ) {
		return 0;
	}

	for (unsigned int p = 0; p <= (L.size() - k); p += k) {
		unsigned long long sum = 1;
		for (unsigned int i = 0; i < k; ++i) {
			sum *= atoll(L[p + i].c_str());
		}
		if (sum > max) max = sum;
	}

	int sum = 0;
	while (max) {
		sum += max % 10;
		max /= 10;
	}

	return sum;
}

int main()
{
	std::vector<std::string> L;
	L.push_back("100");
	L.push_back("300");
	L.push_back("700");

	L.push_back("0");
	L.push_back("1");
	L.push_back("30"); 
	/*=> 3*/


	/*L.push_back("100");
	L.push_back("200");
	L.push_back("300");

	L.push_back("0");
	L.push_back("1");
	L.push_back("30");

	L.push_back("200");
	L.push_back("20");
	L.push_back("10000");

	L.push_back("10000");*/
	/* => 4 */

	/* Doesn't work for huge numbers
	 L.push_back("1000000000000000000000000000000000000000000000000000000000001");
	 L.push_back("1000000000000000000000000000000000000000000000000000000000003");
	 L.push_back("1000000000000000000000000000000000000000000000000000000000002");
	 L.push_back("0");
	 L.push_back("1000000000000000000000000000000000000000000000000000000000000");
	 L.push_back("1000000000000000000000000000000000000000000000000000000000000");
	 */
       

//	 k = 3 -&gt; 15

	std::cout << sumDigProduct(L, 3) << "\n";
}
