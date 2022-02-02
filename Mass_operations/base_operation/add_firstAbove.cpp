#include <iostream>
#include <vector>
#include <algorithm>

struct segment_tree{
    struct Node{
        int64_t max;
        int64_t add;
    };
    int64_t size;
    std::vector<Node> tree;

    void init(const int64_t n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size-1, {0, 0});
    }

    void propagate(int64_t x, int64_t left, int64_t right){
        if(tree[x].add != 0){
            if(right-left == 1){
                tree[x].add = 0;
                return;
            }

            tree[2*x+1].add += tree[x].add;
            tree[2*x+1].max += tree[x].add;

            tree[2*x+2].add += tree[x].add;
            tree[2*x+2].max += tree[x].add;

            tree[x].add = 0;
        }
    }

    void add(const int64_t l, const int64_t r, const int64_t v){
        add(l, r, v, 0, 0, size);
    }

    void add(const int64_t L, const int64_t R, const int64_t v, int64_t x, int64_t left, int64_t right){
        propagate(x, left, right);

        if(L >= right || R <= left) return;
        if(L <= left && R >= right){
            tree[x].add += v;
            tree[x].max += v;
            return;
        }

        int64_t m = (left+right)/2;
        add(L, R, v, 2*x+1, left, m);
        add(L, R, v, 2*x+2, m, right);

        tree[x].max = std::max(tree[2*x+1].max, tree[2*x+2].max);
    }

    int64_t first_above(const int64_t a, const int64_t l){
        return first_above(a, l, 0, 0, size);
    }

    int64_t first_above(const int64_t a, const int64_t l, int64_t x, int64_t left, int64_t right){
        propagate(x, left, right);

        if(tree[x].max < a) return -1;
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
        for(auto it : tree){
            std::cout << it.max << " " << it.add << " | ";
        }
        std::cout << "\n";
    }

};


int main(){
    int64_t n, m; std::cin >> n >> m;

    segment_tree T; T.init(n);

    for(int64_t _ = 0; _ < m; _++){
        int64_t type; std::cin >> type;
        if(type == 1){
            int64_t l, r, v; std::cin >> l >> r >> v;
            T.add(l, r, v);
            //T.print();
        }
        else{
            int64_t x, l; std::cin >> x >> l;
            std::cout << T.first_above(x, l) << "\n";
        }
    }

    return 0;
}
