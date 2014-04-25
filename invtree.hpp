#ifndef _INVTREE_H
#define _INVTREE_H

#include<stdlib.h>
#include<stdio.h>

#define RED 1
#define BLACK 0
#define LEFT 0
#define RIGHT 1

class INVTreeNode {
	friend class INVTree;
public:
	INVTreeNode() : left(NULL), right(NULL), parent(NULL){}
	INVTreeNode(const int d, const int h, const int xx, const int c, const int s, const int m = 0, INVTreeNode* p = NULL, INVTreeNode *l = NULL, INVTreeNode *r = NULL)
		: key(d), high(h), x(xx), color(c), side(s), max(m), left(l), right(r), parent(p) {}
	~INVTreeNode() {}
/*
	int getKey { return key;}
	int getColor {return color;}
	int getSide {return side;
	bool isBlack { return !color;}
	bool isRed {return color; }
	bool
*/	
	int key; //key is ylow
	int high; //high is yhigh
	int x; // x coordinate
	int color;
	int side;
	int max;
	INVTreeNode *left, *right, *parent;
};

class INVTree {
	public:
		INVTree();
		~INVTree() 
			{ destroy(root); delete nil;}
		bool FindOverlap(const INVTreeNode *x)
			{ return (Search(x) != this->nil) ? true : false; }
		INVTreeNode* SearchExactly(const INVTreeNode *i);
		//INVTreeNode* Min() {return Min(root);}
		//INVTreeNode* Max() {return Max(root);}
		void Print() const {Print(root);}
		void Insert(INVTreeNode *z);
		void Delete(INVTreeNode *z);
		void BSTInsert(INVTreeNode *z);
		//void BSTDelete(INVTreeNode *z);
		void Transplate(INVTreeNode* u, INVTreeNode* v);
		void LeftRotate(INVTreeNode *x);
		void RightRotate(INVTreeNode *y);
		void InsertFixup(INVTreeNode *z);
		void DeleteFixup(INVTreeNode *x);
	private:
		INVTreeNode* root;
		INVTreeNode* nil;
		INVTreeNode* Search(const INVTreeNode* i);
		void Print(INVTreeNode *ptr) const;
		void destroy(INVTreeNode *subtree);
		INVTreeNode* Min(INVTreeNode *ptr);
		INVTreeNode* Max(INVTreeNode *ptr);
		INVTreeNode* Successor(INVTreeNode *x);
		INVTreeNode* PreDecessor(INVTreeNode *x);
		bool overlap(const INVTreeNode *x, const INVTreeNode *i);
		void FixUpMax(INVTreeNode *x);
};

#endif
		
		
		
		