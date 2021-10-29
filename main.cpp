#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <math.h>

using namespace std;


vector<vector<int>> puzzle_board (9,vector<int>(9));
vector<vector<int>> directions {{1,0},{0,1},{0,-1},{-1,0}};
unordered_map<int,pair<int,int>> umap;





//BFS-results
int bfs_cost = -1;
int nodes_expanded_bfs = 0;

//DFS-results
int dfs_cost = -1;
int nodes_expanded_dfs = 0;

//A_Star_manhattan-results
int A_star_manhattan_cost = -1;
int nodes_expanded_A_star_manhattan = 0;

//A_Star_euclidean-results
int A_star_euclidean_cost =-1;
int nodes_expanded_A_star_euclidean = 0;


bool check_boundaries(pair<int,int> point){
    if(point.first >= 0 &&
       point.first <=2  &&
       point.second >=0 &&
       point.second <=2)
        return true;
    return false;
}
bool check_goal_state(vector<vector<int>>& state){
    int num = 0;
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ;j++){
            if(state[i][j] != num++)
                return false;
        }
    }
    return true;
}
void print_State(vector<vector<int>>& state){
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ;j++){
            cout<<state[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}
pair<int,int> find_blank(vector<vector<int>>& state){
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ;j++){
            if(state[i][j]==0){
                return {i,j};
            }
        }
    }
}

vector<vector<int>> bfs(vector<vector<int>>& initial_state){
    //Initialization
    bfs_cost = -1;
    nodes_expanded_bfs = 0;
    queue<vector<vector<int>>> search_queue;
    set<vector<vector<int>>> visited_states;


    search_queue.push(initial_state);
    nodes_expanded_bfs++;

    //print_State(initial_state);
    while(!search_queue.empty()){
        vector<vector<int>> curr = search_queue.front();
        search_queue.pop();
        cout<<"\nState\n";
        visited_states.insert(curr);
        bfs_cost++;
        print_State(curr);
        if(check_goal_state(curr)){
            return curr;
        }
        pair<int,int> curr_point = find_blank(curr);
        //cout<<"\nprint neighbours\n";
        for(int i = 0 ; i < 4 ; i++){

            if(check_boundaries({curr_point.first+directions[i][0],curr_point.second+directions[i][1]})){
                vector<vector<int>> neighbour = curr;
                int temp = neighbour[curr_point.first][curr_point.second];
                neighbour[curr_point.first][curr_point.second] = neighbour[curr_point.first+directions[i][0]][curr_point.second+directions[i][1]];
                neighbour[curr_point.first+directions[i][0]][curr_point.second+directions[i][1]] = temp;

                if(visited_states.find(neighbour)==visited_states.end()){

                    search_queue.push(neighbour);
                    nodes_expanded_bfs++;

                   // print_State(neighbour);
                }

            }
        }
    }
    cout<<"failed\n";
    return initial_state;
}
vector<vector<int>> dfs(vector<vector<int>>& initial_state){
    //Initialization
    dfs_cost = -1;
    nodes_expanded_dfs++;
    stack<vector<vector<int>>> search_stack;
    set<vector<vector<int>>> visited_states;

    search_stack.push(initial_state);
    nodes_expanded_dfs++;

    //print_State(initial_state);
    while(!search_stack.empty()){
        vector<vector<int>> curr = search_stack.top();
        search_stack.pop();
        cout<<"\nState\n";
        visited_states.insert(curr);
        dfs_cost++;
        print_State(curr);
        if(check_goal_state(curr)){
            return curr;
        }
        pair<int,int> curr_point = find_blank(curr);
        //cout<<"\nprint neighbours\n";
        for(int i = 0 ; i < 4 ; i++){

            if(check_boundaries({curr_point.first+directions[i][0],curr_point.second+directions[i][1]})){
                vector<vector<int>> neighbour = curr;
                int temp = neighbour[curr_point.first][curr_point.second];
                neighbour[curr_point.first][curr_point.second] = neighbour[curr_point.first+directions[i][0]][curr_point.second+directions[i][1]];
                neighbour[curr_point.first+directions[i][0]][curr_point.second+directions[i][1]] = temp;

                if(visited_states.find(neighbour)==visited_states.end()){

                    search_stack.push(neighbour);
                    nodes_expanded_dfs++;

                    //print_State(neighbour);
                }

            }
        }
    }
    cout<<"failed\n";
    return initial_state;
}

int compute_manhattan(vector<vector<int>>& state){
    int m = 0;
    for(int i = 0 ; i < state.size() ; i++){
        for(int j = 0 ; j < state[i].size() ; j++){
            m += (abs(i-umap[state[i][j]].first)+ abs(j-umap[state[i][j]].second));
        }
    }
}

