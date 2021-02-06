void StartTimer( _int64 *pt1 )
{
   QueryPerformanceCounter( (LARGE_INTEGER*)pt1 );
}

double StopTimer( _int64 t1 )
{
   _int64 t2, ldFreq;

   QueryPerformanceCounter( (LARGE_INTEGER*)&t2 );
   QueryPerformanceFrequency( (LARGE_INTEGER*)&ldFreq );
   return ((double)( t2 - t1 ) / (double)ldFreq) * 1000.0;
}
