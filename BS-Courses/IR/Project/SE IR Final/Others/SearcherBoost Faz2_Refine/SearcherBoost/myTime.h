void StartTimer( _int64 *pt1 )
{
   QueryPerformanceCounter( (LARGE_INTEGER*)pt1 );
}

long double StopTimer( _int64 t1 )
{
   _int64 t2, ldFreq;

   QueryPerformanceCounter( (LARGE_INTEGER*)&t2 );
   QueryPerformanceFrequency( (LARGE_INTEGER*)&ldFreq );
   return ((long double)( t2 - t1 ) / (long double)ldFreq) * 1000.0;
}
