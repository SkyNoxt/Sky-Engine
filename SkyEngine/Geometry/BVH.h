
#pragma once

#include <limits>
#include <vector>

#include <Math/Vector3.h>

#include "Box.h"
#include "IndexedMesh.h"

template <class T>
class BVH
{

public:
	//Constructor
	BVH(const Mesh& mesh);
	BVH(const IndexedMesh& mesh);

	//Member function
	bool intersect(const Mesh& mesh, const Ray& ray, T& distance, unsigned int& index, Vector2<T>& barycenter) const;

	//Destructor
	~BVH();

private:
	static const T maxBound;

	struct BVHBox : Box<T>
	{
		Vector3<T> center;
		unsigned int indices[3];
	};

	struct BVHNode
	{
		Vector3<T> bottom;
		Vector3<T> top;
		virtual bool isLeaf() = 0;
	};

	struct BVHBranch : BVHNode
	{
		BVHNode* left;
		BVHNode* right;
		virtual bool isLeaf() { return false; }
	};

	struct BVHLeaf : BVHNode
	{
		unsigned int numIndices;
		unsigned int* indexArray;
		virtual bool isLeaf() { return true; }
	};

	BVHNode* recurse(std::vector<BVHBox>& workSet, unsigned int depth = 0);
	bool recurseIntersect(BVHNode* node, const Mesh& mesh, const Ray& ray, T& distance, unsigned int& index, Vector2<T>& barycenter, unsigned int depth = 0) const;

	BVHNode* root;
};
