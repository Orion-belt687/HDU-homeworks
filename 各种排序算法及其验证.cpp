#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <math.h> 
//冒泡ok，简单选择ok，简单插入ok，快排ok，归并排序ok，计数排序ok，桶排序ok?，基数排序ok
//这里都是从小到大排的！！！！！！！！！！！！
//随机数组生成ok，排序检查ok及计时函数
#define TIME_LIMIT 300 // 5分钟，单位为秒

int bubble(int A[],int len){//冒泡排序
    clock_t start = clock();
    int i,j;
    for(i=0;i<len;i++){
        for(j=0;j<len-i-1;j++){
            if ((clock() - start) / CLOCKS_PER_SEC > TIME_LIMIT) {
                printf("bubble: 超时终止\n");
                return 1;
            }
            if(A[j]>A[j+1]){
                int temp=A[j];
                A[j]=A[j+1];
                A[j+1]=temp;
            }
        }
    }
    return 0;
}
int simple(int A[],int len){//简单排序
    clock_t start = clock();
    for(int i=0;i<len;i++){
        if ((clock() - start) / CLOCKS_PER_SEC > TIME_LIMIT) {
                printf("simple: 超时终止\n");
                return 1;
            }
        int mininow=i;
        for(int j=i+1;j<len;j++){
            if(A[j]<A[mininow]){
                mininow=j;
            }
        }
        if(mininow!=i){
            int temp=A[i];
            A[i]=A[mininow];
            A[mininow]=temp;
        }
    }
    return 0;
}
int insert(int A[],int len){//插入
    clock_t start = clock();
    for(int i=1;i<len;i++){
        if ((clock() - start) / CLOCKS_PER_SEC > TIME_LIMIT) {
            printf("insert: 超时终止\n");
            return 1;
        }
        int temp=A[i];
        int j=i-1;
        while(j>=0&&A[j]>temp){
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=temp;
    }
    return 0;
}
void quick(int A[],int low,int high){//快速排序
    if (low < high) {
        // 随机选取枢轴并交换到 A[low]
        int pivotIndex = low + rand() % (high - low + 1);
        int temp = A[low];
        A[low] = A[pivotIndex];
        A[pivotIndex] = temp;

        int i = low, j = high;
        int key = A[low];
        while (i < j) {
            while (i < j && A[j] >= key) j--;
            if (i < j) A[i++] = A[j];
            while (i < j && A[i] <= key) i++;
            if (i < j) A[j--] = A[i];
        }
        A[i] = key;
        quick(A, low, i - 1);
        quick(A, i + 1, high);
    }
}
void merge(int A[],int low,int high){//归并
    int mid=(low+high)/2;
     if (low < high) {
        merge(A, low, mid);
        merge(A, mid + 1, high);
        int* temp = (int*)malloc((high - low + 1) * sizeof(int));
        int i = low, j = mid + 1, k = 0;
        while (i <= mid && j <= high) {
            if (A[i] <= A[j]) temp[k++] = A[i++];
            else temp[k++] = A[j++];
        }
        while (i <= mid) temp[k++] = A[i++];
        while (j <= high) temp[k++] = A[j++];
        for (int t = 0; t < k; t++) {
            A[low + t] = temp[t];
        }
        free(temp);
    }
}
void count(int A[],int len){//计数排序
    // 1. 找到最大值
    int max = A[0];
    for (int i = 1; i < len; i++) {
        if (A[i] > max) max = A[i];
    }
    // 2. 分配计数数组
    int* temp = (int*)calloc(max + 1, sizeof(int));
    // 3. 计数
    for (int i = 0; i < len; i++) {
        temp[A[i]]++;
    }
    // 4. 回写
    int pos = 0;
    for (int i = 0; i <= max; i++) {
        while (temp[i] > 0) {
            A[pos++] = i;
            temp[i]--;
        }
    }
    free(temp);
}
void bucket(int A[],int len){//桶排序，桶的大小为1
    int max = A[0];
    for (int i = 1; i < len; i++) {
        if (A[i] > max) max = A[i];
    }
    int* temp = (int*)calloc(max + 1, sizeof(int));
    for (int i = 0; i < len; i++) {
        temp[A[i]]++;
    }
    int pos = 0;
    for (int i = 0; i <= max; i++) {
        while (temp[i] > 0) {
            A[pos++] = i;
            temp[i]--;
        }
    }
    free(temp);
}
void radix(int A[],int len){//基数排序
    int max = A[0];
    for (int i = 1; i < len; i++) {
        if (A[i] > max) max = A[i];
    }
    // 计算最大数的位数
    int exp = 1;
    int* output = (int*)malloc(len * sizeof(int));
    while (max / exp > 0) {
        int bucket[10] = {0};
        // 统计每个桶中的元素个数
        for (int i = 0; i < len; i++) {
            bucket[(A[i] / exp) % 10]++;
        }
        // 计算前缀和，确定每个元素在output中的位置
        for (int i = 1; i < 10; i++) {
            bucket[i] += bucket[i - 1];
        }
        // 从后往前遍历，保证稳定性
        for (int i = len - 1; i >= 0; i--) {
            int idx = (A[i] / exp) % 10;
            output[--bucket[idx]] = A[i];
        }
        // 拷贝回原数组
        for (int i = 0; i < len; i++) {
            A[i] = output[i];
        }
        exp *= 10;
    }
    free(output);
}
int check(int A[],int len){//检查排序是否正确
    for(int i=0;i<len-1;i++){
        if(A[i]>A[i+1]){
            printf("error!\n");
            return 1;
        }
    }
    //printf("ok\n");
    return 0;
}
void createrandom(int A[],int len){//完全随机数组
    for(int i=0;i<len;i++){
        A[i]=rand()%len;
    }
}
void createswap(int A[],int len){//有序数组换位置
    for(int i=0;i<len;i++){//先出有序数组
        A[i]=i;
    }
    int swap=len/5;
    for(int i=0;i<swap;i++){//调换五分之二的数的位置
        int first=rand()%len;
        int second=rand()%len;
        int t=0;
        t=A[first];
        A[first]=A[second];
        A[second]=t;
    }
}
void Try(int A[],int len){
    int* B = (int*)malloc(len * sizeof(int));
    clock_t start, end;

    // 冒泡排序
    memcpy(B, A, len * sizeof(int));
    start = clock();
    int i=bubble(B, len);
    end = clock();
    if(i==0){
        printf("bubble: %ld ms in Windows/ns in LUNIX\n", end - start);
        check(B, len);
    }

    // 简单选择排序
    memcpy(B, A, len * sizeof(int));
    start = clock();
    int j=simple(B, len);
    end = clock();
    if(j==0){
    printf("simple: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);
    }

    // 插入排序
    memcpy(B, A, len * sizeof(int));
    start = clock();
    int k=insert(B, len);
    end = clock();
    if(k==0){
    printf("insert: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);
    }

    // 快速排序
    memcpy(B, A, len * sizeof(int));
    start = clock();
    quick(B, 0, len - 1);
    end = clock();
    printf("quick: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);

    // 归并排序
    memcpy(B, A, len * sizeof(int));
    start = clock();
    merge(B, 0, len - 1);
    end = clock();
    printf("merge: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);

    // 计数排序
    memcpy(B, A, len * sizeof(int));
    start = clock();
    count(B, len);
    end = clock();
    printf("count: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);

    // 桶排序
    memcpy(B, A, len * sizeof(int));
    start = clock();
    bucket(B, len);
    end = clock();
    printf("bucket: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);

    // 基数排序
    memcpy(B, A, len * sizeof(int));
    start = clock();
    radix(B, len);
    end = clock();
    printf("radix: %ld ms in Windows/ns in LUNIX\n", end - start);
    check(B, len);

    printf("\n");
    free(B);
}
int main(){
    int A[100];
    printf("100打乱数组:\n");
    createswap(A,100);
    Try(A,100);
    printf("100随机数组:\n");
    createrandom(A,100);
    Try(A,100);

    int B[1000];
    printf("1000打乱数组:\n");
    createswap(B,1000);
    Try(B,1000);
    printf("1000随机数组:\n");
    createrandom(B,1000);
    Try(B,1000);

    int C[10000];
    printf("10000打乱数组:\n");
    createswap(C,10000);
    Try(C,10000);
    printf("10000随机数组:\n");
    createrandom(C,10000);
    Try(C,10000);

    int D[100000];
    printf("100000打乱数组:\n");
    createswap(D,100000);
    Try(D,100000);
    printf("100000随机数组:\n");
    createrandom(D,100000);
    Try(D,100000);

    int *E=(int *)malloc(1000000*sizeof(int));
    printf("1000000打乱数组:\n");
    createswap(E,1000000);
    Try(E,1000000);
    printf("1000000随机数组:\n");
    createrandom(E,1000000);
    Try(E,1000000);
    free(E);
    return 0;
}
