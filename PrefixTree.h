#pragma once
#include "IPAddress.h"

class PrefixTree
{
public:
	PrefixTree();
	IPAddress* getValueAt(int address, int mask);
	void setValueAt(int address, int mask, IPAddress* value);
private:
	class TreeNode {
	public:
		TreeNode();
		TreeNode(IPAddress* value);
		bool isBranched();
		void setBranched();
		IPAddress* getValue();
		void setValue(IPAddress* newValue);
		TreeNode* branch(bool branch);
	private:
		IPAddress* value;
		TreeNode* noBranch;
		TreeNode* yesBranch;
		bool branched;
	};
	TreeNode* root;
	TreeNode* getNodeAt(int address, int mask);
};
