#pragma once
#include <string>
using namespace std;
class Node
{
private:
	int row;
	int col;
	int gn; //Cost So Far
	int hn; //Heuristic
	int fn; //Estimated Total Cost 
	string label;
	Node* parent;
	bool isGoal;
	bool isObstacle;
	string pathingLabel; //Original label unless on optimal path (**)
public:
	//Constructors
	Node();
	Node(int r, int c, string l, bool g, bool o);

	//Getters
	int getRow() const;
	int getCol() const;
	int getGn() const;
	int getHn() const;
	int getFn() const;
	string getLabel() const;
	Node* getParent() const;
	bool getIsGoal() const;
	bool getIsObstacle() const;
	string getPathingLabel() const;

	//Setters
	void setRow(int r);
	void setCol(int c);
	void setGn(int g);
	void setHn(int h);
	void setFn(int f);
	void setLabel(string l);
	void setParent(Node* p);
	void setPathingLabel(string pl);
};