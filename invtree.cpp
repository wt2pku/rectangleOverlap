#include "invtree.hpp"


int ITMAX( int a, int b) {
	if(a > b) {
		return a;
	} 
	
	return b;
} 

INVTree::INVTree( ) {
	nil = new INVTreeNode;
	nil->key = -10000000;
	nil->color = BLACK;
	nil->side = LEFT;
	nil->x = -100000000;
	nil->high = -100000000;
	nil->max = -100000000;
	nil->left = nil->right = nil->parent = nil;
	root = new INVTreeNode;
	root = nil;
}

void INVTree::destroy(INVTreeNode* subTree) {
	if(subTree != nil) {
		destroy(subTree->left);
		destroy(subTree->right);
		delete subTree;
	}
}

INVTreeNode* INVTree::Min(INVTreeNode* x) {
	INVTreeNode* y = x;
	while( y->left != nil) {
		y = y->left;
	}
	return y;
}

INVTreeNode* INVTree::Max(INVTreeNode* x) {
	INVTreeNode* y = x;
	while( y->right != nil) {
		y = y->right;
	}
	
	return y;
}

INVTreeNode* INVTree::Successor(INVTreeNode* x) {
	if(x->right != NULL) {
		return Min(x->right);
	}
	
	INVTreeNode* y = x->parent;
	while(y != nil && x == y->right) {
		x = y;
		y = y->parent;
	}
	return y;
}

INVTreeNode* INVTree::PreDecessor(INVTreeNode* x) {
	if(x->left != NULL) {
		return Max(x->left);
	}
	
	INVTreeNode* y = x->parent;
	while(y != nil && x == y->left) {
		x = y;
		y = y->parent;
	}
	return y;
}

