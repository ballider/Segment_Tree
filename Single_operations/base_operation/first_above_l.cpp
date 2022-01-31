// первый элемент больший и равный х c индекса l
#include <iostream>
#include <vector>
#include <algorithm>

struct segment_tree{
    int64_t size;
    std::vector<int64_t> tree;

    void init(const int64_t n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size-1, -1);
    }

    void set(const int64_t i, const int64_t v){
        set(i, v, 0, 0, size);
    }

    void set(const int64_t i, const int64_t v, int64_t x, int64_t left, int64_t right){
        if(right-left == 1){
            tree[x] = v;
            return;
        }

        int64_t m = (left+right)/2;
        if( i <  m ) set(i, v, 2*x+1, left, m);
        else set(i, v, 2*x+2, m, right);

        tree[x] = std::max(tree[2*x+1], tree[2*x+2]);
    }

    int64_t first_above(const int64_t a, const int64_t l){
        return first_above(a, l, 0, 0, size);
    }

    int64_t first_above(const int64_t a, const int64_t l, int64_t x, int64_t left, int64_t right){
        if(tree[x] < a) return -1;
        if(right <= l)  return -1;
        if(right-left == 1) return left;

        int64_t m = (left+right)/2;
        int64_t res = first_above(a, l, 2*x+1, left, m);
        if(res == -1){
            res = first_above(a, l, 2*x+2, m, right);
        }

        return res;
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
        if(a == 2) std::cout << T.first_above(b, c) << std::endl;
    }
    
    return 0;
}
