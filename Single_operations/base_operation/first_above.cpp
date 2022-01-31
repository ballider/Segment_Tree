// первый элемент больший и равный х
#include <iostream>
#include <vector>
#include <algorithm>

struct segment_tree{
    int64_t size;
    std::vector<int64_t> tree;

    void init(const int64_t n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size-1, 0);
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

    int64_t first_above(const int64_t a){
        if(a > tree[0]) return -1;
        return first_above(a, 0, 0, size)-size+1;
    }

    int64_t first_above(const int64_t a, int64_t x, int64_t left, int64_t right){
        if(right-left == 1) return x;

        int64_t m = (left+right)/2;

        if(a <= tree[2*x+1]) first_above(a, 2*x+1, left, m);
        else first_above(a, 2*x+2, m, right);
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
        int64_t a; std::cin >> a;
        if(a == 1){
            int64_t b, c; std::cin >> b >> c;
            T.set(b, c);
        }
        if(a == 2){
            int64_t b; std::cin >> b;
            std::cout << T.first_above(b) << std::endl;
        }
    }

    return 0;
}
