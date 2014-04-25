//////////////////////////////////////////////////////////////////////
/// @file rectoverlap.cpp
/// @author Tao Wang@CS325 2014 Spring
/// @Load the input data of the testcases
//////////////////////////////////////////////////////////////////////
using namespace std;
#include<vector>
#include "invtree.hpp"

/*********************subroutines****************************/
void merge_sort(int low, int high, vector<INVTreeNode*> &a);
void merge(int low, int mid, int high, vector<INVTreeNode*> &a);

/**********************global variables***********************/
char input_file[100];

/**********************rectoverlap ****************************/
//@Load data from testcases and decide whether or not there are two
//@rectangles overlap
///////////////////////////////////////////////////////////////////////
bool rectoverlap( ) {
	FILE* fp;
	
	if ( fopen(input_file, "r") == NULL) {
		printf("\nError: cannot open input file %s for read!\n", input_file);
		exit(1);
	}

	/******* read the input ***************************/

	printf("\nLoading input file ... \n");
	
	vector<INVTreeNode*> rectEdges;
	fp = fopen(input_file, "r");
	
	int n;
	char line[50];

	fgets(line, 50, fp);
	
	sscanf(line, "%d", &n);
	
	int i;
	int x1, x2, y1, y2;
	
	for(i = 0; i < n; i++) {
		fgets(line, 50, fp);
		sscanf(line, "%d %d %d %d", &x1, &x2, &y1, &y2);
		INVTreeNode *tmpL = new INVTreeNode(y1, y2, x1, RED, LEFT);
		rectEdges.push_back(tmpL);
		INVTreeNode *tmpR = new INVTreeNode(y1, y2, x2, RED, RIGHT);
		rectEdges.push_back(tmpR);
	}
	
	merge_sort(0, 2*n - 1, rectEdges);
	
	
	int size = rectEdges.size();
	printf("rectEdges after merge_sort:\n");
	for(i = 0; i < size; i++) {
		printf("ylow: %d, yhigh: %d, x: %d, max: %d, ", rectEdges[i]->key, rectEdges[i]->high, rectEdges[i]->x, rectEdges[i]->max);
		
		if(rectEdges[i]->side == LEFT) {
			printf("side = LEFT\n");
		} else {
			printf("side = RIGHT\n");
		}
	}
	
	INVTree tree;
	
	for(i = 0; i < size; i++) {
		if(rectEdges[i]->side == LEFT) { // if the edge is a left edge
			//if it overlaps with some edges, return true
			if(tree.FindOverlap(rectEdges[i])) {
				return true;
			}
			//otherwise, insert it into the tree
			tree.Insert(rectEdges[i]);
		} else { // if the edge is a right edge
			//delete the left edge from inverval tree
			INVTreeNode* leftEdge = tree.SearchExactly(rectEdges[i]);
			tree.Delete(leftEdge);
		}
	}
	
	return false;
}

/*****************************merge_sort************************************/				
void merge_sort(int low, int high, vector<INVTreeNode*> &a)
{
	int mid;
	if(low<high)
	{
		mid = (low+high)/2;
		merge_sort(low, mid, a);
		merge_sort(mid+1, high, a);
		merge(low, mid, high, a);
	}
}

/******************************merge****************************************/
void merge(int low, int mid, int high, vector<INVTreeNode*> &a)
{
	int sz = a.size();
	vector<INVTreeNode*> b(sz);
	int h,i,j,k;
	h=low;
	i=low;
	j=mid+1;

	while((h<=mid)&&(j<=high))
	{
		if(a[h]->x <= a[j]->x )
		{
			b[i] = a[h];
			h++;
		} else {
			b[i] = a[j];
			j++;
		}
		i++;
	}
	
	if(h > mid) {
		for(k = j; k <= high; k++) {
			b[i] = a[k];
			i++;
		}
	} else {
		for(k = h;k <= mid; k++) {
			b[i] = a[k];
			i++;
		}
	}
	
	for(k = low; k <= high; k++) {
		a[k] = b[k];
	}
}
/********************************************************************************************/