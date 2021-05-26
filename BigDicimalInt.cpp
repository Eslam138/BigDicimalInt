#include "BigDicimalInt.h"
bool findBigger(string& number1, string& number2)//this method check which number is begger 
{
	if (number1.length() > number2.length())
		return true;
	else if (number1.length() < number2.length())
		return false;
	else
	{
		for (size_t i = 0; i < number1.length(); i++)
		{
			if (number1[i] < number2[i])
			{
				return false;
			}
			if (number1[i] > number2[i])
			{
				return true;
			}
		}
	}
	return false;
}

BigDicimalInt::BigDicimalInt()
{
	number = " ";
}

BigDicimalInt::BigDicimalInt(int number)
{
	if (number > 0)
	{
		this->sign = true;
	}
	else
		this->sign = false;
	while (number!=0)
	{
		int sum = number % 10;
		this->number.push_back((number % 10) + '0');
		number /= 10;
	}
	for (size_t i = 0; i < this->number.length(); i++)
	{
		if (this->number[i] == '0')
			this->number.erase(i);
	}
}

BigDicimalInt::BigDicimalInt(string number)
{
	int counter = 0;//to know if the string have + or -
	if (number[0] == '-')
	{
		counter++;
		sign = false;
	}
	else if (number[0] == '+')
	{
		counter++;
		sign = true;
	}
	else
		sign = true;

	for (counter; counter <number.length();counter++)
	{
		this->number.push_back(number[counter]);
	}
}
string addtion(string& number1, string& number2)
{
	string bigger, smaller,newString;
	int diff=0;//to know
	if (number1.length()<number2.length())
	{
		bigger = number2;
		smaller = number1;
		diff = number2.length() - number1.length();
	}
	else
	{
		bigger = number1;
		smaller = number2;
		diff = number1.length() - number2.length();
	}
	int carry = 0;
	int i;
	for ( i = smaller.length()-1; i >= 0; i--)
	{
		int sum = ((bigger[i] -'0') + (smaller[i]-'0') + carry);
		newString.push_back(sum % 10+'0' );
		sum -= sum % 2;
		carry = sum / 10;
	}
	for (i = diff-1; i >= 0; i--)
	{
		int sum = ((bigger[i]-'0' ) +carry);
		newString.push_back(sum % 10+'0' );
		carry = sum / 10;
	}
	if (carry!=0)
	{
		newString.push_back(carry+'0');
	}

	reverse(newString.begin(), newString.end());
	return newString;
}
string subtraction(string& number1, string& number2)
{
	string bigger, smaller, newString;
	int diff = 0;//to know
	if (!findBigger(number1,number2))
	{
		bigger = number2;
		smaller = number1;
		diff = number2.length() - number1.length();
	}
	else
	{
		bigger = number1;
		smaller = number2;
		diff = number1.length() - number2.length();
	}
	int carry = 0;
	int i;
	for (i = smaller.length() - 1; i >= 0; i--)
	{
		int sum = ((bigger[i] - '0') - (smaller[i] - '0') - carry);
		if (sum<0)
		{
			sum += 10;
			carry += 1;
		}
		else
			carry = 0;
		newString.push_back(sum + '0');
	}
	for (i = diff - 1; i >= 0; i--)
	{
		int sum = ((bigger[i] - '0') - carry);
		if (sum < 0)
		{
			sum += 10;
			carry += 1;
		}
		else
			carry = 0;
		newString.push_back(sum + '0');
	}
	reverse(newString.begin(), newString.end());
	return newString;
}

BigDicimalInt &BigDicimalInt::operator+(BigDicimalInt& big)
{
	BigDicimalInt* temp = new BigDicimalInt();
	if ((big.sign == false && this->sign == true)|| (big.sign == true && this->sign == false))
	{
		temp->number = subtraction(this->number, big.number);
		if (!findBigger(this->number, big.number))
		{
			if (this->sign == true)
				temp->sign = false;
			else
				temp->sign = true;
		}
		else
			temp->sign = this->sign;
		return *temp;
	}
	temp->number = addtion(this->number, big.number);
	temp->sign = this->sign;
	return *temp;
}
BigDicimalInt &BigDicimalInt::operator-(BigDicimalInt& big)
{
	BigDicimalInt* temp = new BigDicimalInt();
	if ((big.sign==false&&this->sign==true)|| big.sign == true && this->sign == false)
	{
		temp->number = addtion(this->number, big.number);
		temp->sign = false;
		return *temp;
	}
	temp->number = subtraction(this->number, big.number);
	if (!findBigger(this->number, big.number))
	{
		if (this->sign == true)
			temp->sign = false;
		else
			temp->sign = true;
	}
	else
		temp->sign = this->sign;
	return *temp;
}

BigDicimalInt BigDicimalInt::operator=(BigDicimalInt& big)
{
	this->number = big.number;
	this->sign = big.sign;
	return *this;
}

ostream& operator<<(ostream& out, BigDicimalInt& big)
{
	if (big.sign==false)
	{
		out << "-";
	}
	out << big.number << endl;
	return out;
}

istream& operator>>(istream& in, BigDicimalInt& big)
{
	in >> big.number;
	return in;
}
