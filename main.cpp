//////////////////////////////////////////////////////////////////////
/// @file main.cpp
/// @author Tao Wang@CS325 2014 Spring
/// @main file for testcases
//////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<string.h>
#include "invtree.hpp"
#include "rectoverlap.hpp"

/***********************main*******************************************/
/************************ extern variables ************************/
extern char input_file[];
/*****************************************************************/
int main(int argc, char *argv[]) {
	char defaultFile[100] = "test.dat";
    if (argc==1)  {
		strcpy(input_file, defaultFile);
	} else {
		strcpy(input_file, argv[1]);
	}
	
	//test for interval tree
	INVTree tree0;
	INVTreeNode *x0 = new INVTreeNode(5, 8, 0, RED, LEFT);
	tree0.Insert(x0);
	
	INVTreeNode *x1 = new INVTreeNode(16, 21, 1, RED, LEFT);
	tree0.Insert(x1);
	
	INVTreeNode *x2 = new INVTreeNode(25, 30, 2, RED, LEFT);
	tree0.Insert(x2);
	
	INVTreeNode *x3 = new INVTreeNode(26, 26, 3, RED, LEFT);
	tree0.Insert(x3);
	
	INVTreeNode *x4 = new INVTreeNode(17, 19, 4, RED, LEFT);
	tree0.Insert(x4);
	
	INVTreeNode *x5 = new INVTreeNode(15, 23, 5, RED, LEFT);
	tree0.Insert(x5);
	
	INVTreeNode *x6 = new INVTreeNode(8, 9, 6, RED, LEFT);
	tree0.Insert(x6);
	
	INVTreeNode *x7 = new INVTreeNode(0, 3, 7, RED, LEFT);
	tree0.Insert(x7);
	
	INVTreeNode *x8 = new INVTreeNode(6, 10, 8, RED, LEFT);
	tree0.Insert(x8);
	
	INVTreeNode *x9 = new INVTreeNode(19, 20, 9, RED, LEFT);
	tree0.Insert(x9);
	
	INVTreeNode *x10 = new INVTreeNode(25, 30, 10, RED, RIGHT);
	printf("Test for interval tree:\n");
	printf("The tree on page 350..\n");
	
	tree0.Print();
	
	INVTreeNode *i1 = new INVTreeNode(22, 25, 10, RED, LEFT);
	
	printf("i1 = [22 25]\n");
	if(tree0.FindOverlap(i1)) {
		printf("i1 overlaps with x!\n");
	} else {
		printf("i1 not overlaps with x!\n");
	}
	
	INVTreeNode *i2 = new INVTreeNode(11, 14, 10, RED, LEFT);
	
	printf("i2 = [11 14]\n");
	if(tree0.FindOverlap(i2)) {
		printf("i2 overlaps with x!\n");
	} else {
		printf("i2 not overlaps with x!\n");
	}
	
	INVTreeNode* i10 = tree0.SearchExactly(x10);
	printf("Delete [25 30], the tree becomes:\n");
	tree0.Delete(i10);
	
	tree0.Print();
	
	//test for rectoverlap
	printf("\nTest for rectoverlap:\n");
	if(rectoverlap()) {
		printf("There are two rectangles overlap.\n");
	} else {
		printf("There are no rectangles overlap.\n");
	}
	
	return 0;
}