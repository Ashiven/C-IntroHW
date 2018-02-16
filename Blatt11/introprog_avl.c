/* === INTROPROG ABGABE ===
 * Blatt 11, Aufgabe 2
 * Tutorium: t21
 * Gruppe: g07
 * Gruppenmitglieder:
 *  - Ashkan Ardeshirdavani
 *  - Jannik Novak
 * ========================
 */
#include <stdlib.h>		
#include <stdio.h>		//Ein- / Ausgabe
#include <math.h>		//Für die Berechnungen der Ausgabe
#include "avl.h"


AVLNode* find_node(AVLTree* avlt, int value) 
{	
	AVLNode *temp = avlt -> root;
	while(temp != NULL) 
	{
		if(value == temp -> value) 
		{
			return temp; 
		}
		else if(value < temp -> value) 
		{
			temp = temp -> left; 
		}
		else {
			temp = temp -> right; 
		}
	}
	return NULL;
}

int heightcheck(AVLNode *node) {
	if(node == NULL) {
		return 0;
	}
	else {
		return node -> height;
	}
}

void AVL_in_order_walk_node(AVLNode* node) 
{
	if(node -> left != NULL) {
		AVL_in_order_walk_node(node -> left);
	}
	printf("%d ", node -> value);
	if(node -> right != NULL) {
		AVL_in_order_walk_node(node -> right);
	}
}

void AVL_in_order_walk(AVLTree* avlt) 
{
	if (avlt != NULL && avlt -> root != NULL) {
		AVL_in_order_walk_node(avlt -> root);
	}
}

void AVL_rotate_left(AVLTree* avlt, AVLNode* x)
{
	AVLNode *y = x -> right;
	x -> right = y -> left;
	
	if(y -> left != NULL) {
		y -> left -> parent = x;
	}
	y -> parent = x -> parent;
	if(x -> parent == NULL) {
		avlt -> root = y;
	}
	else if(x == x -> parent -> left) {
		x -> parent -> left = y;
	}
	else {
		x -> parent -> right = y;
	}
	y -> left = x;
	x -> parent = y;
	if(x -> left == NULL && x -> right == NULL) {
			x -> height = 1;
	}
	else {
		int L, R;
		L = heightcheck(x -> left);
		R = heightcheck(x -> right);
		if(L > R) {
			x -> height = L + 1;
		}
		else {
			x -> height = R + 1;
		}
	}
	if(y -> left == NULL && y -> right == NULL) {
			y -> height = 1;
	}
	else {
		int L, R;
		L = heightcheck(y -> left);
		R = heightcheck(y -> right);
		if(L > R) {
			y -> height = L + 1;
		}
		else {
			y -> height = R + 1;
		}
	}
}

void AVL_rotate_right(AVLTree* avlt, AVLNode* y)
{
	AVLNode *x = y -> left;
	y -> left = x -> right;
	
	if(x -> right != NULL) {
		x -> right -> parent = y;
	}
	x -> parent = y -> parent;
	if(y -> parent == NULL) {
		avlt -> root = x;
	}
	else if(y == y -> parent -> right) {
		y -> parent -> right = x;
	}
	else {
		y -> parent -> left = x;
	}
	x -> right = y;
	y -> parent = x;
	if(y -> left == NULL && y -> right == NULL) {
			y -> height = 1;
	}
	else {
		int L, R;
		L = heightcheck(y -> left);
		R = heightcheck(y -> right);
		if(L > R) {
			y -> height = L + 1;
		}
		else {
			y -> height = R + 1;
		}
	}
	if(x -> left == NULL && x -> right == NULL) {
			x -> height = 1;
	}
	else {
		int L, R;
		L = heightcheck(x -> left);
		R = heightcheck(x -> right);
		if(L > R) {
			x -> height = L + 1;
		}
		else {
			x -> height = R + 1;
		}
	}
}


void AVL_balance(AVLTree* avlt, AVLNode* node)
{
	if(node == NULL) {
		return;
	}
	int L, R;
	L = heightcheck(node -> left);
	R = heightcheck(node -> right);
	if(L > R + 1) {
		int LL, LR;
		LL = heightcheck(node -> left -> left);
		LR = heightcheck(node -> left -> right);
		if(LL < LR) {
			AVL_rotate_left(avlt, node -> left);
		}
		AVL_rotate_right(avlt, node);
	}
	else if(R > L + 1) {
		int RR, RL;
		RR = heightcheck(node -> right -> right);
		RL = heightcheck(node -> right -> left);
		if(RR < RL) {
			AVL_rotate_right(avlt, node -> right);
		}
		AVL_rotate_left(avlt, node);
	}
}

void AVL_insert_value(AVLTree* avlt, int value)
{
	AVLNode *check = find_node(avlt, value);
	if(check != NULL) {
		printf("Der Wert ist bereits vorhanden!\n");
		return;
	}
	AVLNode *newnode = (AVLNode*)malloc(sizeof(AVLNode));
	newnode -> left = NULL;
	newnode -> right = NULL;
	newnode -> parent = NULL;
	newnode -> value = value;
	newnode -> height = 1;

	if(avlt -> root == NULL) {
		avlt -> root = newnode;
		avlt -> numberOfNodes = avlt -> numberOfNodes + 1;
	}
	else {
		AVLNode *current = avlt -> root;
		AVLNode *prev;
		while(current != NULL) {
			prev = current;
			if(current -> value < value) {
				current = current -> right;
			}
			else {
				current = current -> left;
			}
		}
		if(prev -> value < value) {
			prev -> right = newnode;
			newnode -> parent = prev;
			avlt -> numberOfNodes = avlt -> numberOfNodes + 1;
		}
		else {
			prev -> left = newnode;
			newnode -> parent = prev;
			avlt -> numberOfNodes = avlt -> numberOfNodes + 1;
		}
	}
	//balance after node inserted
	AVLNode *temp = newnode;
	while(temp != NULL) {
		AVL_balance(avlt, temp);
		if(temp -> parent != NULL) {
			if(temp -> parent -> left == NULL && temp -> parent -> right == NULL) {
				temp -> parent -> height = 1;
			}
			else {
				int L, R;
				L = heightcheck(temp -> parent -> left);
				R = heightcheck(temp -> parent -> right);
				if(L > R) {
					temp -> parent -> height = L + 1;
				}
				else {
					temp -> parent -> height = R + 1;
				}
			}
		}
		temp = temp -> parent;
	}
}

void AVL_remove_all_nodes(AVLNode *node) {
	if(node -> left != NULL) {
		AVL_remove_all_nodes(node -> left);
	}
	if(node -> right != NULL) {
		AVL_remove_all_nodes(node -> right);
	}
	free(node);
}

void AVL_remove_all_elements(AVLTree* avlt)
{
	if(avlt != NULL) {
		AVL_remove_all_nodes(avlt -> root);
	}
	else {
		free(avlt);
	}
}