void INVTree::BSTInsert(INVTreeNode *z) {
	INVTreeNode* y = nil;
	INVTreeNode* x = root;
	while( x != nil) {
		y = x;
		if(z->key < x->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	z->parent = y;
	//if tree is empty
	if( y == nil) {
		root = z;
	} else if( z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}
	
}

void INVTree::Transplate(INVTreeNode* u, INVTreeNode* v) {
	if( u->parent == nil) {
		root = v;
	} else if( u == u->parent->left) {
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}
	
	v->parent = u->parent;

	//update max field?
}

void INVTree::LeftRotate(INVTreeNode *x) {
	INVTreeNode* y = x->right; // set y
	x->right = y->left;
	if(y->left != nil) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if(x->parent == nil) {
		root = y;
	} else if( x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	
	y->left = x;
	x->parent = y;
	//update max field
	y->max = x->max;
	x->max = ITMAX(x->high, ITMAX(x->left->max, x->right->max));
}

void INVTree::RightRotate(INVTreeNode *y) {
	INVTreeNode* x = y->left;
	y->left = x->right;
	if(x->right != nil) {
		x->right->parent = y;
	}
	x->parent = y->parent;
	if(y->parent == nil) {
		root = x;
	} else if(y == y->parent->left) {
		y->parent->left = x;
	} else {
		y->parent->right = x;
	}
	
	x->right = y;
	y->parent = x;
	//update max field
	x->max = y->max;
	y->max = ITMAX(y->high, ITMAX(y->left->max, y->right->max));
}

void INVTree::Insert(INVTreeNode *z) {
	BSTInsert(z);
	z->left = nil;
	z->right = nil;
	z->color = RED;
	//update max field
	FixUpMax(z);
	InsertFixup(z);
}

void INVTree::InsertFixup(INVTreeNode *z) {
	while(z->parent->color == RED) {
		if(z->parent == z->parent->parent->left) {
			INVTreeNode* y = z->parent->parent->right;
			if(y->color == RED) { // case 1
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else {
				if( z == z->parent->right) { // case 2
					z = z->parent;
					LeftRotate(z);
				}
				z->parent->color = BLACK; // case 3
				z->parent->parent->color = RED;
				RightRotate(z->parent->parent);
			}
		} else {
			INVTreeNode* y = z->parent->parent->left;
			if(y->color == RED) { // case 1
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else {
				if( z == z->parent->left) { // case 2
					z = z->parent;
					RightRotate(z);
				}
				z->parent->color = BLACK; // case 3
				z->parent->parent->color = RED;
				LeftRotate(z->parent->parent);
			}
		}
	}
	root->color = BLACK;
}
	
void INVTree::Delete(INVTreeNode* z) {
	if(z == nil) {
		return;
	}
	INVTreeNode* y = z;
	int yOrgColor = y->color;
	INVTreeNode* x;
	if(z->left == nil) {
		x = z->right;
		Transplate(z, z->right);
	} else if(z->right == nil) {
		x = z->left;
		Transplate(z, z->left);
	} else {
		y = Min(z->right);
		yOrgColor = y->color;
		x = y->right;
		if(y->parent != z) {
			INVTreeNode* tmp = y->right;
			Transplate(y, y->right);
			//update max field
			FixUpMax(tmp->parent);
			y->right = z->right;
			y->right->parent = y;
			
		} else {
			x->parent = y;
		}
		
		Transplate(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
		//update max field
		y->max = ITMAX(y->high, ITMAX(y->left->max, y->right->max));
	}
	//update max field
	FixUpMax(z->parent);
	
	//fixup
	if(yOrgColor == BLACK) {
		DeleteFixup(x);
	}
	
	//delete z
	delete z;
}	

void INVTree::DeleteFixup(INVTreeNode* x) {
	while(x != root && x->color == BLACK) {
		if(x == x->parent->left) {
			INVTreeNode* w = x->parent->right;
			if(w->color == RED) { //case 1
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotate(x->parent);
				w = x->parent->right;
			}
			
			if(w->left->color == BLACK && w->right->color == BLACK) { // case 2
				w->color = RED;
				x = x->parent;
			} else {
				if(w->right->color == BLACK) { // case 3
					w->left->color = BLACK;
					w->color = RED;
					RightRotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color; // case 4
				x->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotate(x->parent);
				x = root;
			}
		} else {
			INVTreeNode* w = x->parent->left;
			if(w->color == RED) { //case 1
				w->color = BLACK;
				x->parent->color = RED;
				RightRotate(x->parent);
				w = x->parent->left;
			}
			
			if(w->left->color == BLACK && w->right->color == BLACK) { // case 2
				w->color = RED;
				x = x->parent;
			} else {
				if(w->left->color == BLACK) { // case 3
					w->right->color = BLACK;
					w->color = RED;
					LeftRotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color; // case 4
				x->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

INVTreeNode* INVTree::Search(const INVTreeNode* i) {
	INVTreeNode* x = root;
	 while((x != nil) && (!overlap(i, x))) {
		if((x->left != nil) && (x->left->max > i->key)) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	/*
	printf("In Search: ylow: %d, yhigh: %d, x: %d, max: %d, ", x->key, x->high, x->x, x->max);
	if(x->color == RED) {
		printf("color = RED, ");
	} else {
		printf("color = BLACK, ");
	}
	
	if(x->side == LEFT) {
		printf("side = LEFT\n");
	} else {
		printf("side = RIGHT\n");
	}
	*/
	return x;
}

INVTreeNode* INVTree::SearchExactly(const INVTreeNode* i) {
//	printf("i->key: %d, i->high: %d\n", i->key, i->high);
	INVTreeNode* x = root;
	 while(x != nil) {
	//	printf("x->key: %d, x->high: %d\n", x->key, x->high);
		if((x->key == i->key) && (x->high == i->high)) {
	/*		printf("In search exactly: ylow: %d, yhigh: %d, x: %d, max: %d, ", x->key, x->high, x->x, x->max);
			if(x->color == RED) {
				printf("color = RED, ");
			} else {
				printf("color = BLACK, ");
			}
			
			if(x->side == LEFT) {
				printf("side = LEFT\n");
			} else {
				printf("side = RIGHT\n");
			}*/
			return x;
		}
		
		if(x->key > i->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	
	return nil;
}

bool INVTree::overlap(const INVTreeNode *x, const INVTreeNode *i) { 
	
	if( (i->high >= x->key) && (x->high >= i->key)) {
		return true;
	} else {
		return false;
	}
}

void INVTree::Print(INVTreeNode *ptr) const {
	if(ptr != nil) {
		Print(ptr->left);
		printf("ylow: %d, yhigh: %d, x: %d, max: %d, ", ptr->key, ptr->high, ptr->x, ptr->max);
		if(ptr->color == RED) {
			printf("color = RED, ");
		} else {
			printf("color = BLACK, ");
		}
		
		if(ptr->side == LEFT) {
			printf("side = LEFT\n");
		} else {
			printf("side = RIGHT\n");
		}
		
		Print(ptr->right);
	}
}

void INVTree::FixUpMax(INVTreeNode * x) {
  while(x != nil) {
    x->max=ITMAX(x->high,ITMAX(x->left->max,x->right->max));
    x=x->parent;
  }
}