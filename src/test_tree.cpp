#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;
using std::vector;
using std::pair;

typedef pair<string,int> leaves;

int test_tree(){
	vector<vector<leaves> > tree;

	vector<leaves> level_0;
	vector<leaves> level_1;
	vector<leaves> level_2;

	leaves tree_node_1("tcp://10.11.1.208:6000",1);
	level_0.push_back(tree_node_1);

	leaves tree_node_2("tcp://10.11.1.204:6000",1);
	leaves tree_node_3("tcp://10.11.1.205:6000",0);
	level_1.push_back(tree_node_2);
	level_1.push_back(tree_node_3);

	leaves tree_node_4("tcp://10.11.1.206:6000",0);
	leaves tree_node_5("tcp://10.11.1.207:6000",0);
	level_2.push_back(tree_node_4);
	level_2.push_back(tree_node_5);

	tree.push_back(level_0);
	tree.push_back(level_1);
	tree.push_back(level_2);
	while(1){
		cout<<"you can choose a level: "<<endl;
		int level;
		cin>>level;
		cout<<"the level has the nodes: "<<endl;
		for(unsigned i=0;i<tree[level].size();i++){
			cout<<"leaves: ";
			cout<<tree[level][i].first<<endl;
		}

		cout<<"you can choose a node: "<<endl;
		int node;
		cin>>node;
		cout<<"the node is: ";
		if(tree[level][node].second==1)
			cout<<"master ";
		else
			cout<<"slave ";
		cout<<tree[level][node].first<<endl;

		cout<<"you must connect the following nodes: "<<endl;
		for(unsigned i=0;i<tree[level-1].size();i++){
			if(tree[level-1][i].second==1)
				cout<<tree[level-1][i].first<<endl;
		}
		if(tree[level][node].second==1){
			for(unsigned i=0;i<tree[level+1].size();i++){
				cout<<tree[level+1][i].first<<endl;
			}
		}
	}

	return 0;
}

