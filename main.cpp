#include<bits/stdc++.h>
#include<unordered_map>
#include <chrono>
#include "utils.h"
#include "A_star.h"
#include "bfs.h"
#include "dfs.h"

using namespace std;

int main()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n = 3;
    int m = 3;
    vector<vector<int>>puzzle;

    string puzzle_str = "";

    for (int i = 0; i < n; i++)
    {
        vector<int> a;
        for (int j = 0; j < m; j++)
        {
            int x;
            cin >> x;
            a.push_back(x);


            puzzle_str += '0' + x;
        }
        puzzle.push_back(a);
    }

    if(!isSolvable(puzzle_str)){
        cout<<"Puzzle Not Solvable";
        return 0;
    }
    string puzzle_sorted_str = puzzle_str;

    sort(puzzle_sorted_str.begin(), puzzle_sorted_str.end());



    cout<<"\nUsing BFS Algorithm ...\n";

    auto t1 = std::chrono::high_resolution_clock::now();

    bfs(puzzle, puzzle_str, puzzle_sorted_str);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "\n" << ms_int.count() << "ms\n";

    cout << "-------------------------------------------" << endl;
    cout<<"\nUsing DFS Algorithm ...\n";

    auto t3 = std::chrono::high_resolution_clock::now();
    dfs(puzzle, puzzle_str, puzzle_sorted_str);
    auto t4 = std::chrono::high_resolution_clock::now();

    auto ms_int2 = duration_cast<std::chrono::milliseconds>(t4 - t3);
    std::cout << "\n" << ms_int2.count() << "ms\n";

    cout << "----------------------------------" << endl;
    cout<<"\nUsing A* Algorithm using Euclidean Distance ...\n";

    auto t5 = std::chrono::high_resolution_clock::now();
    A_star(puzzle, puzzle_str, puzzle_sorted_str,"Ecludian");
    auto t6 = std::chrono::high_resolution_clock::now();

    auto ms_int3 = duration_cast<std::chrono::milliseconds>(t6 - t5);
    std::cout << "\n" << ms_int3.count() << "ms\n";

    cout << "----------------------------------" << endl;
    cout<<"\nUsing A* Algorithm using Manhattan Distance ...\n";

    auto t7 = std::chrono::high_resolution_clock::now();
    A_star(puzzle, puzzle_str, puzzle_sorted_str,"Manhattan");
    auto t8 = std::chrono::high_resolution_clock::now();
    auto ms_int4 = duration_cast<std::chrono::milliseconds>(t8 - t7);
    std::cout << "\n" << ms_int4.count() << "ms\n";


}