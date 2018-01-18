/* === INTROPROG ABGABE ===
 * Blatt 6, Aufgabe 2
 * Tutorium: t21
 * Gruppe: g07
 * Gruppenmitglieder:
 *  - Jannik Novak
 *  - Ashkan Ardeshirdavani
 * ========================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "introprog_telefonbuch.h"

void bst_insert_node(bstree *bst, unsigned long phone, char *name) {
	int len = strlen(name) + 1;
	bst_node *check = find_node(bst, phone);
	if(check != NULL) {
		printf("Fehler: Telefonnummer entspricht nicht den Vorgaben oder Telefonnummer bereits vorhanden\n");
		return; }
	
	char *newname = (char*)malloc(len * sizeof(char));
	snprintf(newname, len, "%s", name);
	bst_node *new_elem = (bst_node*)malloc(sizeof(bst_node));
	if(bst -> root == NULL) {
		new_elem -> phone = phone;
		new_elem -> name = newname;
		new_elem -> parent = NULL;
		new_elem -> left = NULL;
		new_elem -> right = NULL;
		bst -> root = new_elem; }				
	else {
		bst_node *next = bst -> root;					
		bst_node *prev = NULL;						
		while(next != NULL) {
			if(next -> phone < phone) {
				prev = next;						
				next = next -> right; }
			else {
				prev = next;
				next = next -> left; }
		}	
		if(prev -> phone < phone) {
			new_elem -> phone = phone;
			new_elem -> name = newname;
			new_elem -> parent = prev;
			new_elem -> left = NULL;
			new_elem -> right = NULL;
			prev -> right = new_elem; }
		else {
			new_elem -> phone = phone;
			new_elem -> name = newname;
			new_elem -> parent = prev;
			new_elem -> left = NULL;
			new_elem -> right = NULL;
			prev -> left = new_elem; }
	}
}

bst_node* find_node(bstree* bst, unsigned long phone) {	
	if(phone < 1 || phone > 10000) {
		return NULL; }

	bst_node *temp = bst -> root;
	while(temp != NULL) {
		if(phone == temp -> phone) {
			return temp; }
		else if(phone <= temp -> phone) {
			temp = temp -> left; }
		else {
			temp = temp -> right; }
	}
	return NULL;
}

void bst_in_order_walk_node(bst_node* node) {
	if(node != NULL) {
		bst_in_order_walk_node(node -> left);
		print_node(node);
		bst_in_order_walk_node(node -> right);
	}
}

void bst_in_order_walk(bstree* bst) {
	if (bst != NULL) {
		bst_in_order_walk_node(bst -> root);
	}
}

void bst_free_subtree(bst_node* node) {
	if (node != NULL) {
		bst_free_subtree(node -> left);
		bst_free_subtree(node -> right);
		free(node -> name);
		free(node); }
}

void bst_free_tree(bstree* bst) {
	if(bst != NULL && bst->root != NULL) {
        	bst_free_subtree(bst->root);
		bst->root = NULL;
	}
}

