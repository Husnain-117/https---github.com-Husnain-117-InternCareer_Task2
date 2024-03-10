#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <limits>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <set>
#include <unordered_map>
#include <queue>


// file header
// #include "heap.h"

// ANSI escape codes for text color
#define RESET "\033[0m"
#define RED "\033[31m"
#define DARK_BLUE "\033[34m"
#define LIGHT_BLUE "\033[94m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define PINK "\033[39m"
#define BROWN "\033[38;2;139;69;19m"

using namespace std;

struct Node
{
    char symbol;
    int weight;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *up = nullptr;
    Node *down = nullptr;
};

class Heap
{
public:
    int arr[100];
    string name[100];
    int size = 0;

    Heap()
    {
        arr[0] = -1;
        name[0] = "-1";
        size = 0;
    }
    void insert(int val, string n)
    {
        size = size + 1;
        int index = size;
        arr[index] = val;
        name[index] = n;

        while (index > 1)
        {
            int parentIndex = index / 2;
            if (arr[parentIndex] < arr[index])
            {
                swap(arr[parentIndex], arr[index]);
                swap(name[parentIndex], name[index]);
                index = parentIndex;
            }
            else
            {
                break;
            }
        }
    }

    void print()
    {
        cout << "Name->Score " << endl;
        for (int i = 0; i < size; i++)
        {
            // Display only the first 5 characters of the name
            string Name5 = name[i].substr(0, 5);
            if (i == 0)
            {
            }
            else
            {
                cout << i << ". " << Name5 << " -> " << arr[i] << endl;
            }
        }
    }
};

class Graph
{
private:
    int rows, cols;
    Node *nodes;
    vector<vector<Node *>> parent;

public:
    Graph(int rows, int cols) : rows(rows), cols(cols)
    {
        nodes = new Node[rows * cols];
        parent = vector<vector<Node *>>(rows, vector<Node *>(cols, nullptr)); // Initialize parent vector
        generateGraph(nodes, rows, cols);
    }
    ~Graph()
    {

        delete[] nodes;
    }

    void generateGraph(Node *grid, int rows, int cols)
    {

        srand(time(0));

        // Set all nodes to '.' (empty space)
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {

                grid[i * cols + j].symbol = '.';
            }
        }
        grid[1].symbol = 'C';

        // Set the second last node to 'F'
        grid[rows * cols - 2].symbol = 'F';

