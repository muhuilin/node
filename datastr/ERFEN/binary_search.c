/*************************************************************************
	> File Name: binary_search.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月27日 星期六 19时25分01秒
 ************************************************************************/
/*****************************************************************************************************
*                                                                                                    *
*                                      二分三分查找                                                  *
*                                                                                                    *
*****************************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define EPS 1e-6


int binary_search(int *num, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while(head <= tail) {
        mid = (head + tail) >> 1;
        if(num[mid] == x) return mid;
        if(num[mid] < x) head = mid + 1;
        else tail = mid - 1;
    }
    return -1;
}

int binary_search2(int *num, int n) {
    int head = -1, tail = n - 1, mid;
    while(head < tail) {
        mid = (head + tail + 1) / 2;
        if(num[mid] == 0) tail = mid - 1;
        else head = mid;
    }
    return head;
}

int binary_search3(int *num, int n) {
    int head = 0, tail = n, mid;
    while(head < tail) {
        mid = (head + tail ) / 2;
        if(num[mid] == 0) head = mid + 1;
        else tail = mid;
    }
    if(head == n) return -1;
    return head;
}

int binary_search4(int *num, int n) {
    int l = 0, r = n - 1, mid;
    while(l <= r) {
        mid = (l + r) / 2;
        if(jug(mid)) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return ？;
}


double f(double x) {
    static double a = 3.0, b = 2.0, c = 9.0;
    return a * x * x + b * x + c;
}

double ternary_search(double (*func)(double)) {
    double L = -1000, R = 1000, m1, m2;
    while(fabs(L - R) > EPS) {
        m1 = L + (R - L) / 3.0;
        m2 = L + 2.0 * (R - L) / 3.0;
        if(func(m1) > func(m2)) L = m1;
        else R = m2;
    }
    return L;
}

int main() {
    int num1[] = {1, 2, 3, 4, 5};
    printf("%d \n", binary_search(num1, 5, 4));
    int num2[] = {1,1,1,1,1,1,1,1,1,1,0,0,0,0,0};
    printf("%d \n", binary_search2(num2, 15));
    int num3[] = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1};
    printf("%d \n", binary_search3(num3, 15));
    printf("%lf \n",ternary_search(f));
    return 0;
}



/*_______________
*****************

.................
*****************

*
int a,b,c;

double binary_search(double x) {
    return a * x * x + b * x + c;
}


int main()
{
    *
    double l = 0.0, r = 99999.0;
    while(fabs(r - l) < EPS) {
        double mid1 = l + (r - l) / 3;
        double mid2 = r - (r - l) / 3;
        if(binary_search(mid1) - binary_search(mid2) < 0) {
            l = mid1;
        }
        else {
            r = mid2;
        }
    }
    int l = 0, r = 12;
    int num[12] = {1,2,3,4,5,6,5,3,1,1,1,0};
    while(l < r) {
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;
        if(num[mid1] < num[mid2]) {
            l = mid1 + 1;
        }
        else {
            r = mid2 - 1;
        }
    }
    printf("%d %d\n", num[l], l);

}
*/

