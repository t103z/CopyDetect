#include <cstdlib>
#include <iostream>
#include <cassert>

#include "KDTree.h"

using namespace std;

int KDNode::distance2(vector<int> &x)
{
	int S = 0;
	for (int k = 0; k < (int)x.size(); ++k)
		S += (x_[k]-x[k])*(x_[k]-x[k]);
	return S;
}

bool KDNode::equal(vector<int> &x)
{
	for (int k = 0; k < (int)x.size(); k++)
	{
		if (x_[k] != x[k])
			return false;
	}
	return true ;
}

KDNode::KDNode(vector<int> &x0, int axis0)
{
	axis_ = axis0;
	x_ = x0;
	left_ = right_ = parent_ = NULL;
	checked_ = false;
	id_ = 0;
}

KDNode* KDTree::findLeaf(vector<int> &x0, KDNode *node)
{
	KDNode* parent = NULL;
	while (node)
	{
		int split = node->axis_;
		parent = node;
		if (x0[split] > node->x_[split])
			node = node->right_;
		else
			node = node->left_;
	}
	return parent;
}

KDNode* KDTree::insert(vector<int> &p, KDNode *node)
{
	KDNode* parent = findLeaf(p, node);
	if (parent->equal(p))
		return NULL;
	KDNode* newNode = new KDNode(p, parent->axis_+1 < (int)p.size() ? parent->axis_+1 : 0);
	newNode->parent_ = parent;

	if (p[parent->axis_] > parent->x_[parent->axis_])
	{
		parent->right_ = newNode;
	}
	else
	{
		parent->left_ = newNode;
	}

	return newNode;
}

KDTree::KDTree():root_(NULL), KD_id_(0) { }

bool KDTree::add(vector<int> &x)
{
	if (!root_)
	{
		root_ = new KDNode(x, 0);
		root_->id_ = KD_id_++;
		list_.push_back(root_);
	}
	else
	{
		KDNode* pNode = NULL;
		if ((pNode = insert(x, root_)))
		{
			pNode->id_ = KD_id_++ ;
			list_.push_back(pNode);
		}
	}
	return true ;
}

KDNode* KDTree::findNearest(vector<int> &x, vector<KDNode*> &visitedNodes)
{
	if (!root_)
		return NULL ;

	KDNode* leaf = findLeaf(x, root_);
	nearest_neighbour_ = leaf;
	d_min_ = leaf->distance2(x);
	if (leaf->equal(x))
		return nearest_neighbour_;
	searchParent(leaf, x);
    visitedNodes = checkedNodes_;
	uncheck();

	return nearest_neighbour_;
}

void KDTree::checkSubtree(KDNode* node, vector<int> &x)
{
	if (!node || node->checked_)
		return;

	checkedNodes_.push_back(node);
	node->checked_ = true;
	updateMinNode(node, x);
	
	int dim = node->axis_;
	int d = node->x_[dim] - x[dim];

	if (d*d > d_min_)
    {
		if (node->x_[dim] > x[dim])
		  checkSubtree(node->left_, x);
		else
		  checkSubtree(node->right_, x);
	}
	// If the distance from the key to the current value is 
	// less than the nearest distance, we still need to look
	// in both directions.
	else
	{
		checkSubtree(node->left_, x);
		checkSubtree(node->right_, x);
	}
}

KDNode* KDTree::findNearestBrute(vector<int> &x) 
{
	if (!root_)
		return NULL;

	KDNode* nearest = root_;
	int d;
	d_min_ = root_->distance2(x);
	for (int n = 1; n < (int)list_.size(); n++)
	{
		d = list_[n]->distance2(x);
		if (d < d_min_)
		{
			nearest = list_[n];
			d_min_ = d;
		}
	}
	return nearest;
}

void KDTree::updateMinNode(KDNode* node, vector<int> &x)
{
	if (!node)
		return;
	int d = 0;
	for (int k = 0; k < (int)x.size(); ++k)
	{
        int dx = node->x_[k]-x[k];
        dx *= dx;
        d += dx;
        if (d > d_min_)
            return;
    }
    if (d < d_min_)
    {
        d_min_ = d;
        nearest_neighbour_ = node;
    }
}

void KDTree::searchParent(KDNode* parent, vector<int> &x)
{
    while (parent)
    {
        checkSubtree(parent, x);
        parent = parent->parent_;
    }
}

void KDTree::uncheck()
{
    for (int k = 0; k < (int)checkedNodes_.size(); ++k)
        checkedNodes_[k]->checked_ = false;
    checkedNodes_.clear();
}

