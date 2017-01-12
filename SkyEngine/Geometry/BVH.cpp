
#include "BVH.h"

template <class T>
BVH<T>::BVH(const Mesh& mesh)
{
}

template <class T>
BVH<T>::BVH(const IndexedMesh& mesh)
{
	std::vector<BVHBox> workSet;
	Vector3<T> bottom(maxBound);
	Vector3<T> top(-maxBound);

	for(unsigned int i = 0; i < mesh.numIndices; i += 3)
		{
			BVHBox box;
			box.bounds[0] = Vector3<T>(maxBound);
			box.bounds[1] = Vector3<T>(-maxBound);
			box.indices[0] = mesh.indexArray[i];
			box.indices[1] = mesh.indexArray[i + 1];
			box.indices[2] = mesh.indexArray[i + 2];

			box.bounds[0] = Vector3<T>::minima(box.bounds[0], mesh.vertexArray[i].position);
			box.bounds[0] = Vector3<T>::minima(box.bounds[0], mesh.vertexArray[i + 1].position);
			box.bounds[0] = Vector3<T>::minima(box.bounds[0], mesh.vertexArray[i + 2].position);

			box.bounds[1] = Vector3<T>::maxima(box.bounds[1], mesh.vertexArray[i].position);
			box.bounds[1] = Vector3<T>::maxima(box.bounds[1], mesh.vertexArray[i + 1].position);
			box.bounds[1] = Vector3<T>::maxima(box.bounds[1], mesh.vertexArray[i + 2].position);

			bottom = Vector3<T>::minima(bottom, box.bounds[0]);
			top = Vector3<T>::maxima(top, box.bounds[1]);

			box.center = (box.bounds[0] + box.bounds[1]) * 0.5;

			workSet.push_back(box);
		}

	root = recurse(workSet);

	root->bottom = bottom;
	root->top = top;
}

template <class T>
bool BVH<T>::intersect(const Mesh& mesh, const Ray& ray, T& distance, unsigned int& index, Vector2<T>& barycenter) const
{
	return recurseIntersect(root, mesh, ray, distance, index, barycenter);
}

template <class T>
BVH<T>::~BVH()
{
	//TODO: Implement destructor...
}

template <class T>
const T BVH<T>::maxBound = std::numeric_limits<T>::max();

