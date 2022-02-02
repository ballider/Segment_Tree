// присвоенеи и минимум
#include <iostream>
#include <vector>
#include <algorithm>

struct segment_tree{
    struct Node{
        int64_t min;
        int64_t v;
    };
    int64_t size;
    std::vector<Node> tree;

    void init(int64_t n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(2*size-1, {0, -1});
    }

    void print(){
        for(auto it : tree){
            std::cout << "( " << it.min << " " << it.v << " )" << " "; 
        }
        std::cout << "\n";
    }

    void update(int64_t l, int64_t r, int64_t v){
        update(l, r, v, 0, 0, size);
    }

    void update(int64_t L, int64_t R, int64_t v, int64_t x, int64_t left, int64_t right){
        if(L >= right || R <= left) return;
        
        // проталкивание
        if(tree[x].v != -1){
            if(right-left == 1){
                tree[x].v = v;
                tree[x].min = v;
                return;
            }
            else{
                tree[2*x+1].v = tree[x].v;
                tree[2*x+1].min = tree[x].v;
                tree[2*x+2].v = tree[x].v;
                tree[2*x+2].min = tree[x].v;
            }
            tree[x].v = -1;
        }

        if(L <= left && R >= right){ 
            tree[x].v = v;
            tree[x].min = v;
            return;
        }

        int64_t m = (left+right)/2;
        update(L, R, v, 2*x+1, left, m);
        update(L, R, v, 2*x+2, m, right);

        tree[x].min = std::min(tree[2*x+1].min, tree[2*x+2].min);
    }

    int64_t min(int64_t l, int64_t r){
        return min(l, r, 0, 0, size);
    }

    int64_t min(int64_t L, int64_t R, int64_t x, int64_t left, int64_t right){
        // проталктвание
        if(tree[x].v != -1 && right-left != 1){
            tree[2*x+1].v = tree[x].v;
            tree[2*x+1].min = tree[x].v;
            tree[2*x+2].v = tree[x].v;
            tree[2*x+2].min = tree[x].v;

            tree[x].v = -1;
        }

        if(L >= right || R <= left) return INT64_MAX;
        if(L <= left && R >= right) return tree[x].min;

        int64_t m = (left+right)/2;
        int64_t min1 = min(L, R, 2*x+1, left, m);
        int64_t min2 = min(L, R, 2*x+2, m, right);

        return std::max(std::min(min1, min2), tree[x].min);
    }

};

int main(){
    int64_t n, m; std::cin >> n >> m;

    segment_tree T; T.init(n);

    //T.print();

    for(int64_t _ = 0; _ < m ; _++){
        int64_t type; std::cin >> type;
        if(type == 1){
            int64_t l, r, v; std::cin >> l >> r >> v;
            T.update(l, r, v);
            //T.print();
        }
        if(type == 2){
            int64_t l, r; std::cin >> l >> r;
            std::cout << T.min(l, r) << "\n";
        }
    }

    return 0;
}