        // Randomly place obstacles ('#')
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (rand() % 5 == 0 && grid[i * cols + j].symbol == '.')
                {
                    grid[i * cols + j].symbol = '#'; // Obstacle symbol
                }
            }
        }

        // Randomly place power-ups ('*')
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (rand() % 8 == 0 && grid[i * cols + j].symbol == '.')
                {
                    grid[i * cols + j].symbol = '*'; // Power-up symbol
                }
            }
        }
        // Randomly place '?' symbols at three locations
        int questionCount = 0;
        while (questionCount < 3)
        {
            int randomRow = rand() % rows;
            int randomCol = rand() % cols;

            if (grid[randomRow * cols + randomCol].symbol == '.')
            {
                grid[randomRow * cols + randomCol].symbol = '?';
                questionCount++;
            }
        }
        // Randomly place '+' symbols at three locations
        int plusCount = 0;
        while (plusCount < 3)
        {
            int randomRow = rand() % rows;
            int randomCol = rand() % cols;

            if (grid[randomRow * cols + randomCol].symbol == '.')
            {
                grid[randomRow * cols + randomCol].symbol = '+';
                plusCount++;
            }
        }
        // Connect nodes with their children and assign weights
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                Node *currentNode = &grid[i * cols + j];

                // Handle vertical boundary
                if (j == 0 || j == cols - 1)
                {
                    currentNode->symbol = '|';
                    // currentNode->left = 0;
                    // currentNode->right = 0;
                    // currentNode->down = 0;
                    continue;
                }

                // Connect left child
                if (j > 0)
                {
                    currentNode->left = &grid[i * cols + j - 1];
                    currentNode->left->weight = rand() % 10 + 1;
                }
                else
                {
                    currentNode->left = 0;
                }

                // Connect up child
                if (i > 0)
                {
                    currentNode->up = &grid[(i - 1) * cols + j];
                    currentNode->up->weight = rand() % 10 + 1;
                }
                else
                {
                    currentNode->up = 0;
                }

                // Connect right child
                if (j < cols - 1)
                {
                    currentNode->right = &grid[i * cols + j + 1];
                    currentNode->right->weight = rand() % 10 + 1;
                }
                else
                {
                    currentNode->right = 0;
                }

                // Connect down child
                if (i < rows - 1)
                {
                    currentNode->down = &grid[(i + 1) * cols + j];
                    currentNode->down->weight = rand() % 10 + 1;
                }
                else
                {
                    currentNode->down = 0;
                }

                // if(currentNode->left== 0){
                //     currentNode->left->weight=1;
                // }
                //   if(currentNode->right== 0){
                //     currentNode->right->weight=0;
                // }
                //   if(currentNode->up== 0){
                //     currentNode->up->weight=0;
                // }
                //   if(currentNode->down== 0){
                //     currentNode->down->weight=0;
                // }
                
             
                
            }
        }
    }

    void displayMaze() const
    {
        system("cls");

        int horizontalPadding = (100 - cols) / 2;

        int verticalPadding = (24 - rows) / 2;

        // Add vertical padding
        for (int i = 0; i < verticalPadding; ++i)
        {
            cout << '\n';
        }

        for (int i = 0; i < rows; ++i)
        {
            // Add horizontal padding
            cout << setw(horizontalPadding);
            // cout << grid[i * cols + j].symbol << " ";

            for (int j = 0; j < cols; ++j)
            {
                if (nodes[i * cols + j].symbol == '#')
                {
                    cout << RED << nodes[i * cols + j].symbol << RESET << " "; // Display '#' in red
                }
                else if (nodes[i * cols + j].symbol == '*')
                {
                    cout << YELLOW << nodes[i * cols + j].symbol << RESET << " "; // Display '#' in red
                }
                else if (nodes[i * cols + j].symbol == '<' || nodes[i * cols + j].symbol == '>' || nodes[i * cols + j].symbol == 'v' || nodes[i * cols + j].symbol == '^')
                {
                    cout << PINK << nodes[i * cols + j].symbol << RESET << " "; // Display '#' in red
                }
                else if (nodes[i * cols + j].symbol == 'C')
                {
                    cout << LIGHT_BLUE << nodes[i * cols + j].symbol << RESET << " "; // Display '#' in red
                }
                else if (nodes[i * cols + j].symbol == '+')
                {
                    cout << BROWN << nodes[i * cols + j].symbol << RESET << " "; // Display '#' in red
                }
                else
                {
                    cout << GREEN << nodes[i * cols + j].symbol << RESET << " "; // Display '#' in red
                }
            }

            cout << '\n';
            cout << '\n';
        }

        for (int i = 0; i < verticalPadding; ++i)
        {
            cout << '\n';
        }
          
            //                  //  * printing for weights

            //    for (int i = 0; i < rows; ++i)
            // {
            //     for (int j = 0; j < cols; ++j)
            //     {
            //         const Node *currentNode = &nodes[i * cols + j];

            //         cout << "Node (" << i << ", " << j << ") Weights: ";
            //         cout << "Left: " << (currentNode->left ? currentNode->left->weight : 1) << ", ";
            //         cout << "Right: " << (currentNode->right ? currentNode->right->weight : 1) << ", ";
            //         cout << "Up: " << (currentNode->up ? currentNode->up->weight : 1) << ", ";
            //         cout << "Down: " << (currentNode->down ? currentNode->down->weight : 1) << endl;
            //     }
            // }
            
    }
      void dijkstra()
    {
        int startRow = 0;
        int startCol = 1;
        int targetRow = rows - 1;
        int targetCol = cols - 1;

        // Create a set to store distances and nodes
        set<pair<int, pair<int, int>>> pq;

        // Create a vector to store distances
        vector<vector<int>> distance(rows, vector<int>(cols, INT8_MAX));

        // Set distance for the starting node to 0
        distance[startRow][startCol] = 0;

        // Insert the starting node into the set
        pq.insert({0, {startRow, startCol}});

        while (!pq.empty())
        {
            // Extract the node with the minimum distance
            pair<int, pair<int, int>> top = *pq.begin();
            pq.erase(pq.begin());

            int currentDistance = top.first;
            int currentRow = top.second.first;
            int currentCol = top.second.second;

            // Define neighbors (left, right, up, down)
            pair<int, int> neighbors[] = {
                {0, -1}, // Left
                {0, 1},  // Right
                {-1, 0}, // Up
                {1, 0}   // Down
            };

            for (const auto &neighbor : neighbors)
            {
                int newRow = currentRow + neighbor.first;
                int newCol = currentCol + neighbor.second;

                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols)
                {
                    Node *currentNode = &nodes[currentRow * cols + currentCol];
                    Node *neighborNode = nullptr;

                    if (neighbor.first == 0 && neighbor.second == -1)
                    {
                        neighborNode = currentNode->left;
                    }
                    else if (neighbor.first == 0 && neighbor.second == 1)
                    {
                        neighborNode = currentNode->right;
                    }
                    else if (neighbor.first == -1 && neighbor.second == 0)
                    {
                        neighborNode = currentNode->up;
                    }
                    else if (neighbor.first == 1 && neighbor.second == 0)
                    {
                        neighborNode = currentNode->down;
                    }

                    // Check if the neighbor node is not nullptr
                    if (neighborNode != nullptr)
                    {
                        int edgeWeight = neighborNode->weight;

                        if (currentDistance + edgeWeight < distance[newRow][newCol])
                        {
                            distance[newRow][newCol] = currentDistance + edgeWeight;

                            // Insert the updated distance and node into the set
                            pq.insert({distance[newRow][newCol], {newRow, newCol}});
                        }
                    }
                }
            }
        }

        // Print the distances (for debugging)
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                cout << distance[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Other functions

    Node *getNodes() const
    {
        return nodes;
    }

    int getRows() const
    {
        return rows;
    }

    int getCols() const
    {
        return cols;
    }

    void printAdjacencyList()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                Node *currentNode = &nodes[i * cols + j];
                cout << currentNode->symbol << ": ";

                cout << "[";
                if (currentNode->left)
                {
                    cout << currentNode->left->symbol;
                }
                if (currentNode->up)
                {
                    cout << "," << currentNode->up->symbol;
                }
                if (currentNode->right)
                {
                    cout << "," << currentNode->right->symbol;
                }
                if (currentNode->down)
                {
                    cout << "," << currentNode->down->symbol;
                }
                cout << "]";

                cout << endl;
            }
        }
    }
};

