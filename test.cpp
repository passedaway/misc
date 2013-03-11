#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int test(int a)
{
	cout<<"int part"<<a<<endl;
	return 0;
}

int test(int a, float b)
{
	cout<<"int part"<<b<<"b ="<<a<<endl;
	return 0;
}

int main(int argc, char **argv)
{
	int val;

	cout<<"input some thing!"<<endl;

	test(1);
	test(1,2.0);

	while(cin>>val && val != 42)
	{
		cout<<"in while!"<<endl;
		cout<<"val = "<<val<<endl;
	}

	cout<<"end of while!"<<endl;

	return 0;
}
