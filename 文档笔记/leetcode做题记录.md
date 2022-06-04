# leetcode做题记录

1.暴力算法对于一些无序，无法排序，排序没有意义的特别好用。
2.对于无序序列，一般方法为，将无序序列变成有序序列后在进行操作。
3.对于2个数组，可用双指针，进行依次比较数据。
4.对于查找位置的相关题目，都可用二分查找法。

## 217.存在重复元素

给你一个整数数组 `nums` 。如果任一值在数组中出现 **至少两次** ，返回 `true` ；如果数组中每个元素互不相同，返回 `false` 。

**示例 1：**

```c
输入：nums = [1,2,3,1]
输出：true

输入：nums = [1,2,3,4]
输出：false
```

**解题方法：**

// 直接排序，选择排序，冒泡等排序都太慢了，推荐使用C语言定义的qsort函数进行排序
// 使用排序算法，将数组排序形成有序数列，当当前字符与后一个字符相同时，则有重复

```c
void insertSort(int arr[], int num)
{
    int i,j,temp;
    // 第一个是有序的
    for(i=1; i<num; ++i)
    {
        temp = arr[i];
        j=i-1;
        //temp<arr[j] 前小后大，正序
        while(j >=0 && temp < arr[j])
        {
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = temp;
    }
}

bool containsDuplicate(int* nums, int numsSize){
    insertSort(nums, numsSize);
    int i;
    //numsSize-1是为了防止指针越界
    for(i=0; i<numsSize-1; ++i)
    {
        // 注意：这里nums[i+1]时，当i为最后一个数时会指针越界
        if(nums[i] == nums[i+1])
        {
            return true;
        }
    }
    return false;
}
```

## 1. 两数之和

给定一个整数数组nums和一个整数目标值 target,请你在该数组中找出和为目标值target的那两个整数，并返回它们的数组下标。

**示例:**

``` c
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
```

**解题方法:**

// 暴力求解，遍历数组，验证每一个数之和是否与目标数字相同

``` c
// returnsize是返回数组rearr大小
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i,j;
    // 因为函数内变量是在栈，出去函数会消失，所以要用malloc
    int *rearr = (int*)malloc(sizeof(int)*2);
    for(i=0; i<numsSize; i++)
    {
        for(j=i+1; j<numsSize; j++)
        {
            int mytest = nums[i] + nums[j];
            if(mytest == target)
            {
                rearr[0] = i;
                rearr[1] = j;
                // 因为returnSize是指针，所以要用*returnSize
                *returnSize = 2 ;
                return rearr;
            }
        }
    }
    return 1;
}
```

## 合并两个有序数组

给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。
请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。

**示例:**
> 输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3\
> 输出：[1,2,2,3,5,6]\
> 解释：需要合并 [1,2,3] 和 [2,5,6] 。\
> 合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。

**解题方法:**

// 方法1：直接合并数组，然后进行排序。

// 方法2：双指针。

``` c
// 先合并，在排序
int cmp(int* a, int* b) {
    return *a - *b;
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    for (int i = 0; i != n; ++i) {
        nums1[m + i] = nums2[i];
    }
    qsort(nums1, nums1Size, sizeof(int), cmp);
}

// 双指针 -----------------------------------------------------
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
    int *a = (int*)malloc(sizeof(int)*m);
    memcpy(a, nums1, sizeof(int)*m);

    int i=0, j=0, k=0;

    while(i<m && j<n)
    {
        if(a[i] < nums2[j])
        {
            nums1[k] = a[i];
            ++k;
            ++i;
        }else{
            nums1[k] = nums2[j];
            ++k;
            ++j;
        }
    }
    // 将剩余的元素添加进数组
    if(j < n)
    {
        int b;
        for(b=j; b<n; ++b)
        {
            nums1[k] = nums2[b];
            ++k;
        }
    }else{
        int b;
        for(b=i; b<m; ++b)
        {
            nums1[k] = a[b];
            ++k;
        }
    }

    return 0;
}
```

## 350 两个数组的交集

给你两个整数数组 nums1 和 nums2 ，请你以数组形式返回两数组的交集。返回结果中每个元素出现的次数，应与元素在两个数组中都出现的次数一致（如果出现次数不一致，则考虑取较小值）。可以不考虑输出结果的顺序。

**示例:**

>输入：nums1 = [1,2,2,1], nums2 = [2,2]\
>输出：[2,2]

**解题方法:**

// 先将数组变成有序，然后利用双指针,依次对比每一个数

``` c
int cmp(const void* _a, const void* _b) 
{
    int *a = _a, *b = (int*)_b;
    return *a == *b ? 0 : *a > *b ? 1 : -1;
}

int *intersect(int* nums1, int nums1Size, int* nums2, int nums2Size,int* returnSize) 
{
    // 排序算法，将数组变成有序
    qsort(nums1, nums1Size, sizeof(int), cmp);
    qsort(nums2, nums2Size, sizeof(int), cmp);
    *returnSize = 0;
    // fmin(a,b)是返回a,b的较小整数
    int* intersection = (int*)malloc(sizeof(int) * fmin(nums1Size, nums2Size));
    int index1 = 0, index2 = 0;
    // 循环对比数组，将数小的数组下标+1
    // 相等的话，都要加1，
    while (index1 < nums1Size && index2 < nums2Size) {
        if (nums1[index1] < nums2[index2]) {
            index1++;
        } else if (nums1[index1] > nums2[index2]) {
            index2++;
        } else {
            intersection[(*returnSize)++] = nums1[index1];
            index1++;
            index2++;
        }
    }
    return intersection;
}
```

## 买股票的最佳时机

给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。
设计一个算法来计算你所能获取的最大利润。返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。

**示例:**

> 输入：[7,1,5,3,6,4]\
> 输出：5\
> 解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
> 注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。

**解题方法:**

// 暴力重复判断，
// 先拿出第1个数k，循环找出之后比k大的数，如果没有比k大的数，则这个就没有收益，将K+1
// 对找出的数进行收益计算，必定是多个，再从中找到最大的收益

## 第一个错误的版本

假设你有 n 个版本 [1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。

**示例:**

> 输入：n = 5, bad = 4
> 输出：4
> 解释：
> 调用 isBadVersion(3) -> false
> 调用 isBadVersion(5) -> true
> 调用 isBadVersion(4) -> true
> 所以，4 是第一个错误的版本。

**解题方法:**

// 可以先用查找，找到合适位置，再进行判断

``` c
int firstBadVersion(int n) {
    int left = 1, right = n;
    while (left < right) {  // 循环直至区间左右端点相同
        int mid = left + (right - left) / 2;  // 防止计算时溢出
        if (isBadVersion(mid)) {
            right = mid;  // 答案在区间 [left, mid] 中
        } else {
            left = mid + 1;  // 答案在区间 [mid+1, right] 中
        }
    }
    // 此时有 left == right，区间缩为一个点，即为答案
    return left;
}
```

## 收索插入位置

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

**示例：**

> 输入: nums = [1,3,5,6], target = 5
> 输出: 2

**解题方法:**

// 可以先用二差查找法，查找位置，然后再进行插入（非官方）
// 

``` c
int searchInsert(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1, ans = numsSize;
    while (left <= right) {
        int mid = ((right - left) >> 1) + left;
        if (target <= nums[mid]) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}
```
