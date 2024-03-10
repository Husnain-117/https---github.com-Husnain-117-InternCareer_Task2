#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Graph
{
public:
    unordered_map<char, vector<char>> adj;

    void addEdge(char u, char v, bool direction)
    {
        adj[u].push_back(v);
        if (!direction)
        {
            adj[v].push_back(u);
        }
    }

    void print()
    {
        for (auto i : adj)
        {
            cout << i.first << " -> ";
            for (auto j : i.second)
            {
                cout << j << ", ";
            }
            cout << endl;
        }
    }

    void printAdjacencyMatrix(vector<vector<char>> &matrix)
    {
        cout<<"-----------------------------------"<<endl;
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            for (size_t j = 0; j < matrix[i].size(); ++j)
            {
                if (matrix[i][j] != '\0')
                {
                    cout << " |";

                    cout << matrix[i][j] << "";
                    cout << "| ";
                }
                else
                {
                    cout << " |_| ";
                }
            }
            cout << endl;
            cout << endl;
            // cout<<"----------------------------------"<<endl;
        }
        cout<<"-----------------------------------"<<endl;
    }

    vector<vector<char>> createAdjacencyMatrix()
    {

        int numVertices = adj.size();

        vector<vector<char>> matrix(numVertices, vector<char>(numVertices, '\0'));

        int index = 0;
        unordered_map<char, int> vertexIndexMap;

        // Assign indices to each vertex for referencing in the matrix
        for (auto &pair : adj)
        {
            vertexIndexMap[pair.first] = index++;
        }

        // Iterate through each vertex and its neighbors to update the matrix
        for (auto it = adj.begin(); it != adj.end(); ++it)
        {
            char fromVertex = it->first;
            int fromIndex = vertexIndexMap[fromVertex];
            // cout<<"-----"<<fromVertex <<"----"<<fromIndex<<endl;

            for (auto neighborIt = it->second.begin(); neighborIt != it->second.end(); ++neighborIt)
            {
                char toVertex = *neighborIt;
                int toIndex = vertexIndexMap[toVertex];
                // cout<<"-----"<<toVertex <<"----"<<toIndex<<endl;

                matrix[fromIndex][toIndex] = fromVertex;
                matrix[toIndex][fromIndex] = toVertex;
            }
        }

        // Print only the true positions with node values
        printAdjacencyMatrix(matrix);

        // Return the completed adjacency matrix
        return matrix;
    }
};

int main()
{
    Graph g;

    char u, v;
    char choice;

    do
    {
        cout << "Enter edge (u v): ";
        cin >> u >> v;

        // Assuming undirected edges, change true to false if you want directed edges
        g.addEdge(u, v, 1);

        cout << "Do you want to add another edge? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    // Printing the graph
    cout << "\nGraph:\n";
    g.print();

    // Creating and printing the adjacency matrix
    cout << "\nAdjacency Matrix:\n";
    g.createAdjacencyMatrix();

    return 0;
}
