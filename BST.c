#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct treeNode {
    char *employeeName;
    struct treeNode *left;
    struct treeNode *right;

}treeNode;

treeNode* FindMin(treeNode *node) {
    if(node == NULL) {
        /* There is no element in the tree */
        return NULL;
    }
    
    if(node->left) /* Go to the left sub tree to find the min element */
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
    if(node == NULL) {
        treeNode * temp;
        temp = (treeNode *)malloc(sizeof(treeNode));
        temp -> employeeName = employeeName;
        temp -> left = temp -> right = NULL;
        return temp;
    }
    
    if(employeeName <= node->employeeName) {
        node->left = Insert(node->left, employeeName);
    }
    
    else {
        node->right = Insert(node->right, employeeName);
    }
        
	/* Else there is nothing to do as the data is already in the tree. */
    return node;

}

treeNode* Delete(treeNode *node, char *employeeName) {
    treeNode *temp;
    
    if(node == NULL) {
        printf("Element Not Found\n");
    }
    
    else if(employeeName < node->employeeName) {
        node->left = Delete(node->left, employeeName);
    }
        
    else if(employeeName > node->employeeName) {
        node->right = Delete(node->right, employeeName);
    }
        
    else {
        /* Now We can delete this node and replace with either minimum element 
        in the right sub tree or maximum element in the left subtree */
        if(node->right && node->left) {
            /* Here we will replace with minimum element in the right sub tree */
            temp = FindMin(node->right);
            node -> employeeName = temp->employeeName; 
            /* As we replaced it with some other node, we have to delete that node */
            node -> right = Delete(node->right, temp->employeeName);
        }
                
        else {
            /* If there is only one or zero children then we can directly 
            remove it from the tree and connect its parent to its child */
            temp = node;
            
            if(node->left == NULL) {
                node = node->right;
                free(temp);
            }
                        
            else if(node->right == NULL) {
                node = node->left;
                free(temp); /* temp is no longer required */ 
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

	/*treeNode *root = NULL;
	root = Insert(root, "Alex Balderrama");
	root = Insert(root, "Al");
	root = Insert(root, "Phil");
	root = Insert(root, "Jordan");
	
	PrintTree(root);
    printf("\n");
    
    root = Delete(root, "Lia");
    root = Delete(root, "Phil");
   	bool located = Search(root, "Lexi");
    printf("%s\n", located ? "true" : "false");
    PrintTree(root);
    printf("\n");
    */

	treeNode *root = NULL;
	char userInput;
	
	printf("\nEnter 'R' to run the Personal Management System('E' to exit program): ");
	scanf("%c", &userInput);
	
	while(userInput != 'R' && userInput != 'E') {
		printf("\nInput not recognized\n");
		printf("R - Run Program\n");
		printf("E - Exit program\n");
		scanf("\n%c", &userInput);
		
	}
	
	if(userInput == 'E') exit(0);
	
	while(userInput == 'R') {
		char userInput2;
		
		printf("\n\t-----Menu-----\n");
		printf("A - Add new employee\n");
		printf("O - Remove employee\n");
		printf("L - List employees\n");
		printf("E - Exit program: ");
		scanf("\n%c", &userInput2);
		
		while(userInput2 != 'A' && userInput2 != 'O' && userInput2 != 'L' && userInput != 'E') {
			printf("\nInput not recognized\n");
			printf("\t-----Menu-----\n");
			printf("A - Add new employee\n");
			printf("O - Remove employee\n");
			printf("L - List employees\n");
			printf("E - Exit program\n");
			scanf("%c\n", &userInput2);
		}
		
		if(userInput2 == 'E') {
			exit(0);
		}
		
		while(userInput2 == 'A') {
			char userInput3;
			char fileName[30];
			char employeeName2[30];
			
			printf("\nChoose method to add employees\n");
			printf("F - Add text file\n");
			printf("T - Type employee name: ");
			scanf("\n%c", &userInput3);
			
			while(userInput3 != 'F' && userInput3 != 'T') {
				printf("\nInput not recognized\n");
				printf("Choose method to add employees\n");
				printf("F - Add text file\n");
				printf("T - Type employee name: ");
				scanf("\n%c", &userInput3);
			}
			
			if(userInput3 == 'F') {
				printf("\nEnter file name: ");
				scanf("%s\n", fileName);
				//Function to add names from given fileName
			}
			
			if(userInput3 == 'T') {
				printf("\nEnter employee name: ");
				scanf("\n%s", employeeName2);
				//Function to add name to BST
				root = Insert(root, employeeName2);
				
			}
			
			printf("\nWould you like to insert another name: \n");
			printf("A - Insert another name\n");
			printf("Any other key - Menu: ");
			scanf("\n%c", &userInput2);
		}
		
		if(userInput2 == 'O') {
			char removeName[30];
			
			printf("\nEnter name to remove: ");
			scanf("%s", removeName);
			//Function to remove name from BST
			root = Delete(root, removeName);
			
			printf("\nWould you like to delete another name: \n");
			printf("O - Delete another name\n");
			printf("Any other key - Menu\n");
			scanf("%c\n", &userInput2);
		}
		
		if(userInput2 == 'L') {
			printf("\n\t-----Employee Name List-----\n");
			//Function to list employees from BST
			PrintTree(root);
    		printf("\n");
			
		}
		
		printf("\n\t-----Menu-----\n");
		printf("R - Continue\n");
		printf("E - Exit program: ");
		scanf("\n%c", &userInput);
		
		if(userInput == 'E') {
			exit(0);
		}
	}	
}