template <class T>
typename BVH<T>::BVHNode* BVH<T>::recurse(std::vector<BVHBox>& workSet, unsigned int depth)
{
	if(workSet.size() < 4)
		{
			BVHLeaf* leaf = new BVHLeaf();
			leaf->numIndices = workSet.size() * 3;
			leaf->indexArray = new unsigned int[leaf->numIndices];
			unsigned int j = 0;
			for(unsigned int i = 0; i < workSet.size(); ++i)
				{
					leaf->indexArray[j++] = workSet[i].indices[0];
					leaf->indexArray[j++] = workSet[i].indices[1];
					leaf->indexArray[j++] = workSet[i].indices[2];
				}
			return leaf;
		}

	Vector3<T> bottom(maxBound);
	Vector3<T> top(-maxBound);

	for(unsigned int i = 0; i < workSet.size(); ++i)
		{
			BVHBox& box = workSet[i];
			bottom = Vector3<T>::minima(bottom, box.bounds[0]);
			top = Vector3<T>::maxima(top, box.bounds[1]);
		}

	T side0 = top.x - bottom.x;
	T side1 = top.y - bottom.y;
	T side2 = top.z - bottom.z;

	T minCost = workSet.size() * (side0 * side1 + side1 * side2 + side2 * side0);

	T bestSplit = maxBound;

	int bestAxis = -1;

	for(unsigned int i = 0; i < 3; ++i)
		{
			unsigned int axis = i;

			T start, stop, step;

			if(axis == 0)
				{
					start = bottom.x;
					stop = top.x;
				}
			else if(axis == 1)
				{
					start = bottom.y;
					stop = top.y;
				}
			else
				{
					start = bottom.z;
					stop = top.z;
				}

			if(fabsf(stop - start) < 1e-4)
				continue;

			step = (stop - start) / (1024 / (depth + 1));

			for(T testSplit = start + step; testSplit < stop - step; testSplit += step)
				{
					Vector3<T> leftBottom(maxBound);
					Vector3<T> leftTop(-maxBound);

					Vector3<T> rightBottom(maxBound);
					Vector3<T> rightTop(-maxBound);

					unsigned int countLeft = 0, countRight = 0;

					for(unsigned int j = 0; j < workSet.size(); ++j)
						{
							BVHBox& box = workSet[j];

							T value;
							if(axis == 0)
								value = box.center.x;
							else if(axis == 1)
								value = box.center.y;
							else
								value = box.center.z;

							if(value < testSplit)
								{
									leftBottom = Vector3<T>::minima(leftBottom, box.bounds[0]);
									leftTop = Vector3<T>::maxima(leftTop, box.bounds[1]);
									countLeft++;
								}
							else
								{
									rightBottom = Vector3<T>::minima(rightBottom, box.bounds[0]);
									rightTop = Vector3<T>::maxima(rightTop, box.bounds[1]);
									countRight++;
								}
						}

					if(countLeft <= 1 || countRight <= 1)
						continue;

					T leftSide0 = leftTop.x - leftBottom.x;
					T leftSide1 = leftTop.y - leftBottom.y;
					T leftSide2 = leftTop.z - leftBottom.z;

					T rightSide0 = rightTop.x - rightBottom.x;
					T rightSide1 = rightTop.y - rightBottom.y;
					T rightSide2 = rightTop.z - rightBottom.z;

					T surfaceLeft = leftSide0 * leftSide1 + leftSide1 * leftSide2 + leftSide2 * leftSide0;
					T surfaceRight = rightSide0 * rightSide1 + rightSide1 * rightSide2 + rightSide2 * rightSide0;

					T totalCost = surfaceLeft * countLeft + surfaceRight * countRight;

					if(totalCost < minCost)
						{
							minCost = totalCost;
							bestSplit = testSplit;
							bestAxis = axis;
						}
				}
		}

	if(bestAxis == -1)
		{
			BVHLeaf* leaf = new BVHLeaf();
			leaf->numIndices = workSet.size() * 3;
			leaf->indexArray = new unsigned int[leaf->numIndices];
			unsigned int j = 0;
			for(unsigned int i = 0; i < workSet.size(); ++i)
				{
					leaf->indexArray[j++] = workSet[i].indices[0];
					leaf->indexArray[j++] = workSet[i].indices[1];
					leaf->indexArray[j++] = workSet[i].indices[2];
				}
			return leaf;
		}

	std::vector<BVHBox> left;
	std::vector<BVHBox> right;

	Vector3<T> leftBottom(maxBound);
	Vector3<T> leftTop(-maxBound);
	Vector3<T> rightBottom(maxBound);
	Vector3<T> rightTop(-maxBound);

	for(unsigned int i = 0; i < workSet.size(); ++i)
		{
			BVHBox& box = workSet[i];

			T value;
			if(bestAxis == 0)
				value = box.center.x;
			else if(bestAxis == 1)
				value = box.center.y;
			else
				value = box.center.z;

			if(value < bestSplit)
				{
					left.push_back(box);
					leftBottom = Vector3<T>::minima(leftBottom, box.bounds[0]);
					leftTop = Vector3<T>::maxima(leftTop, box.bounds[1]);
				}
			else
				{
					right.push_back(box);
					rightBottom = Vector3<T>::minima(rightBottom, box.bounds[0]);
					rightTop = Vector3<T>::maxima(rightTop, box.bounds[1]);
				}
		}

	BVHBranch* inner = new BVHBranch();

	inner->left = recurse(left, depth + 1);
	inner->left->bottom = leftBottom;
	inner->left->top = leftTop;

	inner->right = recurse(right, depth + 1);
	inner->right->bottom = rightBottom;
	inner->right->top = rightTop;

	return inner;
}

template <class T>
bool BVH<T>::recurseIntersect(BVHNode* node, const Mesh& mesh, const Ray& ray, T& distance, unsigned int& index, Vector2<T>& barycenter, unsigned int depth) const
{
	if(depth > 50)
		{
			distance = 0;
			index = 0;
			barycenter = { 0.0, 0.0 };
			return true;
		}

	if(Box<T>(node->bottom, node->top).intersect(ray, distance))
		{
			if(node->isLeaf())
				{
					BVHLeaf* leaf = (BVHLeaf*)node;

					bool intersect = false;
					T tempDist, u, v;

					distance = Ray::maxLength;
					for(unsigned int i = 0; i < leaf->numIndices; i += 3)
						{
							if(mesh.triangleIntersect(ray,
								   mesh.vertexArray[leaf->indexArray[i]].position, mesh.vertexArray[leaf->indexArray[i + 1]].position,
								   mesh.vertexArray[leaf->indexArray[i + 2]].position, tempDist, u, v)
								&& tempDist > 0 && tempDist < distance)
								{
									distance = tempDist;
									barycenter = { u, v };
									index = leaf->indexArray[i];
									intersect = true;
								}
						}

					return intersect;
				}
			else
				{
					T testDistance;
					unsigned int testIndex;
					Vector2<T> testBarycenter;

					if(recurseIntersect(((BVHBranch*)node)->left, mesh, ray, testDistance, testIndex, testBarycenter, depth + 1))
						{
							if(recurseIntersect(((BVHBranch*)node)->right, mesh, ray, distance, index, barycenter, depth + 1) && distance < testDistance)
								return true;
							else
								{
									distance = testDistance;
									index = testIndex;
									barycenter = testBarycenter;
									return true;
								}
						}
					else if(recurseIntersect(((BVHBranch*)node)->right, mesh, ray, distance, index, barycenter, depth + 1))
						return true;
					else
						return false;
				}
		}
	return false;
}

template class BVH<float>;
