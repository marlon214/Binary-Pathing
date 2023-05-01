#include <vector>
#include <string>

struct binTreeNode
{
	std::string location;
	binTreeNode * left;
	binTreeNode * right;
};

class binTree
{	
public:
	binTree();
	~binTree();
	void buildTree(std::vector<std::string>);
	std::vector<std::string> zigzag();
private:
	binTreeNode* buildTree(binTreeNode*, std::vector<std::string>, int);
	std::vector<std::string> zigzag(binTreeNode*, bool, std::vector<std::string>);
	void deallocateTree(binTreeNode*);

	binTreeNode * root;
};