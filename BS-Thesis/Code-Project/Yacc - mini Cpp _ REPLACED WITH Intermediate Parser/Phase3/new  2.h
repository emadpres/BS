int fibo(int a)
{
	float input = a ;
	int result = 3 ;
	long int preResult = 2 ;
	for ( int i = 0 ; i < input ; i++ )
	{
		preResult = result + preResult ; 
	}
	
}

int main()
{
	char a = 0;
	cin >> a ;
	long int  result = fibo(a);
	return;
}