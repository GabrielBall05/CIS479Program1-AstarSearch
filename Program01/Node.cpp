#include "Node.h"

Node::Node() {}

Node::Node(int r, int c, string l, bool g, bool o)
{
	row = r;
	col = c;
	label = l;
	isGoal = g;
	isObstacle = o;
	gn = INT_MAX;
	pathingLabel = l;
}

int Node::getRow() const
{
	return row;
}

int Node::getCol() const
{
	return col;
}

int Node::getGn() const
{
	return gn;
}

int Node::getHn() const
{
	return hn;
}

int Node::getFn() const
{
	return fn;
}

string Node::getLabel() const
{
	return label;
}

Node* Node::getParent() const
{
	return parent;
}

bool Node::getIsGoal() const
{
	return isGoal;
}

bool Node::getIsObstacle() const
{
	return isObstacle;
}

string Node::getPathingLabel() const
{
	return pathingLabel;
}


void Node::setRow(int r)
{
	row = r;
}

void Node::setCol(int c)
{
	col = c;
}

void Node::setGn(int g)
{
	gn = g;
}

void Node::setHn(int h)
{
	hn = h;
}

void Node::setFn(int f)
{
	fn = f;
}

void Node::setLabel(string l)
{
	label = l;
}

void Node::setParent(Node* p)
{
	parent = p;
}

void Node::setPathingLabel(string pl)
{
	pathingLabel = pl;
}