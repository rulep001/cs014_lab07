#include <iostream>
#include "Heap.h"

using namespace std;

Heap::Heap() {
    /*Initializes an empty heap.*/
    numItems = 0;
}

void Heap::enqueue ( PrintJob* job) {
    /*Inserts a PrintJob to the heap without
    violating max-heap properties.*/
    if (numItems == MAX_HEAP_SIZE) {
        return;
    }
    
    if (numItems == 0) {
        arr[numItems] = job;
        ++numItems;
    }
    else {
        int x = numItems;
        while (x > 0 && (arr[(x - 1) / 2]->getPriority() < job->getPriority()) ) {
            arr[x] = arr[(x - 1) / 2];
            x = (x - 1) / 2;
        }
        arr[x] = job;
        ++numItems;
    }
}

void Heap::dequeue ( ) 
{
    /*Removes the node with highest priority from the heap. 
    Follow the algorithm on priority-queue slides. */
    if (numItems == 0) {
        return;
    }
    
    PrintJob* first = arr[0];
    arr[0] = arr[numItems-1];
    delete first;
    arr[numItems-1] = 0;
    numItems--;
    trickleDown(0);
    return;
}


PrintJob* Heap::highest ( ) {
    /*Returns the node with highest priority.*/
    return arr[0];
}

void Heap::print ( ) {
    /*Prints the PrintJob with highest priority in the following format:
    Priority: priority, Job Number: jobNum, Number of Pages: numPages
    (Add a new line at the end.)*/
    
    if (arr[0] != 0) {
        cout << "Priority: " << arr[0]->getPriority() << ", Job Number: " << arr[0]->getJobNumber() << ", Number of Pages: " << arr[0]->getPages() << endl;
    }
    
}

/*void Heap::trickleDown(int index) 
{
    This function is called by dequeue function
    to move the new root down the heap to the 
    appropriare location.
    if(index >= numItems) return;
    else if(arr[index]==0) return;
    //else if(arr[index*2+2]==0) return;
    if(arr[index*2+2]==0)
    {
        if(arr[index*2+1]!=0)
        {
            if(arr[index*2+1]->getPriority() > arr[index]->getPriority())
            {
                PrintJob* temp = arr[index];
                arr[index] = arr[index*2+1];
                arr[index*2+1] = temp;
                return;
            }
        }
    }
    
    PrintJob* curr = arr[index];
    PrintJob* currR = arr[index*2+2];
    
    if (curr->getPriority() > currR->getPriority()) return;
    else if (arr[index*2+2]!=0)
    {
        arr[index] = arr[index*2+2];
        arr[index*2+2] = curr;
        trickleDown(index*2+2);
        return;
    }
}
*/

void Heap :: trickleDown(int index)
{
    if(index*2+2 >= numItems) return;
    else if (index*2+1 >=numItems) return;
    PrintJob* curr = arr[index];
    PrintJob* R = arr[index*2+2];
    PrintJob* L = arr[index*2+1];
    if(L!=0)
    {
        if(curr->getPriority() < L->getPriority() &&
            L->getPriority() > R->getPriority())
        {
            arr[index] = L;
            arr[index*2+1] = curr;
            trickleDown(index*2+1);
            return;
        }
    }
    if(R!=0)
    {
        if((curr->getPriority() < R->getPriority()) &&
            R->getPriority() > L->getPriority())
        {
            arr[index] = R;
            arr[index*2+2] = curr;
            trickleDown(index*2+2);
            return;
        }
    }
    
}