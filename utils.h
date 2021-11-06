//
// Created by Abdelrahman Nour on 11/6/2021.
//
#include<bits/stdc++.h>
#include<unordered_map>
#include <chrono>

using namespace std;


int getInvCount(string arr)
{
    int inv_count = 0;
    for (int i = 0; i < 9 - 1; i++)
        for (int j = i+1; j < 9; j++)
            if (arr[j]!='0' && arr[i]!='0' &&  arr[i] > arr[j])
                inv_count++;
    return inv_count;
}

// This function returns true if given 8 puzzle is solvable.
bool isSolvable(string puzzle)
{
    int invCount = getInvCount(puzzle);
    cout<<"Number of inversions "<<invCount<<"\n";
    return (invCount%2 == 0);
}

void print_state(int n,int m,string puzzle_str)
{
    // Function to print Puzzle in good form

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << puzzle_str[i * m + j] << " ";
        }
        cout << endl;
    }
}

pair<int, int> find_zero(vector<vector<int>>puzzle)
{

    /// <summary>
    /// Function to find zero and return it's position
    /// </summary>
    /// <param name="puzzle"> Puzzle vector </param>
    /// <returns> pair represent position </returns>

    int n = puzzle.size();
    int m = puzzle[0].size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (puzzle[i][j] == 0)
            {
                return { i,j };
            }
        }
    }
}

void add_states_to_queue(int n,int m,string state_str,
                         int level,
                         pair<int,int>pos_pair,
                         queue<pair<string,int>>&states,
                         queue<pair<int,int>>&zero_pos,
                         unordered_map<string,pair<string,string>>&parent,
                         unordered_map<string,bool>vis,
                         int& expanded)
{

    // Position of zero
    int pos_i = pos_pair.first;
    int pos_j = pos_pair.second;


    // Position in string
    int pos = m * pos_i +pos_j;

    string temp = state_str;

    int pos_to_swap = 0;


    // Transitions
    vector<pair<int, int>>transitions =
            { {1,0},{-1,0},{0,1},{0,-1} };

    // Move labels
    vector<string>transition_moves = { "Up","Down","Left","Right" };

    for (int i = 0; i < transitions.size(); i++)
    {
        temp = state_str;


        // Get new Positions
        int new_pos_i = pos_i + transitions[i].first;

        int new_pos_j = pos_j + transitions[i].second;

        pos_to_swap = m * (new_pos_i)+new_pos_j;

        // out of boundries
        if (new_pos_i >= n || new_pos_i < 0
            || new_pos_j >= m || new_pos_j < 0)
            continue;

        // Swap characters in temp to represent a move
        swap(temp[pos], temp[pos_to_swap]);


        // Visited state so continue
        if (vis[temp])
            continue;


        // Push new zero position
        zero_pos.push({ new_pos_i,new_pos_j });


        // Push new State
        states.push({ temp,level + 1 });


        // Make move string
        string move_taken = "Move ";
        move_taken += state_str[pos_to_swap];


        // Parent to get the path
        parent[temp] = { state_str,move_taken +" " +transition_moves[i]};

        // Expansion found
        expanded++;
    }

}

float manhattan_dist(int n,int m,string puzzle_str)
{
    /// <summary>
    /// Manhatten Distance
    /// </summary>
    /// <param name="n"> number of rows</param>
    /// <param name="m">number of columns</param>
    /// <param name="puzzle_str">string repersentation of puzzle</param>
    /// <returns>Manhatten distance</returns>
    float manh_dist = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int pos = puzzle_str[i * m + j]-'0';

            int pos_x = pos / m;
            int pos_y = pos % m;

            manh_dist += abs(i - pos_x) + abs(j - pos_y);
        }
    }

    return manh_dist;
}
float ecludian_dist(int n, int m, string puzzle_str)
{
    float eclud_dist = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int pos = puzzle_str[i * m + j] - '0';

            int pos_x = pos / m;
            int pos_y = pos % m;

            int x1 = abs(i - pos_x);
            int y1 = abs(j - pos_y);

            eclud_dist += sqrt(x1 * x1 + y1 * y1);
        }
    }
    return eclud_dist;
}