#include <iostream>
#include <queue>
#include <vector>
#include <iterator>
#include <map>
using namespace std;

#define Y_POS 9
#define X_POS 10


struct Point //store coordinates of points in a map
{
    int x;
    int y;
};

struct Node //this will store the parent child info so we can reconstruct the path
{
    Point parent;
    Point child;
};


// check whether given cell (row, col) is a valid
// cell or not.
bool isValid(int y_given, int x_given)
{
    // return true if given x and y value is within map range
    return (y_given >= 0) && (y_given < Y_POS) &&
        (x_given >= 0) && (x_given < X_POS);
}

// These arrays are used to get row and column
// numbers of 4 neighbours of a given cell
int rowNum[] = { -1, 0, 0, 1 };
int colNum[] = { 0, -1, 1, 0 };

// function to find the shortest path between
// a given source cell to a destination cell.
vector<Point> BFS(int mat[Y_POS][X_POS], Point src, Point dest)
{
    bool visited[Y_POS][X_POS];
    memset(visited, false, sizeof visited);
    std::vector<Point> shortest_path; //this will store our shortest path
    std::vector<Node> parent_child; //this stores the parent-child info

    // Mark the source cell as visited
    visited[src.x][src.y] = true;

    // Create a queue for BFS
    queue<Point> q;

    q.push(src);  // Enqueue source cell

    //Create an iterator
    map<Point, Point>::iterator itr;

    // Do a BFS starting from source cell
    while (!q.empty())
    {
        Point curr_cell = q.front();

        if (curr_cell.x == dest.x && curr_cell.y == dest.y) {
            Node check = parent_child[parent_child.size() - 1];
            while (check.parent.x != src.x && check.parent.y != src.y) {               
                for (int i = parent_child.size() - 1; i > 0; i--) {
                    if ((parent_child[i].child.x == check.parent.x)
                        && (parent_child[i].child.y == check.parent.y)) {
                        shortest_path.push_back(parent_child[i].child);
                        check = parent_child[i];
                        break;
                    }
                }
            }
            //add the missing elements and reverse the list to get the shortest path
            shortest_path.push_back(parent_child[0].child);
            shortest_path.push_back(src);
            reverse(shortest_path.begin(), shortest_path.end());
            shortest_path.push_back(dest);
            return shortest_path;
        }

        // Otherwise dequeue the front cell in queue
        // and enqueue the next cell
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int next_x = curr_cell.x + rowNum[i];
            int next_y = curr_cell.y + colNum[i];

            // if adjacent cell is valid, has path and
            // not visited yet, enqueue it.
            if (isValid(next_x, next_y) && mat[next_x][next_y]==0 &&
                !visited[next_x][next_y])
            {
                // mark cell as visited and add it to the queue
                visited[next_x][next_y] = true;
                Point next_cell = {next_x, next_y};
                q.push(next_cell);

                //set next cell as the parent of the current cell
                parent_child.push_back({ curr_cell, next_cell });
            }
        }
    }
}

int main() //just to test the function
{
    int map[Y_POS][X_POS] =
    { //given a map of matrices
        { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 1, 1, 0, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 0, 1, 1, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 1 },
        { 1, 1, 0, 0, 0, 0, 1, 0, 0, 0 }
    };

    Point source = { 0, 0 };
    Point destination = { 8, 9 };

    std::vector< Point > path = BFS(map, source, destination);
    for (int i = 0; i < path.size(); i++) {
        cout <<'{'<< path[i].x << ',' << path[i].y << '}';
    }
    

    return 0;
}
