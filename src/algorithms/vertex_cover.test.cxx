#include <unordered_set>

#include <catch2/catch_test_macros.hpp>

#include <algorithms/dfs.h>
#include <algorithms/ilst.h>
#include <algorithms/vertex_cover.h>
#include <io_helpers/io_helpers.h>

using namespace std;


TEST_CASE("`init_data_structures` is correct")
{
    
}


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
        1    [0]    3
    */

    const auto got_list = cvc_tree_to_vc(g, tree, root);
    const auto got = unordered_set<unsigned>{got_list.cbegin(), got_list.cend()};
    CHECK(got == unordered_set<unsigned>{0, 2, 4, 5});
    CHECK(is_vc(g, got));
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

    const auto got_list = cvc_tree_to_vc(g, tree, root);
    const auto got = unordered_set<unsigned>{got_list.cbegin(), got_list.cend()};
    CHECK(got == unordered_set<unsigned>{1, 2, 3, 7});
    CHECK(is_vc(g, got));
}
