#include "BST.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;
//Brendon Uzoigwe
BST::BST() {
	root = nullptr;
}

BST::BST(string title, string author, int yr, string pub, long long isbn, float rate) {
	BSTNode *roo = new BSTNode(title, author, yr, pub, isbn, rate);
    root = roo;
}

BST::~BST() {
	clearTree();
}

void BST::insert(string title, string author, int yr, string pub, long long isbn, float rate) {
    BSTNode* node = new BSTNode(title, author, yr, pub, isbn, rate);
	if (root == nullptr){
        root = node;
    }
    else{
        BSTNode* curr = root;
        while(curr != nullptr){
            if(*(node->book) < *(curr->book)){
                if(curr->left != nullptr){
                    curr = curr->left;
                }
                else{
                    break;
                }
            }
            else{
                if(curr->right != nullptr){
                    curr = curr->right;

                }
                else{
                    break;
                }
            }
        }
        if(*(node->book) < *(curr->book)){
            curr->left = node;
            node->parent = curr;
        }
        else{
            curr->right = node;
            node->parent = curr;
        }
        setHeight(node);
    }

}

BSTNode *BST::find(string title, string author) {
    return find(title, author, root);
}

BSTNode *BST::find(string title, string author, BSTNode *start) {
    BSTNode *curr = start;
    while(curr != nullptr){
        if (curr->book->title == title && curr->book->author == author){
            return curr;
        }
        if(author < curr->book->author){
            if(curr->left != nullptr){
                curr = curr->left;
            }
            else{
                break;
            }
        }
        else if(author == curr->book->author){
            if(title<curr->book->title){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }
        else{
            if (curr->right != nullptr){
                curr = curr->right;
            }
            else{
                break;
            }
        }
    }
    return nullptr;
    }


void BST::printTreeIO() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl << "Printing In-Order:" << endl;
		printTreeIO(root);
	}
}

void BST::printTreeIO(BSTNode *node) {
	if (node == NULL){
        return;
    }
    printTreeIO(node->left);
    node->printNode(false);
    printTreeIO(node->right);
}

void BST::printTreePre() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl << "Printing Pre-Order:" << endl;
		printTreePre(root);
	}
}

void BST::printTreePre(BSTNode *node) {
    if (node == NULL){
        return;
    }
    node->printNode(false);
    printTreePre(node->left);
    printTreePre(node->right);
}

void BST::printTreePost() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing Post-Order:" <<endl;
		printTreePost(root);
	}
}

void BST::printTreePost(BSTNode *node) {
    if (node == NULL){
        return;
    }
    printTreePost(node->left);
    printTreePost(node->right);
    node->printNode(false);
}

void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}

void BST::clearTree(BSTNode *node) {
	if (node == NULL) {
		return;
	}
	else {
		clearTree(node->left);
		node->left = NULL;
		clearTree(node->right);
		node->right = NULL;
		node->printNode(true);
		delete node;
	}
}

bool BST::checkOut(string title, string author) {
    BSTNode* curr = find(title, author);
    while(curr!= nullptr){
        if(!curr->book->checked_out){
            curr->book->checked_out = true;
            return true;
        }
        curr = find(title, author, curr->right);
    }
	return false;
}

bool BST::checkIn(string title, string author) {
    BSTNode* curr = find(title, author);
    while(curr!= nullptr){
        if(curr->book->checked_out){
            curr->book->checked_out = false;
            return true;
        }
        curr = find(title, author, curr->right);
    }
	return false;
}

void BST::updateRating(string title, string author, float newRating) {
	BSTNode* curr = find(title, author, root);
    while(curr!= nullptr){
        curr->book->rating = newRating;
        curr = find(title, author, curr->right);
    }
}


BSTNode *BST::removeNoKids(BSTNode *node) {
    if(node->parent->left == node){
        node->parent->left = nullptr;
        setHeight(node->parent);
        node->parent = nullptr;
    }
    else{
        node->parent->right = nullptr;
        setHeight(node->parent);
        node->parent = nullptr;
    }
    return node;
}

BSTNode *BST::removeOneKid(BSTNode *node, bool leftFlag) {
    if(node == nullptr){
        return nullptr;
    }
    else if(leftFlag){
            node->parent->left = node->left;
            node->left->parent = node->parent;
            setHeight(node->left->parent);
            node->parent = nullptr;
            node->left = nullptr;
        }
    else{
            node->parent->right = node->right;
            node->right->parent = node->parent;
            setHeight(node->right->parent);
            node->parent = nullptr;
            node->right = nullptr;
        }
    BSTNode* ret = node;
    return ret;
}

