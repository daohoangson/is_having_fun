#include <iostream>
#include <math.h>

int count_used(int* used, int n)
{
	for (int ni = 0; ni < n; ni++)
	{
		if (used[ni] == -1)
		{
			return ni;
		}
	}

	return n;
}

bool is_used_all(int *used, int n)
{
	return count_used(used, n) == n;
}

bool is_used(int* used, int n, int i)
{
	for (int ni = 0; ni < n; ni++)
	{
		if (used[ni] == i)
		{
			return true;
		}
	}

	return false;
}

void pick_n_digits_from_numbers(int n, int* numbers, int numbers_count, bool* combinations, int* previously_used)
{
	int ni, i;
	int* used = new int[n];

	for (ni = 0; ni < n; ni++) used[ni] = (previously_used != NULL ? previously_used[ni] : -1);
	int used_count = count_used(used, n);

	if (!is_used_all(used, n))
	{
		for (i = 0; i < numbers_count; i++)
		{
			if (!is_used(used, n, i))
			{
				used[used_count] = i;
				pick_n_digits_from_numbers(n, numbers, numbers_count, combinations, used);
				used[used_count] = -1;
			}
		}
	}
	else
	{
		int combination = 0;
		for (ni = 0; ni < n; ni++)
		{
			combination += numbers[used[ni]] * pow(10, ni);
		}

		if (combinations[combination] == false)
		{
			for (ni = 0; ni < n; ni++)
			{
				if (ni > 0) std::cout << ' ';
				std::cout << numbers[used[ni]];
			}
			std::cout << std::endl;

			combinations[combination] = true;
		}
	}

	delete[] used;
}

int main(int argc, char** argv)
{
	int i, n, ni, sum;
	int c[10];

	std::cin >> n;
	sum = 0;
	for (i = 0; i < 9; i++) std::cin >> c[i+1]; // read 1-9
	std::cin >> c[0];
	std::cin >> c[0]; // read 0
	for (i = 0; i < 10; i++) sum += c[i]; // get sum of buttons

	// start preparing numbers to use
	int* numbers = new int[sum];
	bool* combinations = new bool[(int) pow(10, n)];
	ni = 0;
	while (ni < sum)
	{
		for (i = 0; i < 10; i++)
		{
			while (c[i] > 0)
			{
				numbers[ni++] = i;
				c[i]--;
			}
		}
	}
	// finish preparing numbers

	pick_n_digits_from_numbers(n, numbers, sum, combinations, NULL);

	// clean up stuff
	delete[] numbers;
	delete[] combinations;

	return 0;
}