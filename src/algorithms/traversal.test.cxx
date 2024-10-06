#include <algorithm>
#include <cassert>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <utility>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <algorithms/traversal.h>

using namespace std;


struct recursive_dfs {
    vector<vector<unsigned>> a;
    vector<vector<unsigned>> res;
    vector<bool> visited;

    explicit recursive_dfs(vector<vector<unsigned>> adj)
        : a{std::move(adj)}, res(a.size()), visited(a.size(), false)
    {}

    vector<vector<unsigned>> operator()(unsigned root)
    {
        recur(root);
        return res;
    }

    void recur(unsigned parent)
    {
        visited[parent] = true;
        for (const auto child : a[parent]) {
            if (not visited[child]) {
                res[parent].push_back(child);
                res[child].push_back(parent);
                recur(child);
            }
        }
    }
};

vector<vector<unsigned>> read_simple_graph(istream& is)
{
    unsigned n, m;
    is >> n >> m;
    vector<vector<unsigned>> res(n);
    while (m--) {
        unsigned u, v;
        is >> u >> v;
        assert(u < n);
        assert(v < n);
        if (u == v)
            continue;
        auto& uadj = res[u];
        if (find(uadj.cbegin(), uadj.cend(), v) != uadj.cend())
            continue;
        uadj.push_back(v);
        res[v].push_back(u);
    }
    return res;
}

vector<vector<unsigned>> read_simple_graph_from_file(const string& filepath)
{
    ifstream fin{filepath};
    assert(fin and fin.is_open() and !fin.fail());
    return read_simple_graph(fin);
}


TEST_SUITE("DFS traversal is correct") {
    TEST_CASE("graph_editor_default.txt")
    {
        const auto g = read_simple_graph_from_file("graph_editor_default.txt");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("networkrepository.com/order_2-16/soc-tribes.txt")
    {
        const auto g = read_simple_graph_from_file("networkrepository.com/order_2-16/soc-tribes.txt");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("networkrepository.com/order_2-16/ucidata-gama.txt")
    {
        const auto g = read_simple_graph_from_file("networkrepository.com/order_2-16/ucidata-gama.txt");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("networkrepository.com/order_65-128/polbooks.txt")
    {
        const auto g = read_simple_graph_from_file("networkrepository.com/order_65-128/polbooks.txt");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("networkrepository.com/order_129-256/gen200-p0-9-44.txt")
    {
        const auto g = read_simple_graph_from_file("networkrepository.com/order_129-256/gen200-p0-9-44.txt");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("networkrepository.com/order_257-512/gen400-p0-9-55.txt")
    {
        const auto g = read_simple_graph_from_file("networkrepository.com/order_257-512/gen400-p0-9-55.txt");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("networkrepository.com/order_513-1024/G7.txt")
    {
        const auto g = read_simple_graph_from_file("networkrepository.com/order_513-1024/G7.txt");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("networkrepository.com/order_1025-2048/G25.txt")
    {
        const auto g = read_simple_graph_from_file("networkrepository.com/order_1025-2048/G25.txt");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("networkrepository.com/order_1025-2048/G42.txt")
    {
        const auto g = read_simple_graph_from_file("networkrepository.com/order_1025-2048/G42.txt");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("networkrepository.com/order_1025-2048/p-hat1500-1.txt")
    {
        const auto g = read_simple_graph_from_file("networkrepository.com/order_1025-2048/p-hat1500-1.txt");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("judge.yosupo.jp/scc/example_00.in")
    {
        const auto g = read_simple_graph_from_file("judge.yosupo.jp/scc/example_00.in");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("judge.yosupo.jp/scc/large_cycle_00.in")
    {
        const auto g = read_simple_graph_from_file("judge.yosupo.jp/scc/large_cycle_00.in");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("judge.yosupo.jp/scc/max_random_00.in")
    {
        const auto g = read_simple_graph_from_file("judge.yosupo.jp/scc/max_random_00.in");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("judge.yosupo.jp/scc/max_random_01.in")
    {
        const auto g = read_simple_graph_from_file("judge.yosupo.jp/scc/max_random_01.in");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("judge.yosupo.jp/scc/max_random_02.in")
    {
        const auto g = read_simple_graph_from_file("judge.yosupo.jp/scc/max_random_02.in");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("judge.yosupo.jp/scc/max_random_03.in")
    {
        const auto g = read_simple_graph_from_file("judge.yosupo.jp/scc/max_random_03.in");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }

    TEST_CASE("judge.yosupo.jp/scc/max_random_04.in")
    {
        const auto g = read_simple_graph_from_file("judge.yosupo.jp/scc/max_random_04.in");
        CHECK(dfs(g, 0) == recursive_dfs{g}(0));
    }
}
