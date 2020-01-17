#include <stdio.h>
struct test
{
    /* data */
    int data;
    int type;
    char id;
};

struct test max(int num1, int num2)
{
    if (num1 > num2)
    {
        int data = num1;
    }
    else
    {
        int data = num2;
    }
    struct test result;
    result.data = num1;
    result.type = 1;
    result.id = 'z';
    return result;
}

struct test min(int num1, int num2)
{
    if (num1 > num2)
    {
        int data = num1;
    }
    else
    {
        int data = num2;
    }
    struct test result;
    result.data = num2;
    result.type = 1;
    result.id = 'j';
    return result;
};

int main()
{
    int a = 1;
    int b = 2;

    max(a, b);
    min(a, b);

    return 0;
}