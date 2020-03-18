#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using std::cout;
using std::endl;

int* GetSpliter(int* head, int* rear) {
    int mid = *head;     // 每一轮快排的锚点元素的大小
    int* i = head;
    int* j = rear;

    while (i < j) {
        while (*i <= mid && i < j) {
            i++;
        }

        while (*j >= mid && i < j) {
            j--;
        }

        if (i == j) {
            break;
        }
        std::swap(*i , *j);
//        cout << "i - head = " << i - head << endl;
//        cout << "j - head = " << j - head << endl;
//        cout << "after swap, arr is\n";
//        for (int* i = head; i <= rear; ++i) {
//            cout << *i << " ";
//        }
        cout << endl;

    }

    // 除非i指针1轮就走到了数组最末尾, 这样才可能出现i去触碰j指针但是j所在的元素小于mid，
    // 只要j动过一次，那么i去触碰j的时候j所在的元素肯定大于mid,
    // 如果是j去触碰i的情况,i所在的元素也肯定大于mid
    if (*i <= mid) {
        std::swap(*head, *i);
        return i;
    }

    std::swap(*head, *(i-1));
    return i-1;

}

void QucikSort(int* head, int* rear) {
    cout << endl << "begin quicksort" << endl;
    for (int* i = head; i <= rear; ++i) {
        cout << *i << " ";
    }
    cout << endl;
    if (head == rear) {
        return;
    }

    int * idx = GetSpliter(head, rear);  // 经过一轮快排后，spliter的指针指向了哪
    cout << "after get spliter, arr is\n";
    for (int* i = head; i <= rear; ++i) {
        cout << *i << " ";
    }
    cout << endl;

//    cout << "idx - head = " << idx - head << endl;
//    cout << "rear - idx = " << rear - idx << endl;
    if (idx - head > 1) {
//        cout << "do a QuickSort1" << endl;
        QucikSort(head, idx-1);
    }

    if (rear - idx > 1) {
//        cout << "do a QuickSort2" << endl;
        QucikSort(idx+1, rear);
    }

//    cout << "return a quicksort\n" << endl;
    return;
}

int main() {
    // Step0: 生成一个随机数组, 删除里面重复的元素, 打乱所有元素的顺序
    std::vector<int> numbers;
    int n = 30;
    int k = 7;
    for (int i = 0; i < n; ++i) {
        numbers.push_back(rand() % 100);
    }
//    for (int number : numbers) {
//        cout << number << " ";
//    }
//    cout << endl;
    // 注意这里消除重复元素的操作：
    // 1.把vector排序，因为unique只会检查相邻的元素是不是一样的，所以得先排好次序
    // 2.unique函数会把相邻重复的元素放到vector的末尾，并返回这段冗余元素的iterator
    // 3.用erase函数把vector尾部的这段冗余元素全部删除掉
//    std::sort(numbers.begin(), numbers.end());
//    auto iter = std::unique(numbers.begin(), numbers.end());
//    numbers.erase(iter, numbers.end());
//    n = numbers.size();

    // 因为上面的sort()函数对数组排序了，所以在这里重新random_shuffle一下整个数组
    std::random_shuffle(numbers.begin(), numbers.end());
    cout << "the numbers given is:\n";
    for (int number : numbers) {
        cout << number << " ";
    }
    cout << endl;

    // Step1: 冒泡排序，所有的全部排列完然后取前k个

    {
        std::random_shuffle(numbers.begin(), numbers.end());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (numbers[j] > numbers[j+1]) {
                    std::swap(numbers[j], numbers[j+1]);
                }
            }
        }

        cout << "after bubble, k least number is\n";
        for (int i = 0; i < k; ++i) {
            cout << numbers[i] << " ";
        }
        cout << endl;
    }


    // Step2: 还是冒泡排序，不过只冒k个泡
    {
        std::random_shuffle(numbers.begin(), numbers.end());
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (numbers[j] < numbers[j + 1]) {
                    std::swap(numbers[j], numbers[j + 1]);
                }
            }
        }

        cout << "after k bubble, k least number is\n";
        for (int i = 0; i < k; ++i) {
            cout << numbers[n-i-1] << " ";
        }
        cout << endl;
    }

    // Step3: 把前k个数当做一个泡来冒，其中前k个数用最大堆管理起来
    {
        std::random_shuffle(numbers.begin(), numbers.end());
        std::vector<int> nums(numbers.begin(), numbers.begin()+k);
//        nums.assign(numbers.begin(), numbers.begin()+k);
        std::make_heap(nums.begin(), nums.end(), std::less<int>());  // 构建最大堆

        for (int i = k; i < n; ++i) {
            if (numbers[i] < nums.front()) {
                // 注意这里对堆的操作：

                // 1.从堆里删除一个元素。绝大多数情况下都是删除根元素，所以首先pop_heap(), 这个函数会把根元素放到vector的末尾，
                // 然后再pop_back()，这个函数会把vector末尾的那一个元素删除。注意不是先pop_back()再pop_heap()，
                // 因为在heap中正常状态下vector.back()都不是根元素，pop它并没有什么意义，所以需要先用pop_heap()把根元素调到vector.back()

                // 2.往堆里插入一个元素。这个就简单了，首先push_back()，把元素加入到vector中，
                // 然后push_heap()重新整理一下堆里面元素的排列，保证根元素在vector.front()
                std::pop_heap(nums.begin(), nums.end(), std::less<int>());
                nums.pop_back();
                nums.push_back(numbers[i]);
                std::push_heap(nums.begin(), nums.end(), std::less<int>());
            }
        }
        cout << "after heap bubble, k least number is\n";
        for (int i = 0; i < k; ++i) {
            cout << nums[i] << " ";
        }
        cout << endl;
    }
    // Step3.5: 建立堆以及对堆的插入及删除操作

    // Step4: 快排，排到左子集或者右子集刚好size为k时，把这k个数拿出来当做结果
    {
//        std::random_shuffle(numbers.begin(), numbers.end());
        // 把vector作成int数组，便于调整位置
        int arr[n];
        for (int i = 0; i < n; ++i) {
            arr[i] = numbers[i];
        }

        QucikSort(arr, arr+n-1);

        for (int i = 0; i < n; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}