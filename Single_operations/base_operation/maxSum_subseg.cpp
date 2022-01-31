// максимальная сумма подотрезка
#include <iostream>
#include <vector>
#include <algorithm>

struct Node{
    int64_t seg;    // максимальная сумма на подотрезке
    int64_t pref;   // максимальная сумма префикса
    int64_t suf;    // максимальная сумма суффикса
    int64_t sum;    // cумма на отрезке

    Node(const int64_t seg_sum, const int64_t pref_sum, const int64_t suf_sum, const int64_t sum_sum): seg(seg_sum), pref(pref_sum), suf(suf_sum), sum(sum_sum) {};
};

struct segment_tree{
    int64_t size;
    std::vector<Node> tree;

    void init(const int64_t n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size-1, {0, 0, 0, 0});
    }

    void set(const int64_t i, const int64_t v){
        set(i, v, 0, 0, size);
    }

    void set(const int64_t i, const int64_t v, int64_t x, int64_t left, int64_t rigth){
        if(rigth-left == 1){
            if(v <= 0){
                tree[x].seg  = 0;
                tree[x].pref = 0;
                tree[x].suf  = 0;
            }else{
                tree[x].seg  = v;
                tree[x].pref = v;
                tree[x].suf  = v;
            }

            tree[x].sum = v;
            return;
        }

        int64_t m = (left+rigth)/2;
        if(i < m) set(i, v, 2*x+1, left, m);
        else set(i, v, 2*x+2, m, rigth);
        
        tree[x].seg  = std::max(tree[2*x+1].seg, std::max(tree[2*x+2].seg, tree[2*x+1].suf+tree[2*x+2].pref));
        tree[x].pref = std::max(tree[2*x+1].pref, tree[2*x+1].sum + tree[2*x+2].pref);
        tree[x].suf  = std::max(tree[2*x+2].suf, tree[2*x+2].sum + tree[2*x+1].suf);
        tree[x].sum  = tree[2*x+1].sum + tree[2*x+2].sum;
    }

    int64_t max_segment(){
        return tree[0].seg;
    }
};

int main(){
    int64_t n, m; std::cin >> n >> m;

    segment_tree T; T.init(n);
    for(int64_t i = 0; i < n; i++){
        int64_t v; std::cin >> v;
        T.set(i, v);
    }
    std::cout << T.max_segment() << std::endl;
    for(int64_t _ = 0; _ < m; _++){
        int64_t i, v; std::cin >> i >> v;
        T.set(i, v);
        std::cout << T.max_segment() << std::endl;
    }

    return 0;
}
