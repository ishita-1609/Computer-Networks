#include <stdio.h>
//#include <tchar.h>
#include <iostream>
#include <stdint.h>
#include "PrefixTree.h"

PrefixTree::PrefixTree()
	: root(new PrefixTree::TreeNode())
{}

IPAddress* PrefixTree::getValueAt(int address, int mask) {
	PrefixTree::TreeNode* node = this->getNodeAt(address, mask);
	if (node) {
		return node->getValue();
	}
	else {
		return nullptr;
	}
}

void PrefixTree::setValueAt(int address, int mask, IPAddress* value)
{
	PrefixTree::TreeNode* curNode = root;
	for (int i = 0; i < mask; i++) {
		uint32_t curMask = 1 << (31 - i);
		if (!curNode->isBranched()) {
			curNode->setBranched();
		}
		bool decision = (address & curMask) >> (31 - i);
		curNode = curNode->branch(decision);
	}
	curNode->setValue(value);
}

PrefixTree::TreeNode* PrefixTree::getNodeAt(int address, int mask)
{
	TreeNode* curBest = nullptr;
	PrefixTree::TreeNode* curNode = this->root;
	for (int i = 0; i < mask; i++) {
		uint32_t curMask = 1 << (31 - i);
		if (curNode->getValue()) {
			curBest = curNode;
		}
		if (curNode->isBranched()) {
			bool decision = (address & curMask) >> (31 - i);
			curNode = curNode->branch(decision);
		}
		else {
			return curBest;
		}
	}
	return nullptr;
}


PrefixTree::TreeNode::TreeNode()
	: value(nullptr), branched(false) {}

PrefixTree::TreeNode::TreeNode(IPAddress* v)
	: value(v), branched(false) {}

IPAddress* PrefixTree::TreeNode::getValue() {
	return this->value;
}

void PrefixTree::TreeNode::setValue(IPAddress* v) {
	this->value = v;
}

bool PrefixTree::TreeNode::isBranched() {
	return this->branched;
}

void PrefixTree::TreeNode::setBranched() {
	// Make this node null and build branches, unless branches already exist.
	if (!branched) {
		this->noBranch = new TreeNode(this->value);
		this->yesBranch = new TreeNode(this->value);
		this->value = nullptr;
		this->branched = true;
	}
}

PrefixTree::TreeNode* PrefixTree::TreeNode::branch(bool branch) {
	if (branch) {
		return this->yesBranch;
	} else {
		return this->noBranch;
	}
}