float compute_euclidean(vector<vector<int>>& state){
    float m = 0;
    for(int i = 0 ; i < state.size() ; i++){
        for(int j = 0 ; j < state[i].size() ; j++){
            m += sqrt(pow(i-umap[state[i][j]].first,2)+ pow(j-umap[state[i][j]].second,2) );
        }
    }
}
vector<vector<int>> A_star_manhattan(vector<vector<int>>& initial_state){
    //Initialization
    A_star_manhattan_cost = -1;
    nodes_expanded_A_star_manhattan=0;
    priority_queue< pair<int,vector<vector<int>>>, vector<pair<int,vector<vector<int>>>>, greater<pair<int,vector<vector<int>>>> > pq;
    set<vector<vector<int>>> visited_states;

    pq.push({compute_manhattan(initial_state),initial_state});
    nodes_expanded_A_star_manhattan++;

    //print_State(initial_state);
    while(!pq.empty()){
        vector<vector<int>> curr = pq.top().second;
        pq.pop();
        cout<<"\nState\n";
        visited_states.insert(curr);
        A_star_manhattan_cost++;
        print_State(curr);
        if(check_goal_state(curr)){
            return curr;
        }
        pair<int,int> curr_point = find_blank(curr);
        //cout<<"\nprint neighbours\n";
        for(int i = 0 ; i < 4 ; i++){

            if(check_boundaries({curr_point.first+directions[i][0],curr_point.second+directions[i][1]})){
                vector<vector<int>> neighbour = curr;
                int temp = neighbour[curr_point.first][curr_point.second];
                neighbour[curr_point.first][curr_point.second] = neighbour[curr_point.first+directions[i][0]][curr_point.second+directions[i][1]];
                neighbour[curr_point.first+directions[i][0]][curr_point.second+directions[i][1]] = temp;

                if(visited_states.find(neighbour)==visited_states.end()){

                    pq.push({compute_manhattan(neighbour)+A_star_manhattan_cost+1,neighbour});
                    nodes_expanded_A_star_manhattan++;

                    //print_State(neighbour);
                }

            }
        }
    }
    cout<<"failed\n";
    return initial_state;
}
vector<vector<int>> A_star_euclidean(vector<vector<int>>& initial_state){
    //Initialization
    A_star_euclidean_cost = -1;
    nodes_expanded_A_star_euclidean=0;
    priority_queue< pair<int,vector<vector<int>>>, vector<pair<int,vector<vector<int>>>>, greater<pair<int,vector<vector<int>>>> > pq;
    set<vector<vector<int>>> visited_states;

    pq.push({compute_euclidean(initial_state),initial_state});
    nodes_expanded_A_star_euclidean++;

    //print_State(initial_state);
    while(!pq.empty()){
        vector<vector<int>> curr = pq.top().second;
        pq.pop();
        cout<<"\nState\n";
        visited_states.insert(curr);
        A_star_euclidean_cost++;
        print_State(curr);
        if(check_goal_state(curr)){
            return curr;
        }
        pair<int,int> curr_point = find_blank(curr);
        //cout<<"\nprint neighbours\n";
        for(int i = 0 ; i < 4 ; i++){

            if(check_boundaries({curr_point.first+directions[i][0],curr_point.second+directions[i][1]})){
                vector<vector<int>> neighbour = curr;
                int temp = neighbour[curr_point.first][curr_point.second];
                neighbour[curr_point.first][curr_point.second] = neighbour[curr_point.first+directions[i][0]][curr_point.second+directions[i][1]];
                neighbour[curr_point.first+directions[i][0]][curr_point.second+directions[i][1]] = temp;

                if(visited_states.find(neighbour)==visited_states.end()){

                    pq.push({compute_euclidean(neighbour)+A_star_manhattan_cost+1,neighbour});
                    nodes_expanded_A_star_euclidean++;

                    //print_State(neighbour);
                }

            }
        }
    }
    cout<<"failed\n";
    return initial_state;
}
int main() {
    umap[0]={0,0};
    umap[1]={0,1};
    umap[2]={0,2};
    umap[3]={1,0};
    umap[4]={1,1};
    umap[5]={1,2};
    umap[6]={2,0};
    umap[7]={2,1};
    umap[8]={2,2};
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

//    vector<vector<int>> puzzle1 {{6,7,8},{3,4,5},{2,1,0}};
      vector<vector<int>> puzzle2 {{1,2,5},{3,4,0},{6,7,8}};
//    vector<vector<int>> puzzle3 {{1,8,5},{3,4,0},{6,7,2}};
//    vector<vector<int>> puzzle4 {{0,1,2},{3,4,8},{6,7,5}};
//    vector<vector<int>> puzzle5 {{2,0,1},{3,4,5},{6,7,8}};
      vector<vector<int>> puzzle6 {{1,0,2},{3,4,5},{6,7,8}};

    //BFS
//    auto t1 = std::chrono::high_resolution_clock::now();
//    vector<vector<int>> answer2= bfs(puzzle2);
//    auto t2 = std::chrono::high_resolution_clock::now();
//
//    print_State(answer2);
//    cout<<"\nbfs cost: "<<bfs_cost;
//    cout<<"\nnodes expanded: "<<nodes_expanded_bfs;
//    auto ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
//    std::cout << "\n" << ms_int.count() << "ms\n";

    //DFS
//    auto t1 = std::chrono::high_resolution_clock::now();
//    vector<vector<int>> answer2= dfs(puzzle2);
//    auto t2 = std::chrono::high_resolution_clock::now();
//
//    print_State(answer2);
//    cout<<"\ndfs cost: "<<dfs_cost;
//    cout<<"\nnodes expanded: "<<nodes_expanded_dfs;
//    auto ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
//    std::cout << "\n" << ms_int.count() << "ms\n";

    //A_STAR_manhattan

//    auto t1 = std::chrono::high_resolution_clock::now();
//    vector<vector<int>> answer2= A_star_manhattan(puzzle2);
//    auto t2 = std::chrono::high_resolution_clock::now();
//
//    print_State(answer2);
//    cout<<"\na-star-manhattan cost: "<<A_star_manhattan_cost;
//    cout<<"\nnodes expanded: "<<nodes_expanded_A_star_manhattan;
//    auto ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
//    std::cout << "\n" << ms_int.count() << "ms\n";

    //A_STAR_euclidean

    auto t1 = std::chrono::high_resolution_clock::now();
    vector<vector<int>> answer2= A_star_euclidean(puzzle2);
    auto t2 = std::chrono::high_resolution_clock::now();

    print_State(answer2);
    cout<<"\na-star-euclidean cost: "<<A_star_euclidean_cost;
    cout<<"\nnodes expanded: "<<nodes_expanded_A_star_euclidean;
    auto ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "\n" << ms_int.count() << "ms\n";

    return 0;
}