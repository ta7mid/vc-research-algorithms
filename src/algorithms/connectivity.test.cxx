#include <algorithm>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <algorithms/connectivity.h>
#include <io_helpers/io_helpers.h>

using namespace std;


/*
    5-----4-----2    6   8    10
    |\   /|    /|       /|     |
    |  X  |  /  |      / |     |
    |/   \|/    |     /  |     |
    1     0     3    7   9    11
*/
constexpr auto g_str = R"(12
11
0 2
0 4
0 5
1 4
1 5
2 3
2 4
4 5
7 8
8 9
10 11
)";


TEST_CASE("`next_connected_component` works")
{
    const auto g = read_simple_graph(g_str);
    vector<bool> visited(g.size(), false);

    auto got = next_connected_component(g, visited);
    sort(got.begin(), got.end());
    CHECK_EQ(got, vector<unsigned>{0, 1, 2, 3, 4, 5});

    got = next_connected_component(g, visited);
    CHECK_EQ(got, vector<unsigned>{6});

    got = next_connected_component(g, visited);
    sort(got.begin(), got.end());
    CHECK_EQ(got, vector<unsigned>{7, 8, 9});

    got = next_connected_component(g, visited);
    sort(got.begin(), got.end());
    CHECK_EQ(got, vector<unsigned>{10, 11});
}
