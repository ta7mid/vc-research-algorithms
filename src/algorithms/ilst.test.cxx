#include <algorithm>
#include <cassert>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "dfs.h"
#include "ilst.h"
#include <helpers/io.h>

using namespace std;


static bool is_ilst(const vector<vector<unsigned>>& g, const vector<vector<unsigned>>& tree)
{
    const auto n = unsigned(g.size());
    assert(n == tree.size());
    for (unsigned u{0}; u != n; ++u) {
        if (tree[u].size() != 1) // not a leaf
            continue;
        for (unsigned v{u + 1}; v != n; ++v) {
            if (tree[v].size() != 1) // not a leaf
                continue;
            const auto& uadj = g[u];
            if (find(uadj.cbegin(), uadj.cend(), v) != uadj.cend())
                return false;
        }
    }
    return true;
}

static bool has_edge(const vector<vector<unsigned>>& g, const unsigned u, const unsigned v)
{
    assert(u < g.size());
    assert(v < g.size());

    const auto& uadj = g[u];
    return find(uadj.cbegin(), uadj.cend(), v) != uadj.cend();
}


TEST_SUITE("ILST") {
    TEST_CASE("ILST on graph_editor_default.txt")
    {
        const auto g = read_simple_graph_from_file(TEST_DATA_DIR "graph_editor_default.txt");
        unsigned root{4};

        auto tree = dfs(g, root);
        CHECK_FALSE(is_ilst(g, tree));
        CHECK(has_edge(tree, 0, 5));

        const bool is_ilst_{make_ilst_or_hamil_path(g, tree, root)};
        CHECK(is_ilst_);
        CHECK(is_ilst(g, tree));
        CHECK_FALSE(has_edge(tree, 0, 5));
        CHECK(has_edge(tree, 1, 4));
        CHECK_EQ(root, 5);
    }

    TEST_CASE("ILST on nice tree that is not g-independent")
    {
        /*
                   0--
                   |    `
                   |       `
                   1        \ <--- the DFS tree won't have this edge
                  / \        \
                 /    \       )
                /      \      |
               2        3     ,
              / \      / \   /
             /   \    /   \ /
            4     5  6     7
        */
        auto g = read_simple_graph(
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
        unsigned root{0};

        auto tree = dfs(g, root);
        CHECK_FALSE(is_ilst(g, tree));
        CHECK_FALSE(has_edge(tree, 7, 0));

        const bool is_ilst_{make_ilst_or_hamil_path(g, tree, root)};
        CHECK(is_ilst_);
        CHECK(is_ilst(g, tree));
        CHECK(has_edge(tree, 7, 0));
        CHECK_EQ(root, 7);
    }

    TEST_CASE("ILST on a ring graph")
    {
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
        auto g = read_simple_graph(
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
        unsigned root{1};

        auto tree = dfs(g, root);
        CHECK_FALSE(is_ilst(g, tree));

        const auto old_tree = tree;
        const auto old_root = root;
        const bool is_ilst_{make_ilst_or_hamil_path(g, tree, root)};
        CHECK_FALSE(is_ilst_);
        CHECK_EQ(old_tree, tree);
        CHECK_EQ(old_root, root);
    }
}
