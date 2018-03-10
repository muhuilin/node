
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Trie {
	int flag;
	struct Trie* next[26];
} Trie;

typedef struct DATrie {
	int *check, *base, *fail;
} DATrie;

void da_init(DATrie* datree, int n) {
	datree->check = (int*)calloc(sizeof(int), n);
	datree->base = (int*)calloc(sizeof(int), n);
	datree->fail = (int*)calloc(sizeof(int), n);
}
int get_baseval(Trie* tree, DATrie* datree) {
	int val = 1;
	Trie* p = tree;
	int flag = 1;
	while(flag) {
		flag = 0;
	val++;
		for(int i = 0; i < 26; i++) {
			if(p->next[i] == NULL) continue;
			if(datree->check[i + val] == 0) continue;
			flag = 1;
			break;
		}
	}
	return val;
}

int zhuan(Trie* tree, DATrie* datree, int ind) {
	int maxn = 0, tmp = 0;
	int base_val = datree->base[ind];
	Trie* p = tree;
	for(int i = 0; i < 26; i++) {
		if(p->next[i] == NULL) continue;
		datree->check[i + base_val] = (p->next[i]->flag == 1 ? -ind : ind);
        tmp = (tmp > i +  ? tmp : (i + base_val));
	}
	for(int i = 0; i < 26; i++) {
		if(p->next[i] == NULL) continue;
		datree->base[base_val + i] = get_baseval(p->next[i], datree);
		maxn = zhuan(p->next[i], datree, base_val + i);
		maxn = (tmp > maxn ? tmp : maxn);
	}
	return maxn;
}
///**************************************************************************************************
int has_child(DATrie* datree, int ind, int i) {
	if(datree == NULL) return 0;
	int base_val = datree->base[ind];
	int fa = datree->check[base_val + i];
	return (fa == ind || fa == ind * (-1));
}  

void build_automaintain(DATrie* datree, int sum) {
	int* que = (int*)malloc(sizeof(int) * (sum));
	int head = 0, tail = 0;
	que[tail++] = 1;
	datree->fail[1] = sum + 1;   //关键： 把根结点的fail指针值设置为sum+1,用以区分根结点
	while(head < tail) {
		int now = que[head++], base_val = datree->base[now];
		for(int i = 0; i < 26; i++) {
			if(!has_child(datree, now, i)) continue;
			int q = datree->fail[now];
			while(q != (sum + 1) && !has_child(datree, q, i)) {
				q = datree->fail[q];
			}
			if(q != (sum + 1)) {
				int tmp = datree->base[q] + i;
				datree->fail[i + base_val] = tmp;
			}
			else datree->fail[i + base_val] = 1;
			que[tail++] = base_val + i;
		}
	}
	return;


}






int ac_search(DATrie* datree, const char* str) {


	if(str == NULL) return 0;


	int ans = 0, p = 1, q;


	while(str[0]) {


		int tmp = str[0] - 'a';


		while(p && !has_child(datree, p, tmp)) {


			p = datree->fail[p];


		}


		if(p) p = datree->base[p] + tmp;


		else p = 1;


		q = p;


		while(q != 0) ans += (datree->check[q] < 0 ? 1 : 0), q = datree->fail[q];


		str++;


	}


	return ans;


}






///*****************************************************************************************************






Trie* get_node() {


	Trie* p = (Trie*)malloc(sizeof(Trie));


	p->flag = 0;


	for(int i = 0; i < 26; i++) {


		p->next[i] = NULL;


	}


	return p;


}

int insert(Trie* tree, const char* str) {
	if(tree == NULL || str == NULL) return 0 ;
	Trie* p = tree;
	int ans = 0;
	while(str[0]) {
		if(p->next[str[0] - 'a'] == NULL) {
			p->next[str[0] - 'a'] = get_node();
			ans++;
		}
		p = p->next[str[0] - 'a'];
		str++;
	}
	p->flag = 1;
	return ans;
}

int search(Trie* tree, char* str) {
	if(tree == NULL || str == NULL) return 0;
	Trie* p = tree;
	while(str[0] && p) {
		if(p->next[str[0] - 'a'] == NULL) return 0;
		p = p->next[str[0] - 'a'];
		str++;
	}
	return p && p->flag;
}

int main()
{
	int sum = 0;
	char* str = (char*)malloc(sizeof(char) * 100);
	Trie* tree = (Trie*)malloc(sizeof(Trie));
	for(int i = 0; i < 3; i++) {
		scanf("%s", str);
		sum += insert(tree, str);
	}
	DATrie* datree = (DATrie*)malloc(sizeof(DATrie));
	da_init(datree, sum * 26);
	datree->base[1] = 2;
	int maxn = zhuan(tree, datree, 1);
	build_automaintain(datree, sum + 5);/////sum is val
	scanf("%s", str);
	printf("%d\n", ac_search(datree, str));
	for(int i = 1; i <= maxn; i++) {
		printf("(%d %d %d %d)  ", i, datree->base[i], datree->check[i], datree->fail[i]);
		if(i % 3 == 0) printf("\n");
	}

}



