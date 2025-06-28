#include <cassert>
#include <vector>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include <algorithms/dfs.h>
#include <io_helpers/io_helpers.h>

using namespace std;


struct Recursive_dfs {
    Recursive_dfs(vector<vector<unsigned>> g, const unsigned root)
        : a{std::move(g)}, tree(a.size()), visited(a.size(), false)
    {
        assert(root < a.size());
        recur(root);
    }

    [[nodiscard]] vector<vector<unsigned>> result() const
    {
        return tree;
    }
private:
    void recur(const unsigned parent)
    {
        visited[parent] = true;
        for (const auto child : a[parent]) {
            if (not visited[child]) {
                tree[parent].push_back(child);
                tree[child].push_back(parent);
                recur(child);
            }
        }
    }

    vector<vector<unsigned>> a;
    vector<vector<unsigned>> tree;
    vector<bool> visited;
};


TEST_CASE("DFS on graph_editor_default.txt")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "graph_editor_default.txt");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on networkrepository.com/order_2-16/soc-tribes.txt")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "networkrepository.com/order_2-16/soc-tribes.txt");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on networkrepository.com/order_2-16/ucidata-gama.txt")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "networkrepository.com/order_2-16/ucidata-gama.txt");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on networkrepository.com/order_65-128/polbooks.txt")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "networkrepository.com/order_65-128/polbooks.txt");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on networkrepository.com/order_129-256/gen200-p0-9-44.txt")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "networkrepository.com/order_129-256/gen200-p0-9-44.txt");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on networkrepository.com/order_257-512/gen400-p0-9-55.txt")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "networkrepository.com/order_257-512/gen400-p0-9-55.txt");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on networkrepository.com/order_513-1024/G7.txt")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "networkrepository.com/order_513-1024/G7.txt");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on networkrepository.com/order_1025-2048/G25.txt")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "networkrepository.com/order_1025-2048/G25.txt");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on networkrepository.com/order_1025-2048/G42.txt")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "networkrepository.com/order_1025-2048/G42.txt");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on networkrepository.com/order_1025-2048/p-hat1500-1.txt")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "networkrepository.com/order_1025-2048/p-hat1500-1.txt");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on judge.yosupo.jp/scc/example_00.in")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "judge.yosupo.jp/scc/example_00.in");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on judge.yosupo.jp/scc/large_cycle_00.in")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "judge.yosupo.jp/scc/large_cycle_00.in");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on judge.yosupo.jp/scc/max_random_00.in")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "judge.yosupo.jp/scc/max_random_00.in");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on judge.yosupo.jp/scc/max_random_01.in")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "judge.yosupo.jp/scc/max_random_01.in");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on judge.yosupo.jp/scc/max_random_02.in")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "judge.yosupo.jp/scc/max_random_02.in");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on judge.yosupo.jp/scc/max_random_03.in")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "judge.yosupo.jp/scc/max_random_03.in");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}

TEST_CASE("DFS on judge.yosupo.jp/scc/max_random_04.in")
{
    const auto g = read_simple_graph_from_file(TEST_DATA_DIR "judge.yosupo.jp/scc/max_random_04.in");
    CHECK(dfs(g, 0) == Recursive_dfs{g, 0}.result());
}
