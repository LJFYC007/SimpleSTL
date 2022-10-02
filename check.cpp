#include "vector.h"

struct sum
{
    int a, b;
};

int main()
{
    vector<int> a(100, 0);
    vector<sum> b;
    vector<int> c(a);


    return 0;
}
