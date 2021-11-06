//
// Created by Abdelrahman Nour on 11/6/2021.
//
#include<bits/stdc++.h>
#include<unordered_map>
#include <chrono>
//#include "utils.h"
using namespace std;


void dfs_solver(int n,int m,string puzzle_str,
                pair<int, int>zero_pos,
                string final_state,
                vector<string>&moves,
                vector<string>&path,
                unordered_map<string,bool>&vis,
                bool &found,
                int &depth,int level,int &nodes_expanded)
{
    // answer found
    if (found||nodes_expanded>=362880)
        return;

    // out of boundries
    if (zero_pos.first >= n || zero_pos.second < 0
        || zero_pos.second >= m || zero_pos.second < 0)
        return;

    // seen before
    if (vis[puzzle_str])
        return;

    // Done
    if (puzzle_str == final_state)
    {
        found = true;
        depth = level;
        return;
    }

    // Mark visited
    vis[puzzle_str] = true;


    // Transitions
    vector<pair<int, int>>transitions =
            { {0,-1},{0,1},{-1,0},{1,0} };

    // Move labels
    vector<string>transition_moves = { "Right","Left","Down","Up" };



    for (int i = 0; i < transitions.size()&&!found; i++)
    {


        int pos_i = zero_pos.first;
        int pos_j = zero_pos.second;

        // New Positons
        int new_pos_i = pos_i + transitions[i].first;
        int new_pos_j = pos_j + transitions[i].second;

        // Positions in string  representation
        int old_pos = pos_i * m + pos_j;
        int new_pos = new_pos_i * m + new_pos_j;

        // out of boundries
        if (new_pos_i >= n || new_pos_i < 0
            || new_pos_j >= m || new_pos_j < 0)
            continue;


        string temp = puzzle_str;


        // Make move
        swap(temp[old_pos], temp[new_pos]);

        // seen before
        if (vis[temp])
            continue;


        // Make move string
        string move = "Move ";
        move += puzzle_str[new_pos_i * m + new_pos_j];
        move += " "+ transition_moves[i];


        // Push moves
        moves.push_back(move);
        path.push_back(puzzle_str);

        // Increment expanded nodes
        nodes_expanded++;

        dfs_solver(n, m, temp, { new_pos_i,new_pos_j }, final_state, moves, path, vis, found,depth,level+1,nodes_expanded);

        // If answer was found so no need to continue
        if (found)
            break;

        moves.pop_back();
        path.pop_back();

    }

}
void dfs(vector<vector<int>>puzzle,string start_state,
         string final_state)
{
    // Init variabels
    unordered_map<string, bool>vis;
    vector<string>moves;
    vector<string>path;
    bool found = false;
    int depth = 0;

    int nodes_expanded = 0;

    // Call dfs
    dfs_solver(puzzle.size(), puzzle[0].size(), start_state, find_zero(puzzle), final_state, moves, path, vis, found, depth, 0,nodes_expanded);



    cout << "Path to the Goal " << endl << endl;;

    for (int i = 0; i < moves.size(); i++)
    {

        cout << "State" << endl;
        print_state(puzzle.size(), puzzle[0].size(), path[i]);
        cout << moves[i] << endl;

        cout <<endl;
    }

    cout << "State" << endl;
    print_state(puzzle.size(), puzzle[0].size(),final_state);

    cout << endl;
    cout <<"Depth: "<< depth << endl;
    cout <<"Cost: "<< depth << endl;

    cout <<"Nodes expanded: " <<nodes_expanded << endl;
}
