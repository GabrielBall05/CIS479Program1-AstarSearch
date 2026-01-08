//========================================
//Name: Gabriel Ball
//Date: Due 07/09/25
//UMID: 34556820
//Desc: A* Search Algorithm for Windy Maze
//========================================
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "Node.h";
using namespace std;

//Global variables for rows and columns
const int ROWS = 5;
const int COLS = 6;

void displayMaze(Node* maze[ROWS][COLS], bool pathing);
void initializeMaze(Node* maze[ROWS][COLS], string mazeString);
void aStar(Node* maze[ROWS][COLS], Node* startNode, Node* goalNode);
int heuristic(Node* curNode, Node* goalNode);
int moveCost(Node* curNode, Node* targetNode);
string getExploredKey(Node* node);
void insertFrontierPQ(vector<Node*>& frontier, Node* node);
void setOptimalPath(Node* goalNode, Node* startNode);

int main()
{
	//For screenshot purposes
	cout << endl << "Name: Gabriel Ball       UMID: 34556820       CIS-479 Summer II 2025       P1-WindyMazeA*" << endl << endl;

	//Make Maze
	Node* maze[ROWS][COLS];
	//Works with any size maze as long as ROWS and COLS global variables are set correctly
	string mazeString = "[]00[][][][][]########[][]##[]GG##[][]##[][][][][][][][][][]";
	initializeMaze(maze, mazeString); //Fill in nodes in maze with mazeString info
	cout << "Original Maze Configuration:" << endl;
	displayMaze(maze, false);

	//Begin algorithm
	aStar(maze, maze[0][1], maze[2][3]); //Sends maze, start node, and goal node
}

void aStar(Node* maze[ROWS][COLS], Node* startNode, Node* goalNode)
{
	vector<Node*> frontier;
	unordered_set<string> explored;
	int labelCounter = 0;

	//Set g(n), h(n), f(n), and label for start node
	startNode->setGn(0);
	startNode->setHn(heuristic(startNode, goalNode));
	startNode->setFn(startNode->getGn() + startNode->getHn());
	startNode->setLabel(to_string(labelCounter));
	labelCounter++;
	//Put start node in frontier
	frontier.push_back(startNode);

	//Loop until frontier is empty
	while (!frontier.empty())
	{
		//Picks smallest f(n) in frontier, which is at the front
		Node* cur = frontier.front();
		frontier.erase(frontier.begin());
		//Insert key for this node into explored set
		explored.insert(getExploredKey(cur));

		//Check if this node is the goal node
		if (cur == goalNode)
		{
			cur->setLabel("GG"); //Reset label if it was overwritten
			cout << "Goal Found at (" << cur->getRow() << "," << cur->getCol() << ") with label GG "
				<< "when expanding node with label " << cur->getParent()->getLabel() << endl
				<< endl << "Completed Maze via A* Search:" << endl;
			displayMaze(maze, false); //Display final maze
			cout << "Optimal Path (Marked with asterisks):" << endl;
			//Mark optimal path by changing parents' pathing labels until start is reached
			setOptimalPath(goalNode, startNode);
			displayMaze(maze, true); //Display original maze with 
			return;
		}

		//Arrays for neighbor exploration order
		int dRow[] = { 0, -1, 0, 1 };
		int dCol[] = { -1, 0, 1, 0 };
		//Check neighbors
		for (int direction = 0; direction < 4; direction++) //0: W, 1: N, 2: E, 3: S
		{
			int newRow = cur->getRow() + dRow[direction];
			int newCol = cur->getCol() + dCol[direction];

			if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS)
				continue; //Skip this neighbor, it is out of bounds
			
			Node* neighbor = maze[newRow][newCol];
			if (neighbor->getIsObstacle() || explored.count(getExploredKey(neighbor)))
				continue; //Skip this neighbor, it is an obstacle or was already explored

			//G(n) for this node is current cost from start, or g(n), plus the cost to get to its neighbor
			int curGn = cur->getGn() + moveCost(cur, neighbor);
			if (curGn < neighbor->getGn()) //Cheaper path found
			{
				//Set g(n), h(n), f(n), and parent for this neighbor
				neighbor->setGn(curGn);
				neighbor->setHn(heuristic(neighbor, goalNode));
				neighbor->setFn(neighbor->getGn() + neighbor->getHn());
				neighbor->setParent(cur); //Parent is the one that explored it (cur)

				//Update label
				neighbor->setLabel(to_string(labelCounter));
				labelCounter++;
				//Add it to frontier
				insertFrontierPQ(frontier, neighbor);
			}
		}
	}
	//If frontier is empty before goal is found, no path exists
	cout << "Goal Not Found. No path exists" << endl;
}

