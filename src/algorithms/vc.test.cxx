#include <bitset>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "dfs.h"
#include "ilst.h"
#include "vc.h"
#include <common/constants.h>
#include <helpers/io.h>

using namespace std;


TEST_SUITE("ILST-to-VC") {
    TEST_CASE("ILST-to-VC on graph_editor_default.txt")
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
        make_ilst_or_hamil_path(g, tree, root);
        /*
           [5]   [4]   [2]
            |    /|    /|
            |  /  |  /  |
            |/    |/    |
            1    [0]     3
        */

        const auto want = bitset<max_n>{
            1 << 0 |
            1 << 2 |
            1 << 4 |
            1 << 5
        };
        const auto got = ilst_to_vc(g, tree, root);
        CHECK_EQ(got, want);
    }

    TEST_CASE("ILST-to-VC on a nice tree with one loop")
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
             /   \    /    \ /
            4     5  6      7
        */

        unsigned root{0};
        auto tree = dfs(g, root);
        make_ilst_or_hamil_path(g, tree, root);
        /*
                   0--
                   |    `
                   |       `
                  [1]        \
                  / \         \
                 /    \        )
                /       \      |
              [2]       [3]    ,
              / \       /     /
             /   \    /      /
            4     5  6     [7]
        */

        const auto want = bitset<max_n>{
            1 << 1 |
            1 << 2 |
            1 << 3 |
            1 << 7
        };
        const auto got = ilst_to_vc(g, tree, root);
        CHECK_EQ(got, want);
    }
}
