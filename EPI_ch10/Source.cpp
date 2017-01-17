#include <iostream>
#include <memory>

using namespace std;

template <typename T>
class BinaryTree {

private:
	struct BinaryTreeNode {
	public:
		T data;
		unique_ptr<BinaryTreeNode> left, right;
	};

	unique_ptr<BinaryTreeNode> mpRoot;

public:
	void TreeTraversal() {
		TreeTraversal(mpRoot);
	}

	void TreeTraversal(const unique_ptr<BinaryTreeNode>& root) {
		if (root) {
			//preorder process
			cout << root->data << ", ";
			TreeTraversal(root->left);
			TreeTraversal(root->right);
		}
	}

	bool IsBalanced(const unique_ptr<BinaryTreeNode>& root) {
		#pragma region Cache height in nodes
		//if (!root) return true;

		//// tree of height 1 or 0 is always balanced
		//if (root->height <= 1) {
		//	return true;
		//}
		//else if (!root->left->height || !root->right->height) {
		//	return false;
		//	// if h_root > 1 and one subtree is empty: h_R=-1
		//	// the other subtree has to have h_L = h_root-1
		//	// delta_h = abs(h_L - h_R) = (h_root-1) - (-1) = h_root 
		//	// by definition h_root > 1 => unbalanced
		//}
		//else {
		//	// their height differ only for one level
		//	if (abs(root->left->height - root->right->height) > 1)
		//		return false;

		//	// is balanced Left
		//	if (!IsBalanced(root->left))
		//		return false;

		//	// is balanced Right
		//	if (!IsBalanced(root->right))
		//		return false;
		//}
		//return true;
		#pragma endregion
	}
};

template <typename T>
class BinaryTreeWithParent : BinaryTree<T> {

private:
	struct BinaryTreeNode {
	public:
		T data;
		shared_ptr<BinaryTreeNode> left, right;
		weak_ptr<BinaryTreeNode> parent;
	};
	
public:
	BinaryTreeNode* LCA(const BinaryTreeNode *node1, const BinaryTreeNode *node2) {
		int depth1 = Depth(node1);
		int depth2 = Depth(node2);

		if (depth1 < depth2) {
			swap(node1, node2);
		}

		while (depth1 != depth2) {
				depth1--;
				node1 = node1->parent;
		}

		// pointers are at the same depth;
		// the first ancestor with equal pointer is the LCA
		while (node1 != node2) {
			node1 = node1->parent;
			node2 = node2->parent;
		}
		return node1
	}

	static int Depth(const BinaryTreeNode *node) {
		int depth = 0;
		while (node->parent) {
			depth++;
			node = node->parent;
		}
		return depth;
	}
	
};

void main() {
	/* 10.1 */


	return;
}