// segment tree for min
#include <iostream>
#include <vector>
#include <algorithm>

struct segment_tree{
    std::vector<int64_t> tree;
    int64_t size;

    void init(const int64_t n){
        size = 1;
        while( size < n ) size *= 2;
        tree.assign(2*size-1, INT64_MAX);
    }

    void set(const int64_t i, const int64_t v){
        set(i, v, 0, 0, size);
    }

    void set(const int64_t i, const int64_t v, int64_t x, int64_t left, int64_t rigth){
        if(rigth-left == 1){
            tree[x] = v;
            return;
        }
        int64_t m = (left+rigth)/2;
        if( i <  m ) set(i, v, 2*x+1, left, m);
        else set(i, v, 2*x+2, m, rigth);
        tree[x] = std::min(tree[2*x+1], tree[2*x+2]);
    }

    int64_t min(const int64_t l, const int64_t r){
        return min(l, r, 0, 0, size);
    }

    int64_t min(const int64_t L, const int64_t R, int64_t x, int64_t left, int64_t right){
        if( R <= left || L >= right ) return INT64_MAX;
        if( left >= L && right <= R ) return tree[x];

        int64_t m = (left+right)/2;
        int64_t min1 = min(L, R, 2*x+1, left, m);
        int64_t min2 = min(L, R, 2*x+2, m, right);
        return std::min(min1, min2);
    }

    void print(){
        for(auto i : tree){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

int main(){
    int64_t n, m; std::cin >> n >> m;
    segment_tree T; T.init(n);
    for(int64_t i = 0; i < n; i++){
        int64_t v; std::cin >> v;
        T.set(i, v);
    }

    for(int64_t _ = 0; _ < m; _++){
        int64_t a, b, c; std::cin >> a >> b >> c;
        if(a == 1) T.set(b, c);
        if(a == 2) std::cout << T.min(b, c) << std::endl;
    }

    return 0;
}
