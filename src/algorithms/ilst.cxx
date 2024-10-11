#include <algorithm>
#include <cassert>
#include <vector>

#include <algorithms/ilst.h>

using namespace std;


bool make_ilst_or_hamil_path(const vector<vector<unsigned>>& g, vector<vector<unsigned>>& dfs_tree, unsigned& root)
{
    assert(g.size() != 1);
    assert(root < g.size());

    if (dfs_tree[root].size() != 1) {
        // root is not a leaf, so dfs_tree is already g-independent
        return true;
    }

    const auto& root_adj_in_g = g[root];
    assert(dfs_tree[root][0] == root_adj_in_g[0]);
    assert(root_adj_in_g.size() != 1);

    /// the first d-leaf of dfs_tree that is *not* g-independent with root -- equivalently, the first
    /// g-neighbor of root that is not a dfs_tree-neighbor of root and is a leaf in dfs_tree
    const unsigned dleaf{
        *find_if(
            root_adj_in_g.cbegin() + 1,  // root_adj_in_g[0] is in the tree
            root_adj_in_g.cend(),
            [&](const unsigned u) {
                // leaf means degree == 1
                return dfs_tree[u].size() == 1;
            }
        )
    };

    auto& dleaf_adj = dfs_tree[dleaf];

    // find the first branching (node with degree > 2) on the path from dleaf to root, if such a branching exists:
    unsigned b{dleaf_adj[0]}; //< eventually dleaf's closest branching ancestor, or the root if the tree is branchless
    unsigned bchild{dleaf}; //< eventually b's immediate child on the path to dleaf
    while (dfs_tree[b].size() == 2) {  // until b is either a branching or the root
        const auto& bneighbors = dfs_tree[b];
        const auto bparent = bneighbors[0] == bchild ? bneighbors[1] : bneighbors[0];

        // climb up the branch
        bchild = b;
        b = bparent;
    }

    if (b == root) {
        // dfs_tree has no branching, which implies that g is a ring graph and hence a spanning tree
        // of it cannot have g-independent leaves.  therefore, dfs_tree is not an indpendence tree,
        // but it is a Hamiltonian path.
        return false;
    }

    // remove the arc b->bchild
    auto& b_adj = dfs_tree[b];
    auto& bchild_adj = dfs_tree[bchild];
    b_adj.erase(find(b_adj.begin(), b_adj.end(), bchild));
    bchild_adj.erase(find(bchild_adj.begin(), bchild_adj.end(), b));
    assert(bchild_adj.size() == (dleaf == bchild ? 0 : 1));

    // add the arc dleaf->root
    dleaf_adj.push_back(root);
    dfs_tree[root].push_back(dleaf);
    assert(dleaf_adj.size() == (dleaf == bchild ? 1 : 2));
    assert(dfs_tree[root].size() == 2);

    // bchild is the new root of the tree
    root = bchild;
    return true;
}
