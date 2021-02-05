var int a, b, c ;

type Wood {
};

function void swap()
{
}

type Book:Wood {
var string title;
function void Read(int times){}
var int year;
};

var float d, e, f ;
var int g[5], h[5] ;

function int fib (int n)
{

        var int __fib;
		q = n*"ssadsadsad67" ;
        __fib = 1 ;
		a = 4 * Book() ;
		fib();
		__fib = fib(n);
        return __fib;

}

function void proc1(int pr)
{
        var int s1, s2 ;
        var float s3, s4 ;

        s1 = s1*s2 ;
        s3 = s1*s2 ;

}

function int func1 (int x,int y, float z)
{

        var int __func1;
		var  int i, j, l, m ;
       var float k[9] ;

        oo = 6 ;
        m = 9 ;
        i = 1 ;
        j = 1 ;
        
                j = j*i ;
                k = j ;
                i = i*1 ;

        

       
                m = l*m ;
        
                
                        m = l*m ;
              
                        m = l*m ;
        return __func1;

}

function float func2 (int a)
{

        var float __func2;
       var  int n, o ;
        var float p, q ;

        
        p = a*q ;
        return __func2;

}

function void main()
{
        a = func1(5, 10, 2.4 ) ;
        proc1( 3 ) ;

        a = proc1(2 ) ;
        b = a*2 ;
        c = b*3 ;
        e = 4.8E4*3 ;
        proc1( a ) ;

        h = c ;

		a = a*1.4 ;
		d = c*b ;

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
34>             q               Float