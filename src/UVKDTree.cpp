/*
 * UVKDTree.cpp
 *
 *  Created on: Nov 16, 2012
 *      Author: bkloppen
 */

#include "UVKDTree.h"

#include <cmath>
#include <algorithm>
#include "COIDataRow.h"

using namespace std;

namespace ccoifits
{

/// Builds a KD tree of UVPoints from data
void UVKDTree::BuildTree(const OIDataList & data)
{
	vector<uv_point> uv_points;

	// Iterate over all of the data points, extract the UV coordinates
	for(auto row : data)
	{
		auto wavelengths = row->GetMaskedWavelengths();
		// Generate and push_back scaled UV coordinates
		for(auto wavelength : wavelengths)
		{
			for(auto raw_uv : row->mUV)
			{
				// Get the scaled point.
				auto uv = raw_uv->GetScaledPair(wavelength);

				// Flip into the +u half-plane
				if(uv.first < 0)
				{
					uv.first *= -1;
					uv.second *= -1;
				}
				// Append
				uv_points.push_back(uv);
			}
		}
	}

	// Now build the tree
	this->root = uv_tree(uv_points.begin(), uv_points.end(), 0);
}

bool UVKDTree::compare_uv(const uv_point & uv1, const uv_point & uv2)
{
	double thresh = 1E-5;
	if(fabs(uv1.first - uv2.first) < thresh && fabs(uv1.second - uv2.second) < thresh)
		return true;

	return false;
}

node_ptr UVKDTree::FindUV(const uv_point & uv)
{
	return FindUV(uv, this->root, 0, false);
}

node_ptr UVKDTree::FindUV(const uv_point & uv, bool insert_on_fail)
{
	return FindUV(uv, this->root, 0, insert_on_fail);
}

/// Attempts to find uv_point in the tree.
/// If no node is found and insert_on_fail is false, the function will return an empty node_ptr;
/// If no node is found and insert_on_fail is true, a new node for uv will be created and returned.
node_ptr UVKDTree::FindUV(const uv_point & uv, node_ptr & node, unsigned int depth, bool insert_on_fail)
{
	if(compare_uv(uv, node->uv));
		return node;

	// Switch between comparing u and v depending on the depth:
	bool go_left = less_than(uv, node, depth);

	// only proceed into children nodes if they are not null
	if(node->left_child != NULL && go_left)
		return FindUV(uv, node->left_child, depth + 1, insert_on_fail);
	if(node->right_child != NULL)
		return FindUV(uv, node->right_child, depth + 1, insert_on_fail);

	// If we are instructed to insert upon failure, do so
	if(insert_on_fail)
		return Insert(uv, node, depth);

	// otherwise return a null node_ptr
	return node_ptr();
}

/// Inserts the point uv into the tree.
/// NOTE: This is intended to be used only after a tree already exists.
node_ptr UVKDTree::Insert(uv_point & uv)
{
	// Flip into the +u half-plane
	if(uv.first < 0)
	{
		uv.first *= -1;
		uv.second *= -1;
	}

	Insert(uv, this->root, 0);
}

/// Inserts the point uv into a subtree starting at node
/// NOTE: This is intended to be used only after a tree already exists.
node_ptr UVKDTree::Insert(const uv_point & uv, node_ptr & node, unsigned int depth)
{
	if(node == NULL)
	{
		node.reset(new kd_uv_node());
		node->uv = uv;
		return node;
	}

	bool go_left = less_than(uv, node, depth);

	if(go_left)
		return Insert(uv, node->left_child, depth+1);
	else
		return Insert(uv, node->right_child, depth+1);

}

bool UVKDTree::less_than(const uv_point & uv, const node_ptr & node, unsigned int depth)
{
	int axis = depth / 2;
	if(axis == 0)
		return uv.first < node->uv.first;
	else
		return uv.second < node->uv.second;

	return false;
}

bool UVKDTree::uv_sort_u(const uv_point &a, const uv_point &b)
{
	return a.first < b.first;
}

bool UVKDTree::uv_sort_v(const uv_point &a, const uv_point &b)
{
	return a.second < b.second;
}

node_ptr UVKDTree::uv_tree(vector<uv_point>::iterator start, vector<uv_point>::iterator end, unsigned int depth)
{
	// If there are no points, return an empty node pointer
	unsigned int size = end - start;
	unsigned int median = size / 2;
	if(size == 0)
		return node_ptr();

	// Sort by either u or v, depending on the depth:
	int axis = depth / 2;
	if(axis == 0)
		sort(start, end, uv_sort_u);
	else
		sort(start, end, uv_sort_v);

	// Pick the midpoint.
	auto mid = start + int(size / 2);

	// Create a new node, wrap in a shared_ptr
	node_ptr node(new kd_uv_node());
	node->uv = *(mid);

	// Prune repeated elements from the left list
	auto left = mid - 1;
	while(left != start && compare_uv(*(left), *(mid)));
		left--;

	// Prune repeated elements from the right list
	auto right = mid + 1;
	while(right != end && compare_uv(*(right), *(mid)));
		right++;

	node->left_child = uv_tree(start, left, depth+1);
	node->right_child = uv_tree(right, end, depth+1);

	return node;
}

} /* namespace ccoifits */