class Game
{
private:
    Graph *gameMaze;
    int carRow, carCol;
    int score;
    string playerName;
    chrono::steady_clock::time_point startTime;

public:
    Game()
    {
        gameMaze = nullptr;
    }
    Game(int rows, int cols) : score(0)
    {
        gameMaze = new Graph(rows, cols);
        carRow = 0;
        carCol = 1;
    }

    ~Game()
    {
        delete gameMaze;
    }
    void setPlayerName(const string &name)
    {
        playerName = name;
    }

    void handleInput(char input)
    {
        switch (input)
        {
        case 'w':
            moveCar(-1, 0);
            break;
        case 's':
            moveCar(1, 0);
            break;
        case 'a':
            moveCar(0, -1);
            break;
        case 'd':
            moveCar(0, 1);
            break;
        default:
            break;
        }
    }

    //
    void moveCar(int rowChange, int colChange)
    {
        int newRow = carRow + rowChange;
        int newCol = carCol + colChange;

        if (newRow >= 0 && newRow < gameMaze->getRows() && newCol >= 0 && newCol < gameMaze->getCols())
        {
            Node *currentNode = &gameMaze->getNodes()[carRow * gameMaze->getCols() + carCol];
            Node *nextNode = &gameMaze->getNodes()[newRow * gameMaze->getCols() + newCol];

            if (nextNode->symbol == '.' || nextNode->symbol == '*' || nextNode->symbol == ' ' || nextNode->symbol == '#' || nextNode->symbol == 'F' || nextNode->symbol == '?')
            {

                if (rowChange == 0 && colChange == 1)
                {

                    currentNode->symbol = '>';
                }
                else if (rowChange == 0 && colChange == -1)
                {

                    currentNode->symbol = '<';
                }
                else if (rowChange == -1 && colChange == 0)
                {

                    currentNode->symbol = '^';
                }
                else if (rowChange == 1 && colChange == 0)
                {

                    currentNode->symbol = 'v';
                }

                if (nextNode->symbol == '.')
                {
                    score += 1;
                }

                if (nextNode->symbol == '*')
                {
                    score += 3;
                }

                // Check if the next node is an obstacle
                if (nextNode->symbol == '#')
                {
                    score -= 5;
                    if (score < 0)
                    {
                        // SaveDataToFile();

                        Game manualGame(8, 16);

                        cout << "Game Over! You do not have enough points to handle the obstacle.\n";
                        cout << "Better Luck Next time... \n";

                        int choice;
                        cout << "0. Restart\n";
                        cout << "1. Back to Main Menu\n";
                        cout << "2. Exit\n";
                        cout << "Enter your choice: ";
                        cin >> choice;

                        switch (choice)
                        {
                        case 0:
                            // Restart the game

                            manualGame.runGame(false);

                            break;
                        case 1:
                            // Go back to the main menu
                            mainMenu();
                            break;
                        case 2:
                            // Exit the game
                            exit(0);
                            break;
                        default:
                            cout << "Invalid choice. Exiting the game.\n";
                            exit(0);
                        }
                    }
                }

                // Check if the car reached the finish point
                if (nextNode->symbol == 'F')
                {
                    SaveDataToFile();

                    Game manualGame(8, 16);
                    chrono::steady_clock::time_point endTime = chrono::steady_clock::now();
                    chrono::duration<double> elapsedTime = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);

                    cout << "Congratulations! You reached the finish Point.\n";
                    score = score - (elapsedTime.count() / 4);
                    cout << "Player: " << playerName << "\tScore: " << score << "\tTime: " << fixed << setprecision(2) << elapsedTime.count() << " seconds\n";

                    int choice;
                    cout << "0. Restart\n";
                    cout << "1. Back to Main Menu\n";
                    cout << "2. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice)
                    {
                    case 0:
                        // Restart the game
                        manualGame.runGame(false);

                        break;
                    case 1:
                        // Go back to the main menu
                        mainMenu();
                        break;
                    case 2:
                        // Exit the game
                        exit(0);
                        break;
                    default:
                        cout << "Invalid choice. Exiting the game.\n";
                        exit(0);
                    }
                }
                if (nextNode->symbol == '?')
                {
                    // Handle the case when the car encounters a '?'
                    // Find a random empty spot ('.') to place the car
                    int randomRow, randomCol;
                    do
                    {
                        randomRow = rand() % gameMaze->getRows();
                        randomCol = rand() % gameMaze->getCols();
                    } while (gameMaze->getNodes()[randomRow * gameMaze->getCols() + randomCol].symbol != '.');

                    // Update the current node symbol to '.'
                    currentNode->symbol = '.';

                    carRow = randomRow;
                    carCol = randomCol;

                    // Update the display
                    gameMaze->displayMaze();
                    return; // Exit the function after handling the special case
                }

                nextNode->symbol = 'C';
                carRow = newRow;
                carCol = newCol;

                // Update the display
                //  cout << "Score: " << score << '\n';

                gameMaze->displayMaze();
            }
        }
    }

    // Update the SaveDataToFile function
    // Update the SaveDataToFile function
    void SaveDataToFile()
    {
        ofstream outFile("data.txt", ios::app); // Append to the file

        if (!outFile)
        {
            cerr << "Error creating file!" << endl;
        }

        int lineNumber = 1;

        // If this is the first entry, write the header

        outFile << playerName << "," << score << endl;

        // Increment the line number for the next entry
        lineNumber++;

        // Close the file
        outFile.close();
    }

    // Update the loadPlayerData function
    void loadPlayerData()
    {
        ifstream inFile("data.txt");

        if (!inFile)
        {
            cerr << "Error opening file!" << endl;
        }

        // Read data from the file
        string line;
        while (getline(inFile, line))
        {
            cout << RED << line << RESET << endl; // Print the entire line from the file
        }

        // Close the file
        inFile.close();
    }

    void ViewHighestScore()
    {
        Heap heap;
        ifstream inFile("data.txt");

        if (!inFile)
        {
            cerr << "Error opening file!" << endl;
            return;
        }

        // Read and display scores from the file
        string line;
        while (getline(inFile, line))
        {

            stringstream ss(line);
            string playerName;
            string scoreString;

            getline(ss, playerName, ',');
            getline(ss, scoreString, ',');

            int score = stoi(scoreString);

            heap.insert(score, playerName);
        }
        heap.print();

        inFile.close();
    }

    void runGame(bool automated)
    {

        char input;
        cout << "Enter your name: ";
        cin >> playerName;
        // Record the start time when the game starts
        startTime = chrono::steady_clock::now();
        do
        {
            chrono::steady_clock::time_point currentTime = chrono::steady_clock::now();
            chrono::duration<double> elapsedTime = chrono::duration_cast<chrono::duration<double>>(currentTime - startTime);

            cout << "Player: " << playerName << "\tScore: " << score << "\tTime: " << fixed << setprecision(2) << elapsedTime.count() << " seconds\n\n";

            gameMaze->displayMaze();

            // Get user input in manual mode
            if (!automated)
            {
                input = _getch();

                // Handle user input
                handleInput(input);
            }
            else
            {

            
            }
            

        } while (input != 'q');
        // Calculate the elapsed time when the game ends
    }
    // Inside the Graph class
    void mainMenu()
    {
        Game manualGame(8, 16);

        int choice;

        cout << "\n\n\n";
        cout << setw((80));
        cout << "---------------------------------\n";
        cout << setw((52));
        cout << DARK_BLUE << " Welcome to the Race Car Game! \n"
             << RESET;
        cout << setw((82));
        cout << "---------------------------------\n\n\n";

        do
        {
            cout << setw((69));
            cout << "1. View Rules\n"
                 << setw((70));
            cout << "2. Manual Mode\n"
                 << setw((73));
            cout << "3. Automated Mode\n"
                 << setw((77));
            cout << "4. View Highest Score\n"
                 << setw((64));
            cout << "5. Exit\n\n"
                 << setw((81));
                  cout << "6. Print shortest PAth\n\n"
                 << setw((81));
            cout << "Enter your choice (1, 2, 3, or 4): ";

            cin >> choice;

            switch (choice)
            {
            case 1:
                displayRules();
                break;
            case 2:
                manualGame.runGame(false);
                manualGame.SaveDataToFile();
                break;
            case 3:
                manualGame.runGame(true);
                manualGame.SaveDataToFile();
                break;
            case 4:
                ViewHighestScore();
                break;
            case 5:
                cout << "Exiting the Race Car Game. Goodbye!\n";
                break;
            case 6:
                // View Shortest Path
                gameMaze->dijkstra();
            //    gameMaze->printShortestPath();
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
            }

        } while (choice != 5);
    }
    void displayRules()
    {
        cout << LIGHT_BLUE << "Rules:\n"
             << RESET;
        cout << "1. Movement of the car gives 1 point.\n";
        cout << "2. Car passing through '*' gets 3 points.\n";
        cout << "3. Car passing through '#' deducts 5 points.\n";
        cout << "4. Time will also affects your score\n";
        cout << "5. Game will be over if your score is negative.\n";
        cout << "6. To win, you must reach the 'F' node.\n\n";
    }
};

int main()
{
    Game obj;

    obj.mainMenu();

    return 0;
}