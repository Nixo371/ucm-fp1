#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdio.h>

using namespace std;

int capicua(int n);

int main()
{
	ifstream	input;
	int		num;

	input.open("input.txt");
	if (!input.is_open())
	{
		perror ("Input no se pudo abrir");
		return (1);
	}

	do
	{
		input >> num;
		if (num <= 0)
			continue;
		if (capicua(num) && num < INT32_MAX)
		{
			cout << "El primer numero capicua en input.txt es: " << num << endl;
			return (0);
		}
	} while (num != 0);
	return (0);
}

int capicua(int n)
{
	ofstream capicua;
	ifstream comprobar;
	int		res;
	int		num = n;

	capicua.open("temp.txt");

	do
		{
			res = num % 10;
			num = num / 10;
			capicua << res;
		} while (num >= 10);
	capicua << num << endl;

	capicua.close();
	comprobar.open("temp.txt");
	comprobar >> num;

	remove("./temp.txt");
	if (num == n)
		return (1);
	return (0);
}