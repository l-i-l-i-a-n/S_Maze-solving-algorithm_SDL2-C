#include "testbinary_heap.h"
#include "comparison.h"

int main()
{
    test_MinHeapify();
    testBuildMinHeap();
    puts("\n");
    comparison(100000);

    return 0;
}