//
// Created by Abdelrahman Nour on 11/6/2021.
//
#include<bits/stdc++.h>
#include<unordered_map>
#include <chrono>
//#include "utils.h"
using namespace std;

void A_star(vector<vector<int>>puzzle,string puzzle_start,
            string puzzle_end, string hurestic_func)
{
    /// <summary>
    ///
    /// </summary>
    /// <param name="puzzle">Puzzle vector</param>
    /// <param name="puzzle_start">start puzzle state in string</param>
    /// <param name="puzzle_end">finish puzzle state in string</param>
    /// <param name="hurestic_func"> the required hurestic function</param>

    int nodes_expanded = 0;

    // Dimesnions
    int n = puzzle.size();
    int m = puzzle[0].size();

    // Priority queue
    priority_queue<pair<float, pair<string, pair<int,int>>>>pq;


    // Zero position
    pair<int, int> zero_pos = find_zero(puzzle);

    int zero_i = zero_pos.first;
    int zero_j = zero_pos.second;

    int pos = zero_i * m + zero_j;


    // Hurestic
    if (hurestic_func == "Manhattan")
    {
        pq.push({ -manhattan_dist(n,m,puzzle_start) ,{puzzle_start,{pos,0}} });
    }
    else
    {
        pq.push({ -ecludian_dist(n,m,puzzle_start) ,{puzzle_start,{pos,0}} });
    }

    // Transitions
    vector<pair<int, int>>transitions =
            { {1,0},{-1,0},{0,1},{0,-1} };

    vector<string>transition_moves = { "Up","Down","Left","Right" };


    // G distance
    unordered_map<string, float>g;



    // Parent for printing Path
    unordered_map<string, pair<string, string>>parent;

    // Initialize the start state parent with -1
    parent[puzzle_start] = { "-1","-1" };


    // G start state = 0
    g[puzzle_start] = 0;

    int depth = 0;
    while (!pq.empty())
    {
        pair<float, pair<string, pair<int,int>>>state_pair = pq.top();

        float f_dist = -state_pair.first;

        int level = state_pair.second.second.second;

        string state = state_pair.second.first;


        // Pos in the string format
        int pos = state_pair.second.second.first;

        // Converting Pos to 2d vector representation
        int pos_i = pos / m;
        int pos_j = pos % m;



        // Pop
        pq.pop();


        if (state == puzzle_end)
        {
            depth = level;
            break;
        }


        for (int i = 0; i < transitions.size(); i++)
        {

            int new_pos_i = pos_i + transitions[i].first;

            int new_pos_j = pos_j + transitions[i].second;

            int old_pos = pos;

            int new_pos = new_pos_i * m + new_pos_j;

            // out of boundries
            if (new_pos_i >= n || new_pos_i < 0
                || new_pos_j >= m || new_pos_j < 0)
                continue;

            string temp = state;

            swap(temp[old_pos], temp[new_pos]);


            // If never seen before or require relaxing
            if (g.find(temp)==g.end()|| g[state] + 1 < g[temp])
            {

                // Make hurestic
                float new_h = 0;
                if (hurestic_func == "Manhattan")
                {
                    new_h = manhattan_dist(n, m, temp);
                }
                else
                {
                    new_h = ecludian_dist(n, m, temp);
                }

                // Update G
                g[temp] = g[state] + 1;

                // Update f
                float new_f = g[temp] + new_h;


                // Push
                pq.push({ -new_f,{temp,{new_pos,level + 1} } });


                // Make move label
                string move_taken = "Move ";
                move_taken += state[new_pos];

                parent[temp] = { state,move_taken + " " + transition_moves[i] };

                // Expand node
                nodes_expanded++;
            }

        }
    }

    // Get the Path
    vector<string>moves;
    vector<string>grid;

    string curr = puzzle_end;

    while (parent[curr].first != "-1")
    {
        pair<string, string>next = parent[curr];

        moves.push_back(next.second);

        grid.push_back(next.first);

        curr = next.first;
    }

    reverse(moves.begin(), moves.end());
    reverse(grid.begin(), grid.end());


    cout << "Path to the goal" << endl << endl;;


    for (int i = 0; i < moves.size(); i++)
    {

        cout << "State" << endl;
        print_state(n,m,grid[i]);

        cout<<moves[i] << endl;

        cout << endl;
    }

    cout << "State" << endl;
    print_state(n, m, puzzle_end);
    cout << endl;

    cout << "Node expanded: " << nodes_expanded << endl;

    cout << "Depth : " << depth << endl;
    cout << "Cost : " << depth << endl;
}
