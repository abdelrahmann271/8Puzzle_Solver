//
// Created by Abdelrahman Nour on 11/6/2021.
//
#include<bits/stdc++.h>
#include<unordered_map>
#include <chrono>
//#include "utils.h"
using namespace std;

void bfs(vector<vector<int>>puzzle,string start_state_str,string finish_state_str)
{

    // Nodes to be expanded
    int nodes_expanded = 0;

    // Dimensions
    int n = puzzle.size();
    int m = puzzle[0].size();


    // indicies for zero
    int zero_i = 0;
    int zero_j = 0;



    // find zero position

    pair<int, int>pos_init = find_zero(puzzle);
    zero_i = pos_init.first;
    zero_j = pos_init.second;

    // Frontier Queue
    // String for the state strings
    queue<pair<string,int>>state_str_queue;


    // zero position
    queue<pair<int, int>>zero_pos_queue;



    // Add first state
    state_str_queue.push({ start_state_str,0 });

    // add zero position

    zero_pos_queue.push({ zero_i,zero_j });



    // Map for visited states
    unordered_map<string, bool>visited;

    // Map for path
    //string 1 has current state
    // pair : string 1 has parent state
    //        string 2 has move taken

    unordered_map<string, pair<string, string>>parent;

    parent[start_state_str] = { "-1","initial State" };

    int finished_level = 0;

    while (!state_str_queue.empty())
    {
        // Assign
        string state = state_str_queue.front().first;

        int level = state_str_queue.front().second;

        pair<int, int>zero_pos = zero_pos_queue.front();


        //Pop
        state_str_queue.pop();

        zero_pos_queue.pop();


        // if seen before pop
        if (visited[state])
            continue;

        // visited state

        visited[state] = 1;
        // if state is the finish_state then done
        if (state == finish_state_str)
        {
            finished_level = level;

            break;
        }


        // for expansion if no neighboors found so no expansion happened
        int expanded = 0;

        // Add states to queues
        add_states_to_queue(n, m, state,level, zero_pos, state_str_queue, zero_pos_queue,parent,visited,expanded);


        nodes_expanded += expanded;
    }

    // Print the Path

    vector<string>moves;
    vector<string>grid;

    string curr = finish_state_str;


    while (parent[curr].first != "-1")
    {
        pair<string, string>next = parent[curr];

        moves.push_back(next.second);

        grid.push_back(next.first);

        // Get the parent of this state
        curr = next.first;
    }

    // Reverse moves to get it in correct order
    reverse(moves.begin(), moves.end());
    reverse(grid.begin(), grid.end());

    // Path to the Goal

    cout << "Path to Goal" << endl << endl;

    for (int i = 0; i < moves.size(); i++)
    {

        cout << "State" << endl;
        print_state(n,m,grid[i]);

        cout<< moves[i] << endl;;
        cout << endl;

    }
    cout << "State" << endl;
    print_state(n, m, finish_state_str);
    cout << endl;

    cout << "Depth: " << finished_level << endl;
    cout << "Cost: " << finished_level << endl;

    cout << "Node expanded: " << nodes_expanded << endl;
}