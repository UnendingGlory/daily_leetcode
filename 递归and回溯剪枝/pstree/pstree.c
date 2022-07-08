#define TRUE 1
#define FALSE 0
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>

long ProcCount = 384;

char C[5][4] = {
    "─",
    "┬",
    "├",
    "└",
    "│"
};

struct proc {
    char name[32];
    long pid; // process id
    long ppid; // parent process id
    long parent, child, sister; // idx
} *Proc;

void read_tree() {
    FILE* f = fopen("list.txt", "r");
    if (f == NULL) {
        printf("File cannot open! " );
        exit(0);
    }
    for (int i = 0; i < ProcCount; i++) {
        fscanf(f, "%s %ld %ld %ld %ld %ld\n", Proc[i].name, &Proc[i].pid, &Proc[i].ppid, &Proc[i].parent, &Proc[i].child, &Proc[i].sister);
    }
    fclose(f);
}

// the function you need to complete
// you need to custom the argument
int name_len[100] = {0}; // 模拟栈
int p_idx[100] = {-1}; // 栈中元素的id
int i = -1, j = -1;
void dfs(long cur) {
    long child = Proc[cur].child, sister = Proc[cur].sister;
    if (child != -1) {
        printf("%s%s%s%s", C[0], Proc[child].sister == -1? C[0] : C[1], C[0], Proc[child].name);
        name_len[++i] = strlen(Proc[child].name); // 入栈
        p_idx[++j] = child;
        dfs(child);
        --i, --j;
    } else {
        printf("\n");
    }
    
    if (sister != -1) {
        for (int m = 0; m < i - 1; ++m) {
            for (int k = 0; k < name_len[m]; ++k) printf(" ");
            printf(" %s ", Proc[p_idx[m+1]].sister == -1 ? " " : C[4]);
        }
        for (int k = 0; k < name_len[i - 1]; ++k) printf(" ");
        printf(" %s%s%s", Proc[sister].sister == -1? C[3] : C[2], C[0], Proc[sister].name);
        name_len[i] = strlen(Proc[sister].name); // 更改当前层的长度
        p_idx[j] = sister;
        dfs(sister); // 再遍历sister
    }
}

void print_tree() {
    printf("%s", Proc[0].name);
    name_len[++i] = strlen(Proc[0].name);
    p_idx[++j] = 0;
    dfs(0);
}

int main(int argc, char *argv[]) {
    Proc = calloc(ProcCount, sizeof(struct proc));
    read_tree();
    
    // here to call print_tree
    // .......
    print_tree();

    free(Proc);
    return 0;
}
