// присвоенеи и sum
#include <iostream>
#include <vector>
#include <algorithm>

struct segment_tree{
    struct Node{
        int64_t sum;
        int64_t set;
        int64_t count;
    };
    int64_t size;
    std::vector<Node> tree;

    void build(int64_t x, int64_t left, int64_t rigth){
        if(rigth-left == 1){
            tree[x].set = -1;
            tree[x].sum = 0;
            tree[x].count = 1;
        }
        else{
            int64_t m = (left+rigth)/2;
            build(2*x+1, left, m);
            build(2*x+2, m, rigth);
            tree[x].count = tree[2*x+1].count + tree[2*x+2].count;
            tree[x].set = -1;
            tree[x].sum = 0;
        }
    }

    void init(int64_t n){
        size = 1;
        while(size < n) size *= 2;
        tree.resize(2*size-1);
        build(0, 0, size);
    }

    void print(){
        for(auto it : tree){
            std::cout << "( " << it.sum << " " << it.set << " )" << " "; 
        }
        std::cout << "\n";
    }

    void update(int64_t l, int64_t r, int64_t v){
        update(l, r, v, 0, 0, size);
    }

    void update(int64_t L, int64_t R, int64_t v, int64_t x, int64_t left, int64_t right){
        if(L >= right || R <= left) return;
        
        // проталкивание
        if(tree[x].set != -1){
            if(right-left == 1){
                tree[x].set = v;
                tree[x].sum = v;
                return;
            }
            else{
                tree[2*x+1].set = tree[x].set;
                tree[2*x+1].sum = tree[x].set*tree[2*x+1].count;
                tree[2*x+2].set = tree[x].set;
                tree[2*x+2].sum = tree[x].set*tree[2*x+2].count;
            }
            tree[x].set = -1;
        }

        if(L <= left && R >= right){ 
            tree[x].set = v;
            tree[x].sum = v*tree[x].count;
            return;
        }

        int64_t m = (left+right)/2;
        update(L, R, v, 2*x+1, left, m);
        update(L, R, v, 2*x+2, m, right);

        tree[x].sum = tree[2*x+1].sum + tree[2*x+2].sum;
    }

    int64_t sum(int64_t l, int64_t r){
        return sum(l, r, 0, 0, size);
    }

    int64_t sum(int64_t L, int64_t R, int64_t x, int64_t left, int64_t right){
        // проталктвание
        if(tree[x].set != -1 && right-left != 1){
            tree[2*x+1].set = tree[x].set;
            tree[2*x+1].sum = tree[x].set*tree[2*x+1].count;
            tree[2*x+2].set = tree[x].set;
            tree[2*x+2].sum = tree[x].set*tree[2*x+2].count;

            tree[x].set = -1;
        }

        if(L >= right || R <= left) return 0;
        if(L <= left && R >= right) return tree[x].sum;

        int64_t m = (left+right)/2;
        int64_t sum1 = sum(L, R, 2*x+1, left, m);
        int64_t sum2 = sum(L, R, 2*x+2, m, right);

        return sum1+sum2;
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
            std::cout << T.sum(l, r) << "\n";
        }
    }

    return 0;
}
