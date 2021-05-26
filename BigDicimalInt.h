#pragma once
#include<iostream>
#include<string>
using namespace std;
class BigDicimalInt
{
	string number;
	bool sign;
public:
	BigDicimalInt();
	BigDicimalInt(int number);
	BigDicimalInt(string number);
	friend ostream& operator<<(ostream& out, BigDicimalInt& big);
	friend istream& operator>>(istream& in, BigDicimalInt& big);
	BigDicimalInt& operator+(BigDicimalInt& big);
	BigDicimalInt &operator-(BigDicimalInt& big);
	BigDicimalInt operator=(BigDicimalInt& big);
	
};

