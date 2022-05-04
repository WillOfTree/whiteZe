# leetcode做题记录

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
