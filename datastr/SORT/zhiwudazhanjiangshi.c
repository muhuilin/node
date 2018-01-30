/*************************************************************************
	> File Name: zhiwudazhanjiangshi.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年01月24日 星期三 20时47分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define swap(a, b) {\
    typeof(a) __temp = a;\
    a = b; b = __temp;\
}


typedef struct jiangshi {
    int first;
    int second;
    int id;
}jiangshi;

void merge_sort(jiangshi *js, int l, int r) {
    if(l == r) return ;
    int mid = (l + r) >> 1;
    merge_sort(js, l, mid);
    merge_sort(js, mid + 1, r);
    int x = l, y = mid + 1, loc = 0;
    jiangshi *tmp = (jiangshi *)malloc(sizeof(jiangshi) * (r - l + 1));
    while(x <= mid || y <= r) {
        if(x <= mid && (y > r || js[x].second < js[y].second || (js[x].second == js[y].second && js[x].id < js[y].id) )) {
            tmp[loc++] = js[x++];
        }
        else  {
            tmp[loc++] = js[y++];
        }
    }
   /* printf("This is a merge_sort :");
    for(int i = 0; i < loc ; i++) {
        printf("%d ", tmp[i].second);
    }
    printf("\n");*/
    memcpy(js + l, tmp,sizeof(jiangshi) * loc);
    /*for(int i = l; i <= r; i++) {
        printf("%d ", js[i].second);
    }
    printf("\n-------------------------\n");*/
    free(tmp);
    return ;
}

typedef struct Heap {
    jiangshi *data;
    int size;
}Heap;

Heap *init(int len) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->data = (jiangshi *)malloc(sizeof(jiangshi) * len);
    heap->size = 0;
    return heap;
}

int push(Heap *heap, jiangshi js) {
    heap->size += 1;
    heap->data[heap->size] = js;
    int loc = heap->size;
    int father = loc / 2;
    while(father && (heap->data[father].first < heap->data[loc].first || (heap->data[father].first == heap->data[loc].first && heap->data[father].id > heap->data[loc].id) )) {
        swap(heap->data[father], heap->data[loc]);
        loc = father ;
        father = loc / 2;
    } 
    return 1;
}

int empty(Heap *heap) {
    //printf("hhhhhhhhhh           %p \n",heap);
    return heap->size == 0;
}
int pop(Heap *heap) {
    if(empty(heap)) return 0;
    swap(heap->data[1], heap->data[heap->size]);
    heap->size -= 1;
    int loc = 1;
    while(loc * 2 <= heap->size) {
        int l = loc * 2;
        int r = l + 1;
        int pos = loc;
        if(l <= heap->size && (heap->data[pos].first < heap->data[l].first || 
           (heap->data[pos].first == heap->data[l].first && heap->data[pos].id > heap->data[l].id))) {
            pos = l;
        }
        if(r <= heap->size && (heap->data[pos].first < heap->data[r].first || 
           (heap->data[pos].first == heap->data[r].first && heap->data[pos].id > heap->data[r].id))) {
            pos = r;
        }
        if(pos != loc) {
            swap(heap->data[pos], heap->data[loc]) ;
            loc = pos;
        }
        else break;
    }
    return 1;
    
}


jiangshi top(Heap *heap) {
    return heap->data[1];
}

int main()
{
    int t;
    int c = 0;
    scanf("%d", &t);
    printf("OK\n");
    Heap **heap = (Heap **)malloc(sizeof(Heap *) * 110);
    jiangshi *js = (jiangshi *)malloc(sizeof(jiangshi) * (50000 + 1));
    for(int i = 0; i <102; i++) {
        heap[i] = init(50000 + 10);
    }
    //printf("THIS IS RIGHT\n");
    while(t--) {
        int n;
        scanf("%d", &n);
        //jiangshi *js = (jiangshi *)malloc(sizeof(jiangshi) * (n + 1));
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &js[i].first, &js[i].second);
            js[i].id = i + 1;
           // printf("CAN IT\n");
            while(!empty(heap[i])) pop(heap[i]);
          //  printf("ERROR\n");
        }
        merge_sort(js, 0, n - 1);
       /* for(int i = 0; i < n; i++) {
            printf("%d %d %d \n", js[i].first, js[i].second, js[i].id);
        }*/
        int cur = 0;
        int m = 0;
        for(int i = 1; i < n; i++) {
            if(js[i].second != js[i - 1].second) {
                //heap[m] = init(i - cur + 1);

                while(cur != i) {
                    push(heap[m], js[cur++]);
                }
                m++;
            }
        }
        //heap[m] = init(n - cur);
        while(cur != n) {
            push(heap[m], js[cur++]);
        }
        m++;
     //   printf("m == %d\n", m);
        printf("Case #%d:\n",++c);
        for(int i = 0; i < n; i++) {
            int max = 0, id, ind;
           // printf("\nTIME ======== %d\n", i);
            for(int j = 0; j < m; j++) {
                if(!empty(heap[j])) {
                  //  printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA %d\n", j);
                  //  fflush(stdout);
                   // printf("%d ",top(heap[j]).id);
                    jiangshi tmp = top(heap[j]);
                    if(tmp.first + tmp.second * i > max) {
                        max = tmp.first + tmp.second * i;
                        id = tmp.id;
                        ind = j;
                    }
                    else if(tmp.first + tmp.second * i == max && id > tmp.id) {
                        id = tmp.id;
                        ind = j;
                    }
                }
            }
        //    printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        //    fflush(stdout);
            pop(heap[ind]);
            printf("%d", id);
            if(i != n - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}
