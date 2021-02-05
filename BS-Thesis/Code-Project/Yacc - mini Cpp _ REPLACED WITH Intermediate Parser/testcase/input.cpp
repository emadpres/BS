
int fib (int n)
{

        int __fib;

        if ((n<=2 ) )
                __fib = 1 ;
      
        return __fib;

}

void proc1(int pr)
{
        int s1, s2 ;
        float s3, s4 ;

        s1 = s1*s2 ;
        s3 = s1%s2 ;

}

int func1 (int x,int y, float z)
{

        int __func1;
        int i, j, l, m ;
        float k[9] ;

        oo = 6 ;
        m = 9 ;
        i = 1 ;
        j = 1 ;
        while( i<10 ){
                j = j*i ;
                k[i-1] = j ;
                i = i+1 ;

        }

        if (i<20 )
                if (i>=20 )
                        m = l/m ;

        return __func1;

}

float func2 (int a)
{

        float __func2;
        int n, o ;
        float p, q ;

        q = n*(o/3 ) ;
        p = a%q ;
        if (n<3 )
                {
                        o = 5 ;

                }

        q = o+7 ;
        return __func2;

}
void main()
{
        a = func1(5, 10, 2.4 ) ;
        proc1( 3 ) ;

        a = proc1(2 ) ;
        b = a/2 ;
        c = a+b*3 ;
        e = 0.8E+3+(2*(5/3 ) ) ;
        proc1( a ) ;

        h[4-3] = c ;
        while( a<b ){
                a = a+1 ;
                d = c*a/b ;

        }


}
Symbol Table
------------> Global(8)

1>              a               Integer
2>              b               Integer
3>              c               Integer
4>              d               Float
5>              e               Float
6>              f               Float
7>              g               Integer         YES             LowerBound:3
8>              h               Integer         YES             LowerBound:3
------------> fib(2)

10>             n               Integer
11>             __fib   Unknown
------------> proc1(5)

13>             pr              Integer
14>             s1              Integer
15>             s2              Integer
16>             s3              Float
17>             s4              Float
------------> func1(9)

19>             x               Integer
20>             y               Integer
21>             z               Float
22>             __func1 Unknown
23>             i               Integer
24>             j               Integer
25>             l               Integer
26>             m               Integer
27>             k               Float           YES             LowerBound:1
------------> func2(6)

29>             a               Integer
30>             __func2 Unknown
31>             n               Integer
32>             o               Integer
33>             p               Float
34>             q               Floatco	