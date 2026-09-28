#include <iostream>
#include <iomanip>

// For 6 integers a, b, c, d, e, and f, find the average value of those that are both odd numbers and multiples of 3
// Then print the result with 4 decimal places

int main()
{
    int a, b, c, d, e, f;
    std::cin >> a >> b >> c >> d >> e >> f;

    int arr[] = { a, b, c, d, e, f };
    int total = 0;
    int count = 0;

    for (int i = 0; i < 6; i++)
    {
        int num = arr[i];
        if (num % 2 == 0)
        {
            continue;
        }
        if (num % 3 == 0)
        {
            total += num;
            count++;
        }
    }

    if (count == 0)
    {
        std::cout << std::fixed << std::setprecision(4) << (0.0);
        return 0;
    }
    std::cout << std::fixed << std::setprecision(4) << ((double)total / count);
}