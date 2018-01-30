/*************************************************************************
	> File Name: hash_table.c
	> Author:  muhuilin 
	> Mail:  
	> Created Time: 2018年01月28日 星期日 09时26分18秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct HashTable {
    int *data, *flag;
    int size;
    int cnt;
} HashTable;

HashTable * init(int n) {
    HashTable *p = (HashTable *) malloc(sizeof(HashTable));
    p->data = (int *)malloc(sizeof(int) * n * 2);
    int size = 2 * n / 30 + 1;
    p->flag = (int *)calloc(size, sizeof(int));
    p->size = 2 * n;
    p->cnt = 0;
    return p;
}

void clear(HashTable *p) {
    if(p == NULL) return ;
    free(p->data);
    free(p);
    return ;
}

int has_val(HashTable *p, int ind) {
    int x = ind / 30, y = ind % 30;
    return p->flag[x] & (1 << y);
}

int set_val(HashTable *p, int ind, int val) {
    int x = ind / 30, y = ind % 30;
    p->data[ind] = val;
    p->flag[x] |= (1 << y);
    p->cnt ++;
}

int hash(HashTable * p, int x) {
    return (x % p->size + p->size) % p->size;
}

int hash_conflict(HashTable *p, int *ind, int val) {
    int times = 0, temp_ind = *ind;
    while(has_val(p, temp_ind) && p->data[temp_ind] != val) {
        temp_ind += (++times);
        temp_ind %= p->size;
    }
    *ind = temp_ind;
    return times;
}

int search(HashTable *p, int val) {
    int ind = hash(p, val);
    hash_conflict(p, &ind, val);
    return has_val(p, val);
}

int insert(HashTable * p, int val) {
    if(p->cnt * 2 >= p->size) {
        return 0;
    }
    int ind = hash(p, val);
    hash_conflict(p, &ind, val);

    if(p->data[ind] == val) return 0;
    set_val(p, ind, val);
    return 1;
}

int main()
{
    int op, val;
    HashTable * hashtable = init(100);
    while(~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 1: 
                insert(hashtable, val);
            case 2:
                printf("val = %d ind =  %d\n", val, search(hashtable, val));
            default : fprintf(stderr,"ERROR\n");
            break;
        }
    }
}
