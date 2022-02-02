#include <iostream>
#include <vector>
#include <algorithm>

struct segment_tree{
    struct Node{
        int64_t max;        // максимум на отрезке
        int64_t secondMax;  // второй строгий максимум на отрезке
        int64_t cntMax;     // количевсвто максимумов на отрезке

        int64_t min;        // минимум на отрезке
        int64_t secondMin;  // второй строгий минимум на отрезке
        int64_t cntMin;     // количевство минимумов на отрезке 

        int64_t sum;        // сумма на отрезке
    };
    int64_t size;
    std::vector<Node> tree;

    void build_empty(int64_t x, int64_t left, int64_t right){
        if(right-left == 1){
            tree[x].max = tree[x].min = tree[x].sum = 0;
            tree[x].cntMax = tree[x].cntMin = 1;
            tree[x].secondMax = -1;
            tree[x].secondMin = 1e7;
        }
        else{
            int64_t m = (left+right)/2;
            build_empty(2*x+1, left, m);
            build_empty(2*x+2, m, right);
            updateFromChildren(x);
        }
    }

    void init(int64_t n){
        size = 1;
        while(size < n) size *= 2;
        tree.resize(2*size-1);
        build_empty(0, 0, size);
    }

    void updateFromChildren(int64_t x){
        tree[x].sum = tree[2*x+1].sum + tree[2*x+2].sum;
        tree[x].max = std::max(tree[2*x+1].max, tree[2*x+2].max);
        tree[x].secondMax = std::max(tree[2*x+1].secondMax, tree[2*x+2].secondMax);
        tree[x].cntMax = 0;
        if(tree[2*x+1].max == tree[x].max) {
            tree[x].cntMax += tree[2*x+1].cntMax;
        }else{
            tree[x].secondMax = std::max(tree[x].secondMax, tree[2*x+1].max);
        }
        if(tree[2*x+2].max == tree[x].max) {
            tree[x].cntMax += tree[2*x+2].cntMax;
        }else{
            tree[x].secondMax = std::max(tree[x].secondMax, tree[2*x+2].max);
        }

        tree[x].min = std::min(tree[2*x+1].min, tree[2*x+2].min);
        tree[x].secondMin = std::min(tree[2*x+1].secondMin, tree[2*x+2].secondMin);
        tree[x].cntMin = 0;
        if (tree[2*x+1].min == tree[x].min) {
            tree[x].cntMin += tree[2*x+1].cntMin;
        }else{
            tree[x].secondMin = std::min(tree[x].secondMin, tree[2*x+1].min);
        }
        if (tree[2*x+2].min == tree[x].min) {
            tree[x].cntMin += tree[2*x+2].cntMin;
        }else{
            tree[x].secondMin = std::min(tree[x].secondMin, tree[2*x+2].min);
        }
    }

    void updateNode(int64_t x, int64_t left, int64_t right, int64_t h){
        tree[x].min = tree[x].max = h;
        tree[x].cntMax = tree[x].cntMin = right - left;
        tree[x].secondMax = -1;
        tree[x].secondMin = 1e7;
 
        tree[x].sum = h*(right-left);
    }

    void updateMinNode(int64_t x, int64_t left, int64_t right, int64_t h){
        if(tree[x].min >= h) updateNode(x, left, right, h);
        else if(tree[x].max > h){
            if(tree[x].secondMin == tree[x].max) tree[x].secondMin = h;
            tree[x].sum -= (tree[x].max - h) * tree[x].cntMax;
            tree[x].max = h;
        }
    }

    void updateMaxNode(int64_t x, int64_t left, int64_t right, int64_t h){
        if(tree[x].max <= h) updateNode(x, left, right, h);
        else if(tree[x].min < h){
            if(tree[x].secondMax == tree[x].min) tree[x].secondMax = h;
            tree[x].sum += (h - tree[x].min) * tree[x].cntMin;
            tree[x].min = h;
        }
    }

    void min(int64_t l, int64_t r, int64_t h){
        min(l, r, h, 0, 0, size);
    }

    void updateToChildren(int64_t x, int64_t left, int64_t right){
        if(right-left == 1) return;

        int64_t m = (left+right)/2;

        updateMinNode(2*x+1, left, m, tree[x].max);
        updateMinNode(2*x+2, m, right, tree[x].max);
 
        updateMaxNode(2*x+1, left, m, tree[x].min);
        updateMaxNode(2*x+2, m, right, tree[x].min);
    }

    void min(int64_t L, int64_t R, int64_t h, int64_t x, int64_t left, int64_t right){
        if(L >= right || R <= left || tree[x].max <= h) return;
        if(L <= left && R >= right && tree[x].secondMax < h){
           updateMinNode(x, left, right, h);
           return;
        }

        updateToChildren(x, left, right);

        int m = (left + right) / 2;
        min(L, R, h, 2*x+1, left, m);
        min(L, R, h, 2*x+2, m, right);
        
        updateFromChildren(x);
    }

    void max(int64_t l, int64_t r, int64_t h){
        max(l, r, h, 0, 0, size);
    }

    void max(int64_t L, int64_t R, int64_t h, int64_t x, int64_t left, int64_t right){
        if(L >= right || R <= left || tree[x].min >= h) return;
        if(L <= left && R >= right && tree[x].secondMin > h){
           updateMaxNode(x, left, right, h);
           return;
        }

        updateToChildren(x, left, right);

        int m = (left + right) / 2;
        max(L, R, h, 2*x+1, left, m);
        max(L, R, h, 2*x+2, m, right);
        
        updateFromChildren(x);
    }

    int64_t sum(int64_t l, int64_t r){
        return sum(l, r, 0, 0, size);
    }

    int64_t sum(int64_t L, int64_t R, int64_t x, int64_t left, int64_t right){
        if(L >= right || R <= left ) return 0;
        if(L <= left && R >= right) return tree[x].sum;
        updateToChildren(x, left, right);
        int64_t m = (left+right)/2;
        int64_t s1 = sum(L, R, 2*x+1, left, m);
        int64_t s2 = sum(L, R, 2*x+2, m, right);
        return s1 + s2;
    }

    void print(){
        for(auto it : tree){
            std::cout << it.max << " " << it.cntMax << " " << it.sum << " " << it.secondMax << "\n";
        }
    }
};

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int64_t n, k; std::cin >> n >> k;
    segment_tree T; T.init(n);
    //T.print();
    for(int64_t _ = 0; _ < k; _++){
        int64_t t, l, r, h; std::cin >> t >> l >> r >> h;
        r++;
        if(t == 1){
            T.max(l, r, h);
            //T.print();
        }
        if(t == 2){
            T.min(l, r, h);
            //T.print();
        }
    }

    for(int64_t i = 0; i < n; i++){
        std::cout << T.sum(i, i+1) << "\n";
    }

    return 0;
}
