/*
 * Trees.h
 *
 *  Created on: 2013-9-17
 *      Author: casa
 */

#ifndef TREES_H_
#define TREES_H_

#include <iostream>
using namespace std;

static const int M=2;
static const int KEY_MAX=2*M-1;
static const int KEY_MIN=M-1;
static const int CHILD_MAX=KEY_MAX+1;
static const int CHILD_MIN=KEY_MIN+1;

struct TreeNode{
	//是叶子节点吗
	bool isLeaf;
	//每个节点上key的数量
	int keyNum;
	//key值数组
	int keyValue[KEY_MAX];
	//子树指针数组
	TreeNode *children[CHILD_MAX];

//	TreeNode()
//	:isLeaf(true),keyNum(0){}

	TreeNode(bool b=true,int n=0)
	:isLeaf(b),keyNum(n){}
};

class Trees {
	//树肯定会有
public:
	Trees();
	Trees(TreeNode *node){
		rootNode=node;
	}
	virtual ~Trees();

	bool insert(const int &key){
		if(contain(key)){
			return false;
		}
		else{
			if(rootNode==0){
				rootNode=new TreeNode();
			}
			if(rootNode->keyNum==KEY_MAX){
				cout<<"split"<<endl;
				TreeNode *node=new TreeNode();
				node->isLeaf=false;
				node->children[0]=rootNode;
				splitChild(node,0,rootNode);
				rootNode=node;
			}
			insertNonfull(rootNode,key);
			return true;
		}
	}

	bool remove(const int &key){
		if(!search(rootNode,key))
			return false;
		if(rootNode->keyNum==1){
			if(rootNode->isLeaf){
				return true;
			}
		}
	}

//	void modify(TreeNode *node, int data);
//
//	void PreorderTraverse();
//	void InorderTraverse();
//	void PostorderTraverse();

	void display() const{
		display_1(rootNode,KEY_MAX*10);
	}

private:
	bool contain(const int &key) const{
		return search(rootNode,key);
	}

	void clear(){

		rootNode=0;
	}

	//查找一个key所对应的节点
	bool search(TreeNode *node,const int &key) const{
		if(node==0)//检测节点是否为空
			return false;
		else{
			int i=0;
			for(i=0;i<node->keyNum && key>*(node->keyValue+i);i++){
			}
			if(i<node->keyNum && key==node->keyValue[i]){
				return true;
			}
			else{
				if(node->isLeaf){
					return false;
				}
				else{
					return search(node->children[i],key);
				}
			}
		}
	}

	void insertNonfull(TreeNode *node, const int &key){
		int i=node->keyNum;
		if(node->isLeaf){
			while(i>0 && key<node->keyValue[i-1]){
				node->keyValue[i]=node->keyValue[i-1];
				--i;
			}
			node->keyValue[i]=key;
			++node->keyNum;
		}
		else{
			while(i>0 && key<node->keyValue[i-1])
				--i;
			TreeNode *child=node->children[i];
			if(child->keyNum==KEY_MAX){
				cout<<"split"<<endl;
				splitChild(node,i,child);
				if(key>node->keyValue[i])
					child=node->children[i+1];
			}
			insertNonfull(child,key);
		}
	}

	void splitChild(TreeNode *node,int index,TreeNode *child){
		TreeNode *right=new TreeNode();
		right->isLeaf=child->isLeaf;
		right->keyNum=KEY_MIN;
		int i=0;
		for(i=0;i<KEY_MIN;i++){
			right->keyValue[i]=child->keyValue[i+CHILD_MIN];
		}
		if(!child->isLeaf){
			for(int i=0;i<CHILD_MIN;++i){
				right->children[i]=child->children[i+CHILD_MIN];
			}
		}
		child->keyNum=KEY_MIN;

		for(i=node->keyNum;i>index;--i){
			node->children[i+1]=node->children[i];
			node->keyValue[i]=node->keyValue[i-1];
		}
		++node->keyNum;
		node->children[index+1]=right;
		node->keyValue[index]=child->keyValue[KEY_MIN];
	}

	void display_1(TreeNode *node, int count) const{
		if(node!=0){
			int i,j;
			for(i=0;i<node->keyNum;++i){
				if(!node->isLeaf){
					display_1(node->children[i],count-2);
				}
				for(j=count;j>=0;--j){
					cout<<"-";
				}
				cout<<"++++++++++"<<node->keyValue[i]<<"|"<<endl;
			}
			if(!node->isLeaf){
				display_1(node->children[i],count-2);
			}
		}
	}

private:
	TreeNode *rootNode;
};

#endif /* TREES_H_ */
