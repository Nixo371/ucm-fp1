#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;


int main()
{
	ifstream	input;
	ofstream	output;
	int		num;
	int		res;

	input.open("input.txt");
	if (!input.is_open())
	{
		perror ("Input no se pudo abrir");
		return (1);
	}
	output.open("output.txt");
	if (!output.is_open())
	{
		perror ("Output no se pudo abrir");
		return (1);
	}

	do
	{
		input >> num;
		if (num <= 0)
			continue;
		do
		{
			res = num % 10;
			num = num / 10;
			output << res;
		} while (num >= 10);
		output << num << endl;
		
	} while (num != 0);
	
	return (0);
}