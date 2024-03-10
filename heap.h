#include <iostream>
using namespace std;

class Heap
{
public:
    int arr[100];
    string name[100];
    int size = 0;

    Heap()
    {
        arr[0] = -1;
        name[0] = "-1";
        size = 0;
    }
    void insert(int val, string n)
    {
        size = size + 1;
        int index = size;
        arr[index] = val;
        name[index] = n;

        while (index > 1)
        {
            int parentIndex = index / 2;
            if (arr[parentIndex] < arr[index])
            {
                swap(arr[parentIndex], arr[index]);
                swap(name[parentIndex], name[index]);
                index = parentIndex;
            }
            else
            {
                break; 
            }
        }
    }

    void print()
    {
        cout << "Name->Score " << endl;
        for (int i = 0; i < size; i++)
        {
            // Display only the first 5 characters of the name
            string Name5 = name[i].substr(0, 5);
            if (i == 0)
            {
            }
            else
            {
                cout << i << ". " << Name5 << " -> " << arr[i] << endl;
            }
        }
    }
};
