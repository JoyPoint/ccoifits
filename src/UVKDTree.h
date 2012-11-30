/*
 * UVKDTree.h
 *
 *  Created on: Nov 16, 2012
 *      Author: bkloppen
 */

#ifndef UVKDTREE_H_
#define UVKDTREE_H_

#include <memory>
#include <vector>

using namespace std;



namespace ccoifits
{

class COIDataRow;
typedef shared_ptr<COIDataRow> OIDataRowPtr;
typedef vector<OIDataRowPtr> OIDataList;

class kd_uv_node;
typedef shared_ptr<kd_uv_node> node_ptr;

// A representation of a UV point.  uv_point.first === u, uv_point.second === v
typedef pair<double,double> uv_point;

class kd_uv_node
{
public:
	unsigned int index;
	uv_point uv;
	node_ptr left_child;
	node_ptr right_child;
};

class UVKDTree
{

protected:
	node_ptr root;

public:
	void AssignIndicies();
protected:
	static void AssignIndicies(node_ptr & node, unsigned int & node_index);
public:
	void BuildTree(const OIDataList & data);

	static bool compare_uv(const uv_point & uv1, const uv_point & uv2);

	vector<pair<double,double> > Flatten();
	static vector<pair<double, double>> Flatten(node_ptr & node, vector<pair<double,double>> & output);

	node_ptr FindUV(uv_point uv);
	node_ptr FindUV(uv_point uv, bool insert_on_fail);
protected:
	node_ptr FindUV(uv_point uv, node_ptr & node, unsigned int depth, bool insert_on_fail);
	node_ptr Insert(uv_point & uv);
	static node_ptr Insert(const uv_point & uv, node_ptr & node, unsigned int depth);

public:
	static bool less_than(const uv_point & uv, const node_ptr & node, unsigned int depth);
	unsigned int size();
	unsigned int size(const node_ptr & node);
	static bool uv_sort_u(const uv_point &a, const uv_point &b);
	static bool uv_sort_v(const uv_point &a, const uv_point &b);

protected:
	static node_ptr uv_tree(vector<uv_point>::iterator start, vector<uv_point>::iterator end, unsigned int depth=0);
};

} /* namespace ccoifits */
#endif /* UVKDTREE_H_ */
