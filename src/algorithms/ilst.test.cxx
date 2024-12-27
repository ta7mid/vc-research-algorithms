#include <algorithm>
#include <cassert>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <algorithms/dfs.h>
#include <algorithms/ilst.h>
#include <graph_helpers/graph_helpers.h>
#include <io_helpers/io_helpers.h>

using namespace std;


static bool is_independence_tree(const vector<vector<unsigned>>& g, const vector<vector<unsigned>>& tree)
{
    const auto n = unsigned(g.size());
    assert(n == tree.size());
    for (unsigned u{0}; u != n; ++u) {
        if (tree[u].size() != 1) // not a leaf
            continue;
        for (unsigned v{u + 1}; v != n; ++v) {
            if (tree[v].size() != 1) // not a leaf
                continue;
            if (const auto& uadj = g[u]; find(uadj.cbegin(), uadj.cend(), v) != uadj.cend())
                return false;
        }
    }
    return true;
}


TEST_SUITE("ILST") {
    TEST_CASE("ILST on graph_editor_default.txt")
    {
        const auto g = read_simple_graph_from_file(TEST_DATA_DIR "graph_editor_default.txt");
        /*
            5-----4-----2
            |\   /|    /|
            |  X  |  /  |
            |/   \|/    |
            1     0     3
        */

        unsigned root{4};
        auto tree = dfs(g, root);
        /*
            5     4     2
            |\    |    /|
            |  \  |  /  |
            |    \|/    |
            1     0     3
        */
        CHECK_FALSE(is_independence_tree(g, tree));
        CHECK(has_edge(tree, 0, 5));

        const bool indenendence{make_ilst_or_hamil_path(g, tree, root)};
        /*
            5     4     2
            |    /|    /|
            |  /  |  /  |
            |/    |/    |
            1     0     3
        */
        CHECK(indenendence);
        CHECK(is_independence_tree(g, tree));
        CHECK_FALSE(has_edge(tree, 0, 5));
        CHECK(has_edge(tree, 1, 4));
        CHECK_EQ(root, 5);
    }

    TEST_CASE("ILST on a nice tree with one loop")
    {
        const auto g = read_simple_graph(
            R"(8
            8
            0 1
            0 7
            1 2
            1 3
            2 4
            2 5
            3 6
            3 7)"
        );
        /*
                   0--
                   |    `
                   |       `
                   1         \
                  / \         \
                 /    \        )
                /       \      |
               2         3     ,
              / \       / \   /
             /   \     /   \ /
            4     5   6     7
        */

        unsigned root{0};
        auto tree = dfs(g, root);
        /*
                   0
                   |
                   |
                   1
                  / \
                 /    \
                /       \
               2         3
              / \       / \
             /   \    /    \
            4     5  6      7
        */
        CHECK_FALSE(is_independence_tree(g, tree));
        CHECK_FALSE(has_edge(tree, 7, 0));

        const bool indenendence{make_ilst_or_hamil_path(g, tree, root)};
        /*
                   0--
                   |    `
                   |       `
                   1         \
                  / \         \
                 /    \        )
                /       \      |
               2         3     ,
              / \       /     /
             /   \     /     /
            4     5   6     7
        */
        CHECK(indenendence);
        CHECK(is_independence_tree(g, tree));
        CHECK(has_edge(tree, 7, 0));
        CHECK_EQ(root, 7);
    }

    TEST_CASE("ILST on a ring graph")
    {
        const auto g = read_simple_graph(
            R"(6
            6
            0 1
            1 2
            2 3
            3 4
            4 5
            5 0
            3 7)"
        );
        /*
                 ____
              _0'    `5_
             /           \
            |             |
            1             4
             \           /
              `\        /
                `2----3'
        */
        CHECK(has_edge(g, 0, 1));

        unsigned root{1};
        auto tree = dfs(g, root);
        /*
                 ____
               0'    `5_
                         \
                          |
            1             4
             \           /
              `\        /
                `2----3'
        */
        CHECK_FALSE(is_independence_tree(g, tree));
        CHECK_FALSE(has_edge(g, 0, 1));

        const auto old_tree = tree;
        const auto old_root = root;
        const bool indenendence{make_ilst_or_hamil_path(g, tree, root)};
        /*
                 ____
               0'    `5_
                         \
                          |
            1             4
             \           /
              `\        /
                `2----3'
        */
        CHECK_FALSE(indenendence);
        CHECK_EQ(old_tree, tree);
        CHECK_EQ(old_root, root);
    }
}
