/*
 Name: Marlon Alejandro
 NSHE: 5002573038
 Description: Building Binary Tree and Determine Optimal Pathing
 Input: Series of Characters
 Output: Optimal Path
*/
#include "binTree.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std; 

binTree::binTree(){
    root=NULL; 
} 

binTree::~binTree(){
    deallocateTree(root); 
}

void binTree::deallocateTree(binTreeNode* r){
    if(r == NULL){  // check if node exists
        return;
    }  
    
    deallocateTree(r->left);    // deallocate left
    deallocateTree(r->right);   // deallocate right

    delete r;                   // delete node
}

void binTree::buildTree(std::vector<std::string> locations){
    if(locations.empty()){  // check if nodes exists
        return; 
    }

    root= buildTree(new binTreeNode(), locations, 0); // build tree starting from initial root
}

binTreeNode* binTree::buildTree(binTreeNode * r, std::vector<std::string> locations, int index){
    if(index >= locations.size() || locations[index]=="_"){
        // if index is OOB or contains "_", whcih signifies empty, deallocate node
        deallocateTree(r);    
        return NULL; 
    } 

    r->location = locations[index]; // set current node as the root
    r->left=buildTree(new binTreeNode(), locations, index*2+1); // add node to the left of the root
    r->right=buildTree(new binTreeNode(), locations, (index+1)*2);  // add note to the right of the root

    return r;   
}

std::vector<std::string> binTree::zigzag(){

    std::vector<std::string> leftPath, rightPath;

    if(root == NULL){   //check if tree exist 
        return {};      //return empty vector if tree
    }
    
    leftPath = zigzag(root->left, true, {root->location,root->left->location});    // check left side of tree
    rightPath = zigzag(root->right, false, {root->location,root->right->location}); // check left side of tree

    if(rightPath.size() > leftPath.size()){ // return largest zigzag
        return rightPath; 
    }else{
        return leftPath; 
    }
}

std::vector<std::string> binTree::zigzag(binTreeNode *r, bool childType, std::vector<std::string> path){

    std::vector<std::string> leftPath,rightPath;	
    leftPath=rightPath=path;    //Set left and right equal to current zigzag path
    
    if(r == NULL){  // check if current node is empty
        return {};  // return empty vector other wise
    }

	if(childType==true){    // if left node
		if(r->left != nullptr){ // continue searching left for possible pathways
			leftPath= zigzag(r->left,true,{r->location,r->left->location});	//reset zigzag pathway
		}

		if(r->right != nullptr){    // check right
			path.push_back(r->right->location);	//Add right node to current zigzag path
			rightPath= zigzag(r->right,false,path);// continue search
            path.pop_back();        // revert back to search other direction
		}
	}

	if(childType==false){   //if right node
		if(r->left != nullptr){	//check left
			path.push_back(r->left->location);		//add left node to current zigzag path
			leftPath= zigzag(r->left,true,path);	//continue search
		}

		if(r->right != nullptr){ // continue searching right for possible pathways
			rightPath= zigzag(r->right,false,{r->location,r->right->location});	//reset zigzag pathway

		}
	}
	
    if(leftPath.size() > rightPath.size()){ // return largest zigzag
        return leftPath;
    }else{
        return rightPath;
    }
}