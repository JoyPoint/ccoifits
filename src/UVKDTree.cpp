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
#include <iostream>

using namespace std;

namespace ccoifits
{

void UVTree::AssignIndicies()
{
	unsigned int id = 0;
	AssignIndicies(this->root, id);
}

void UVTree::AssignIndicies(node_ptr & node, unsigned int & node_index)
{
	node->index = node_index;
	node_index += 1;

	if(node->left_child != NULL)
		AssignIndicies(node->left_child, node_index);

	if(node->right_child != NULL)
		AssignIndicies(node->right_child, node_index);
}

/// Builds a KD tree of UVPoints from data
void UVTree::BuildTree(const OIDataList & data)
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

	sort(uv_points.begin(), uv_points.end(), uv_sort_u);

	cout << "Creating tree with " << uv_points.size() << " UV points." << endl;

	// Now build the tree
	// NOTE: Because of how the building algorithim works, the start and
	// end points must be the true starting and ending points of the vector.
	// Normally end points to an element one beyond the end of the vector
	// so we simply decrement end before passing it in.
	this->root = uv_tree(uv_points.begin(), uv_points.end());
}

/// \brief Compares two UV points
///
/// This function assumes the UV coordinates are in spatial frequency (i.e. ~1E6) so that
/// adjacent spectral channels are (probably) clearly separated.
bool UVTree::compare_uv(const uv_point & uv1, const uv_point & uv2)
{

	// Because every point is conjugated into the +u half-plane, we can compare
	// points using a thresholded comparison:
	double du = fabs(uv1.first - uv2.first);
	double dv = fabs(uv1.second - uv2.second);

	if(du < 1 && dv < 1)
		return true;

	return false;
}

node_ptr UVTree::FindUV(uv_point uv)
{
	return FindUV(uv, this->root);
}

node_ptr UVTree::FindUV(uv_point uv, bool insert_on_fail)
{
	node_ptr node = FindUV(uv, this->root);

	if(node == NULL && insert_on_fail)
		node = Insert(uv);

	return node;
}

/// Attempts to find uv_point in the tree.
/// If no node is found and insert_on_fail is false, the function will return an empty node_ptr;
/// If no node is found and insert_on_fail is true, a new node for uv will be created and returned.
node_ptr UVTree::FindUV(uv_point uv, node_ptr & node)
{
	// We enforce that the tree has all positive uv.first values, conjugate if necessary.
	if(uv.first < 0)
	{
		uv.first *= -1;
		uv.second *= -1;
	}

	// If we hit an unpopulated leaf, return this node
	if(node == NULL)
		return node;

	// Compare the node with the UV point
	if(compare_uv(uv, node->uv))
		return node;

	if(less_than(uv, node))
		return FindUV(uv, node->left_child);

	return FindUV(uv, node->right_child);
}

vector<pair<double,double> > UVTree::Flatten()
{
	vector<pair<double,double> > output;
	Flatten(this->root, output);
	return output;
}

vector<pair<double, double>> UVTree::Flatten(node_ptr & node, vector<pair<double,double>> & output)
{
	output.push_back(node->uv);

	if(node->left_child != NULL)
		Flatten(node->left_child, output);

	if(node->right_child != NULL)
		Flatten(node->right_child, output);

	return output;
}

/// Inserts the point uv into the tree.
/// NOTE: This is intended to be used only after a tree already exists.
node_ptr UVTree::Insert(uv_point & uv)
{
	// Flip into the +u half-plane
	if(uv.first < 0)
	{
		uv.first *= -1;
		uv.second *= -1;
	}

//	cout << " Inserting: " << std::setprecision(0) << uv.first << ", " << uv.second << endl;

	return Insert(uv, this->root);
}

/// Inserts the point uv into a subtree starting at node
/// NOTE: This is intended to be used only after a tree already exists.
node_ptr UVTree::Insert(const uv_point & uv, node_ptr & node)
{
	if(node == NULL)
	{
		node.reset(new uv_node());
		node->uv = uv;
		return node;
	}

	bool go_left = less_than(uv, node);

	if(go_left)
		return Insert(uv, node->left_child);
	else
		return Insert(uv, node->right_child);

}

bool UVTree::less_than(const uv_point & uv, const node_ptr & node)
{
	return uv.first < node->uv.first;
}

unsigned int UVTree::size()
{
	return size(this->root);
}

unsigned int UVTree::size(const node_ptr & node)
{
	// Count the current node.
	int n_nodes = 1;

	if(node->left_child != NULL)
		n_nodes += size(node->left_child);

	if(node->right_child != NULL)
		n_nodes += size(node->right_child);

	return n_nodes;
}

bool UVTree::uv_sort_u(const uv_point &a, const uv_point &b)
{
	return a.first < b.first;
}

node_ptr UVTree::uv_tree(vector<uv_point>::iterator start, vector<uv_point>::iterator end)
{
	// Create a  new node
	node_ptr node(new uv_node());
	unsigned int size = distance(start, end);
	auto mid = start + size/2;

	// assign the current UV point
	node->uv = *(mid);

	// calculate the left and and right nodes from the midpoint
	auto left = mid - 1;
	auto right = mid + 1;

	// strip repeated nodes. This shouldn't happen when opening
	// OIFITS files directly, but can happen in bootstrapped data sets.
	while(left >= start && compare_uv(*(left), *(mid)))
	{
		left--;
	}

	while(right <= end && compare_uv(*(right), *(mid)))
	{
		right++;
	}

	// Add children. If the node is at an endpoint, the
	// child should be an empty (null) node_ptr
	if(left >= start)
		node->left_child = uv_tree(start, left);
	else
		node->left_child = node_ptr();

	if(right <= end)
		node->right_child = uv_tree(right, end);
	else
		node->right_child = node_ptr();

	// return this node.
	return node;
}

} /* namespace ccoifits */
