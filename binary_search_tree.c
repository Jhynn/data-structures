#include <stdio.h>
#include <stdlib.h>

struct element {
    int code;
    float value;
    struct element* left;
    struct element* right;
};

typedef struct element element;

struct tree {
    element* root;
};

typedef struct tree tree;

element*
new_element(int code, float value) {
    element* tmp = malloc(sizeof(element));
    tmp->code  = code;
    tmp->left  = NULL;
    tmp->right = NULL;
    tmp->value = value;

    return tmp;
}

void
print_element(element* user_element) {
    if (user_element != NULL) {
        printf("Code: %d, value: %g\n", 
            user_element->code, user_element->value);
    } else {
        printf("This element don't exist!\n");
    }
}

void
initialize(tree* tree) {
    tree->root = NULL;
}

int
size(element* root) {
    if (root == NULL)
        return 0;
	return size(root->left) + 1 + size(root->right);
}

void
insert(tree* tree, element* member) {
    if (tree->root == NULL)
        tree->root = member;
    else {
        element* aux = malloc(sizeof(element));
        aux = tree->root;

        while (aux) {
            if (aux->value == member->value) {
                printf("Element already in this tree.\n");
                return;
            } else if (aux->value > member->value) {
                if (aux->left == NULL) {
                    aux->left = member;
                    break;
                } else                
                    aux = aux->left;
            } else {
                if (aux->right == NULL) {
                    aux->right = member;
                    break;
                } else
                    aux = aux->right;
            }
        }
    }
}

void
show(element* node) {
    if (node != NULL) {
        print_element(node);
        show(node->left);
        show(node->right);
    }
}

element*
search_antecessor(tree* tree, float value) {
    if (!tree->root) {
        return NULL;
    } else if (tree->root->value == value) {
        return tree->root;
    } else {
        element* aux = malloc(sizeof(element));
        aux = tree->root;

        while (1) {
            if (value < aux->value) {
                if (aux->left == NULL)
                    return NULL;
                else if (aux->left->value == value)
                    return aux;
                aux = aux->left;
            } else {
                if (aux->right == NULL)
                    return NULL;
                else if (aux->right->value == value)
                    return aux;
                aux = aux->right;
            }
        }
    }
    return NULL;
}

element*
search(tree* tree, float value) {
    if (tree->root == NULL) {
        return NULL;
    } else if (tree->root->value == value)
        return tree->root;

    element* tmp = malloc(sizeof(element));
    tmp = search_antecessor(tree, value);

    if (tmp != NULL) {
        if (value < tmp->value)
            return tmp->left;
        return tmp->right;
    }
    return NULL;
}

void
delete(tree* tree, float value) {
    if (tree->root == NULL) {
        print_element(tree->root);
        return;
    } else if (tree->root->value == value) {
        if (size(tree->root) == 1) {
            free(tree->root);
            tree->root = NULL;
            return;
        }
        printf("You may not remove the root!\n");
        return;
    }

    element* aux = malloc(sizeof(element));
    element* tmp = malloc(sizeof(element));
    aux = search_antecessor(tree, value);

    if (aux == NULL) {
        print_element(aux);
        return;
    }
    if (value < aux->value) {
        tmp = aux->left;
        if (tmp->left == NULL && tmp->right == NULL) {
            free(tmp);
            tmp = NULL;
            aux->left = NULL;
            return;
            // That was the case the element that will be removed is a leaf.
        } else if (tmp->left != NULL && tmp->right == NULL) {
            aux->left = tmp->left;
            free(tmp);
            tmp = NULL;
            return;
            // That was the case of the element that will be removed 
            // when it has only one successor.
        }  else if (tmp->left == NULL && tmp->right != NULL) {
            aux->left = tmp->right;
            free(tmp);
            tmp = NULL;
            return;
            // That was the case of the element that will be removed 
            // when it has only one successor.
        } else {
            element* tmpr = malloc(sizeof(element));
            tmpr = tmp->left;

            if (tmpr->right == NULL) {
                aux = tmpr;
                free(tmp);
                tmp  = NULL;
                tmpr = NULL;
                return;
            }

            while (tmpr->right->right != NULL)
                tmpr = tmpr->right;

            aux->left   = tmpr->right;
            tmpr->right = tmp->right->left;

            aux->left->left   = tmp->left;
            aux->left->right  = tmp->right;
            
            free(tmp);
            tmp  = NULL;
            tmpr = NULL;
            // That was the case of the element that will be removed
            // when it has two successors.
        }
    } else {
        tmp = aux->right;
        if (tmp->left == NULL && tmp->right == NULL) {
            free(tmp);
            tmp = NULL;
            aux->right = NULL;
            return;
            // That was the case the element that will be removed is a leaf.
        } else if (tmp->left != NULL && tmp->right == NULL) {
            aux->right = tmp->left;
            free(tmp);
            tmp = NULL;
            return;
            // That was the case of the element that will be removed 
            // when it has only one successor.
        }  else if (tmp->left == NULL && tmp->right != NULL) {
            aux->right = tmp->right;
            free(tmp);
            tmp = NULL;
            return;
            // That was the case of the element that will be removed 
            // when it has only one successor.
        } else {
            element* tmpr = malloc(sizeof(element));
            tmpr = tmp->right;

            if (tmpr->left == NULL) {
                aux = tmpr;
                free(tmp);
                tmp  = NULL;
                tmpr = NULL;
                return;
            }

            while (tmpr->left->left != NULL)
                tmpr = tmpr->left;

            aux->right = tmpr->left;
            tmpr->left = tmp->left->right;

            aux->right->right = tmp->right;
            aux->right->left  = tmp->left;
            
            free(tmp);
            tmp  = NULL;
            tmpr = NULL;
            // That was the case of the element that will be removed
            // when it has two successors.
        }
    }
}

int
main(void) {
    int choice, code = 0;
    float number;

    tree bst;
    initialize(&bst);

    do {
        printf("\t\tBinary Search Tree\n\t1. Insert"
                "\t2. Display\t3. Search\n"
                "\t4. Remove\t0. Exit\n");
        printf("\nEnter Choice 0─4: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                continue;
            case 1:
                printf("\nPlease, enter a number: ");
                scanf("%f", &number);
                insert(&bst, new_element(code++, number));
                printf("\n");
                break;
            case 2:
                printf("\nSize: %d\n", size(bst.root));
                show(bst.root);
                printf("\n");
                break;
            case 3:
                printf("Please, type a number to be searched: ");
                scanf("%f", &number);
                print_element(search(&bst, number));
                printf("\n");
                break;
            case 4:
                printf("Please, enter the value: ");
                scanf("%f", &number);
                delete(&bst, number);
                printf("\n");
                break;
            default:
                printf("Invalid choice, please try again.\n\n");
        }
    } while (choice != 0);
    printf("Thank you!\n");
}
