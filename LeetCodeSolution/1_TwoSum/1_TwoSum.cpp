#include <vector>
#include <iostream>
#include <time.h>
#include <unordered_map>

using namespace std;

// When N = 20000, time needs about 144ms
vector<int> twoSumNaive(vector<int>& nums, int target) {
    int size = nums.size();
    vector<int> result;
    bool flag = false;
    for (int i = 0; i < size - 1; i++)
    {
        if (flag == false)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (nums[i] + nums[j] == target)
                {
                    result.push_back(i);
                    result.push_back(j);
                    flag = true;
                    break;
                }
            }
        }
        else
            break;
    }
    return result;
}

// When N = 20000, time needs about 144ms
vector<int> twoSum(vector<int>& nums, int target) {
    int size = nums.size();
    int *data = nums.data();
    int *end = data + size;
    int *first = data;
    int *second = first + 1;
    vector<int> result;
    int err;

    while (first < end)
    {
        err = target - *first;
        while (second < end)
        {
            if (err == *second)
            {
                result.push_back(first - data);
                result.push_back(second - data);
                return(result);
            }
            second++;
        }
        second = ++first;
    }
    return(result);
}

// 讨论区给出的优质答案，使用了unordered_map这样的hash表数据结构，
// http://www.cplusplus.com/reference/unordered_map/unordered_map/
// When N = 20000 and most of them are zeors, time needs about 0ms...

vector<int> twoSumMap(vector<int>& nums, int target) {
    vector<int> res;
    unordered_map<int, int> m;
    int index = 0;

    for (auto val : nums) {
        m.insert({ val,index++ });
    }

    index = 0;
    for (auto val : nums) {
        if (m.count(target - val)) {
            if (m[target - val] == index) {
                index++; continue;
            }
            res.push_back(index);
            res.push_back(m[target - val]);
            return res;
        }
        index++;
    }
    return res;
}

int main(int argc, char **argv)
{
    int N = 20000;// atoi(argv[1]);
    int *data = new int[N] {0};

    vector<int> input(data, data+N);

    input.push_back(2);
    input.push_back(7);

    int target = 9;

    clock_t start = clock();
    vector<int> result = twoSumMap(input, target);
    
    printf("Time = %.4fms, [%d, %d]", double(clock()-start)/CLOCKS_PER_SEC*1000, result[0], result[1]);

    return 0;
}