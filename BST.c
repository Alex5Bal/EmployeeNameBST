#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

/* Structure for BST string node */
typedef struct treeNode {
    char *employeeName;
    struct treeNode *left;
    struct treeNode *right;

}treeNode;

treeNode* FindMin(treeNode *node) {
    /* Tree is empty */
    if(node == NULL) {
        return NULL;
    }
    
    /* If left child exists, go to left sub tree to find min */
    if(node->left) 
        return FindMin(node->left);
    
    else 
        return node;
}

bool Search(treeNode* node, char *employeeName) {
	if(node == NULL) return false;
	else if(node->employeeName == employeeName) return true;
	else if(employeeName <= node->employeeName) return Search(node->left, employeeName);
	else return Search(node->right, employeeName);
}

treeNode* Insert(treeNode *node, char *employeeName) {
    if(node == NULL) { /* Empty node found; Set node to employeeName; Add empty left and right children nodes to new parent */
        treeNode * temp;
        temp = (treeNode *)malloc(sizeof(treeNode));
        temp -> employeeName = employeeName;
        temp -> left = temp -> right = NULL;
        return temp;
    }
    
    /* Recursive call on left sub tree */
    if(employeeName <= node->employeeName) { 
        node->left = Insert(node->left, employeeName);
    }
    
    /* Recursive call on right sub tree */
    else { 
        node->right = Insert(node->right, employeeName);
    }
        
    return node;

}

treeNode* Delete(treeNode *node, char *employeeName) {
    treeNode *temp;
    
    /* No such employee name found */
    if(node == NULL) { 
        printf("Element Not Found\n");
    }
    
    /* Recursive call on left sub tree */
    else if(employeeName < node->employeeName) { 
        node->left = Delete(node->left, employeeName);
    }
        
    /* Recursive call on right sub tree */
    else if(employeeName > node->employeeName) { 
        node->right = Delete(node->right, employeeName);
    }
        
    else { /* Found employee name to be deleted */
        /* Current node has left and right children */
        if(node->right && node->left) { 
            /* Replace with minimum element in the right sub tree */
            temp = FindMin(node->right);
            node->employeeName = temp->employeeName; 
            /* Delete node */
            node->right = Delete(node->right, temp->employeeName);
        }
                
        else {
            /* A node with one or zero children can be directly 
            removed from the tree by swapping it with a child node, 
            then deleting the former parent node */
            temp = node;
            
            if(node->left == NULL) {
                node = node->right;
                free(temp);
            }
                        
            else if(node->right == NULL) {
                node = node->left;
                free(temp); 
            }
        }
    }
    return node;

}

void PrintTree(treeNode *node) {
    if(node == NULL) {
        return;
    }
        
    PrintTree(node->left);
    printf("%s\n",node->employeeName);
    PrintTree(node->right);
}

int main() {

    treeNode *root = NULL;
    root = Insert(root, "Alex Balderrama");
    root = Insert(root, "Joe Rojas");
    root = Insert(root, "Phil Larson");
    root = Insert(root, "Jordan Cisneros");
    root = Insert(root, "Benny More");
	
    PrintTree(root);
    printf("\n");
    
    root = Delete(root, "Phil Larson");
    root = Delete(root, "Joe Rojas");
    root = Insert(root, "Matt Williams");
    
    PrintTree(root);
    printf("\n");
    
	/* 
    bool located = Search(root, "Ryan");
    printf("%s\n", located ? "true" : "false");
    */

	/*
	treeNode *root = NULL;
	char userInput;
	
	printf("\nEnter 'R' to run the Personal Management System('E' to exit program): ");
	scanf("%c", &userInput);
	
	while(userInput != 'R' && userInput != 'E') {
		printf("\nInput not recognized\n");
		printf("R - Run Program\n");
		printf("E - Exit program: ");
		scanf(" %c", &userInput);
		
	}
	
	if(userInput == 'E') exit(0);
	
	while(userInput == 'R') {
		char userInput2;
		
		printf("\n\t-----Menu-----\n");
		printf("A - Add new employee\n");
		printf("O - Remove employee\n");
		printf("L - List employees\n");
		printf("E - Exit program: ");
		scanf(" %c", &userInput2);
		
		while(userInput2 != 'A' && userInput2 != 'O' && userInput2 != 'L' && userInput2 != 'E') {
			printf("\nInput not recognized\n");
			printf("\t-----Menu-----\n");
			printf("A - Add new employee\n");
			printf("O - Remove employee\n");
			printf("L - List employees\n");
			printf("E - Exit program: ");
			scanf(" %c", &userInput2);
		}
		
		if(userInput2 == 'E') exit(0);
	
		
		if(userInput2 == 'A') {
			char userInput3;
			char fileName[30];
			char employeeName2[30];
			
			printf("\nChoose method to add employees\n");
			printf("F - Add text file\n");
			printf("T - Type employee name: ");
			scanf(" %c", &userInput3);
			
			while(userInput3 != 'F' && userInput3 != 'T') {
				printf("\nInput not recognized\n");
				printf("Choose method to add employees\n");
				printf("F - Add text file\n");
				printf("T - Type employee name: ");
				scanf("\n%c", &userInput3);
			}
			
			if(userInput3 == 'F') {
				printf("\nEnter file name: ");
				scanf(" %s", fileName);
				//Function to add names from given fileName 
			}
			
			while(userInput3 == 'T') {
				printf("\nEnter employee name: ");
				scanf(" %[^\n]%*c", employeeName2);
				
				// Function to add name to BST
				root = Insert(root, employeeName2);
				
				printf("\nWould you like to insert another name: \n");
				printf("T - Insert another name\n");
				printf("Any other key - Menu: ");
				scanf(" %c", &userInput3);
				
			}
			
		}
		
		while(userInput2 == 'O') {
			char removeName[30];
			
			printf("\nEnter name to remove: ");
			scanf(" %[^\n]%*c", removeName);
			
			// Function to remove name from BST 
			root = Delete(root, removeName);
			
			printf("\nWould you like to delete another name?\n");
			printf("O - Delete another name\n");
			printf("Any other key - Menu: ");
			scanf(" %c", &userInput2);
		}
		
		if(userInput2 == 'L') {
			printf("\n\t-----Employee Name List-----\n");
			
			// Function to print list of employees from BST 
			PrintTree(root);
    		printf("\n");
			
		}
	}
	*/
	
}
