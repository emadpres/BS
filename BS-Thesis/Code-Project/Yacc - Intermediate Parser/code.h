/* Can easily be modified to work with other data types */
 
void heapsort(int *arr, int n)
{
    int start, end;
 
    // heapify the array
    for(start = (n - 2) / 2; start >= 0; --start) // for every root
        siftDown(arr, start, n); // sift through it
     
    // sort the array
    for(end = n - 1; end; --end) // for every element of the heap
    {
        swapi(&arr[end], &arr[0]); // swap it with the top root
        siftDown(arr, 0, end); // rebuild the heap
    }
}
 
void siftDown(int *arr, int start, int end)
{
    int root, child;
 
    root = start; // pick the root index
    while(2 * root + 1 < end) // while the root has a child
    {
        child = 2 * root + 1; // pick its index
        if((child + 1 < end) && (arr[child] < arr[child+1]))
            ++child; // if the other child is bigger, pick it instead
        if(arr[root] < arr[child]) // if root is smaller than the child
        {
            swapi(&arr[child], &arr[root]); // swap them
            root = child; // go down the heap
        }
        else // if the child is smaller than the root
            return; // that root is in the right spot
    }
}
 
void swapi(int *x, int *y)
{
    int z;
     
    z = *x;
    *x = *y;
    *y = z;
}