int heuristic(Node* curNode, Node* goalNode)
{
	//Horizontal (east/west) distance between node and goal
	int horizontal = goalNode->getCol() - curNode->getCol();
	//Vertical (north/south) distance between node and goal
	int vertical = goalNode->getRow() - curNode->getRow();
	//Horizontal cost is 3 if going east (horizontal > 0) and 1 if going west (horizontal < 0)
	int costH = (horizontal > 0) ? 3 : 1;
	//Vertical cost is 2 regardless of direction being north or south
	int costV = 2;
	return (abs(horizontal) * costH) + (abs(vertical) * costV); //Returns calculated h(n)
}

int moveCost(Node* curNode, Node* neighbor)
{
	//Difference between columns gets horizontal distance and direction
	int horizontal = curNode->getCol() - neighbor->getCol();
	//Since this function is only used to find direction/cost of a
	//node and its neighbor, it only needs to check -1 and 1 distances
	if (horizontal == 1) return 1; // West = 1
	if (horizontal == -1) return 3; //East = 3
	return 2; //North or South = 2
}

void insertFrontierPQ(vector<Node*>& frontier, Node* node)
{
	//Loop through frontier until end is reached
	for (vector<Node*>::iterator it = frontier.begin(); it != frontier.end(); ++it)
	{
		int f1 = (*it)->getFn();
		int f2 = node->getFn();

		//Lower f(n) goes first
		if (f1 > f2)
		{
			//Insert just before the first node with higher f(n)
			frontier.insert(it, node);
			return;
		}

		//f(n) tie breaker is based on lower label
		if (f1 == f2)
		{
			string l1 = (*it)->getLabel();
			string l2 = node->getLabel();

			//Only compare numerically if both labels are digits
			if (isdigit(l1[0]) && isdigit(l2[0]) && (stoi(l1) > stoi(l2)))
			{
				//Insert just before first node with higher label if f(n) was tied
				frontier.insert(it, node);
				return;
			}
		}
	}
	//Insert at end here - loop ended, this node has the highest f(n)
	frontier.push_back(node);
}

string getExploredKey(Node* node)
{
	//Key is just row,col for hash table
	return to_string(node->getRow()) + "," + to_string(node->getCol());
}

void initializeMaze(Node* maze[ROWS][COLS], string mazeString)
{
	string label;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			label = mazeString.substr(0, 2); //First 2 characters of mazeString
			//Make node in maze at ith row and jth column with overloaded constructor
			maze[i][j] = new Node(i, j, label, label == "GG", label == "##");
			mazeString = mazeString.substr(2); //Remove first 2 characters of mazeString
		}
	}
}

void displayMaze(Node* maze[ROWS][COLS], bool pathing)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			//If pathing is true, we want to display pathing labels for displaying optimal path. Otherwise, display regular label 
			cout << setw(2) << setfill('0') << ((pathing) ? maze[i][j]->getPathingLabel() : maze[i][j]->getLabel()) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void setOptimalPath(Node* goalNode, Node* startNode)
{
	Node* cur = goalNode->getParent(); //Skip overwriting goal node with **
	while (cur && cur != startNode) // Loop from goal to start
	{
		cur->setPathingLabel("**"); //Set new (pathing) label
		cur = cur->getParent();
	}
}