BSTNode *BST::remove(string title, string author) {
    BSTNode *rnode = find(title,author);
    if(rnode == nullptr){
        return nullptr;
    }
    BSTNode *dupe = find(title, author, rnode->right);
    if(dupe == root){
        Book *temp = dupe->book;
        dupe->book = root->book;
        root->book = temp;
        if (dupe->left != nullptr) {
            dupe->left->parent = root;
        }
        if (dupe->right != nullptr) {
            dupe->right->parent = root;
        }
        root->left = dupe->left;
        root->right = dupe->right;
        dupe->left = nullptr;
        dupe->right = nullptr;
        dupe->parent = nullptr;
        rnode->left = nullptr;
        rnode->right = nullptr;
        rnode->parent = nullptr;
    }
    else {
        if (rnode == root) {
            if (root->left == nullptr && root->right == nullptr) {
                root = nullptr;

            } else if (root->left != nullptr && root->right == nullptr) {
                root = root->left;
                root->parent->left = nullptr;
                root->parent = nullptr;


            } else if (root->left == nullptr && root->right != nullptr) {
                root = root->right;
                root->parent->right = nullptr;
                root->parent = nullptr;

            } else {
                BSTNode *curr = rnode->right;
                BSTNode *currP = curr->parent;
                while (curr->left != nullptr) {
                    curr = curr->left;
                }
                if (curr->right == nullptr) {
                    curr = removeNoKids(curr);
                    setHeight(currP);
                } else if (curr->right != nullptr) {
                    curr = removeOneKid(curr, false);
                    setHeight(currP);
                }
                curr->right = root->right;
                curr->left = root->left;
                curr->left->parent = curr;

                curr->right->parent = curr;
                root->left = nullptr;
                root->right = nullptr;
                root = curr;
                BSTNode *c = root;
                while (c != nullptr) {
                    if (c->left == nullptr && c->right != nullptr) {
                        c = c->right;
                    } else if (c->left != nullptr && c->right == nullptr) {
                        c = c->left;
                    } else if (c->left == nullptr && c->right == nullptr) {
                        break;
                    } else if (c->left->height > c->right->height) {
                        if (c->left == nullptr) {
                            break;
                        }
                        c = c->left;
                    } else {
                        if (c->right == nullptr) {
                            break;

                        }
                        c = c->right;
                    }
                }
                setHeight(c);
            }
        } else {
            if (rnode->left != nullptr && rnode->right == nullptr) {
                return removeOneKid(rnode, true);

            } else if (rnode->left == nullptr && rnode->right != nullptr) {
                return removeOneKid(rnode, false);

            } else if (rnode->left == nullptr && rnode->right == nullptr) {

                return removeNoKids(rnode);
            } else if (rnode->left != nullptr && rnode->right != nullptr) {
                BSTNode *curr = rnode->right;
                while (curr->left != nullptr) {
                    curr = curr->left;
                }
                if (curr->right == nullptr) {
                    curr = removeNoKids(curr);
                } else if (curr->right != nullptr) {
                    curr = removeOneKid(curr, false);
                }
                curr->right = rnode->right;
                curr->left = rnode->left;
                curr->left->parent = curr;

                if (rnode->right != nullptr) {
                    curr->right->parent = curr;
                }
                curr->parent = rnode->parent;
                if (rnode->parent->right == rnode) {
                    curr->parent->right = curr;

                } else if (rnode->parent->left == rnode) {
                    curr->parent->left = curr;
                }


                rnode->left = nullptr;
                rnode->right = nullptr;
                rnode->parent = nullptr;


                BSTNode *c2 = curr;
                while (c2 != nullptr) {
                    if (c2->left == nullptr && c2->right != nullptr) {
                        c2 = c2->right;
                    } else if (c2->left != nullptr && c2->right == nullptr) {
                        c2 = c2->left;
                    } else if (c2->left == nullptr && c2->right == nullptr) {
                        break;
                    } else if (c2->left->height > c2->right->height) {
                        if (c2->left != nullptr) {
                            c2 = c2->left;
                        }
                        else{
                            break;
                        }

                    } else {
                        if (c2->right != nullptr) {
                            c2 = c2->right;
                        }
                        else{
                            break;
                        }

                    }
                }
                setHeight(c2);


            }

        }
    }

    return rnode;

}

void BST::setHeight(BSTNode *node) {
    BSTNode *curr = node;
    while(curr != nullptr){
        if(curr->right == nullptr && curr->left == nullptr){
            curr->height = 1;
        }
        else if(curr->right != nullptr && curr->left == nullptr){
            curr->height = curr->right->height +1;
        }
        else if(curr->right == nullptr && curr->left != nullptr){
            curr->height = curr->left->height + 1;
        }
        else{
            if(curr->right->height > curr->left->height){
                curr->height = curr->right->height +1;
            }
            else{
                curr->height = curr->left->height + 1;
            }
        }
        curr = curr->parent;
    }
}

