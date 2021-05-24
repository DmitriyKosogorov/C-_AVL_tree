#include<iostream>

using namespace std;

class TreeNode
{
private:
	int value;
	TreeNode* left;
	TreeNode* right;
	int height;
	const int NONE = 0;
public:
	TreeNode()
	{
		value = NONE;
		left = NULL;
		right = NULL;
		height = 0;
	}
	TreeNode(int name)
	{
		value = name;
		left = NULL;
		right = NULL;
		height = 0;
	}
	int getvalue()
	{
		return this->value;
	}
	TreeNode* get_left()
	{
		return this->left;
	}
	TreeNode* get_right()
	{
		return this->right;
	}
	void give_left(TreeNode* newLeft)
	{
		left = newLeft;
		return;
	}
	void give_right(TreeNode* newRight)
	{
		right = newRight;
		return;
	}
	friend class Tree;
};

class Tree
{
private:
	TreeNode* root;

public:
	TreeNode* get_root()
	{
		return root;
	}

	TreeNode* insert(TreeNode* elem, int newval)
	{
		if (elem == NULL)
		{
			elem = new TreeNode;
			elem->value = newval;
			elem->height = 0;
			elem->left = elem->right = NULL;
		}
		else if (newval < elem->value)
		{
			elem->left = insert(elem->left, newval);
			if (height(elem->left) - height(elem->right) == 2)
			{
				if (newval < elem->left->value)
					elem = right_rotate(elem);
				else
					elem = rr_rotate(elem);
			}
		}
		else if (newval > elem->value)
		{
			elem->right = insert(elem->right, newval);
			if (height(elem->right) - height(elem->left) == 2)
			{
				if (newval > elem->right->value)
					elem = left_rotate(elem);
				else
					elem = ll_rotate(elem);
			}
		}

		elem->height = max(height(elem->left), height(elem->right)) + 1;
		return elem;
	}

	TreeNode* right_rotate(TreeNode* elem)
	{
		TreeNode* verh = elem->left;
		elem->left = verh->right;
		verh->right = elem;
		elem->height = max(height(elem->left), height(elem->right)) + 1;
		verh->height = max(height(verh->left), elem->height) + 1;
		return verh;
	}

	TreeNode* left_rotate(TreeNode*& t)
	{
		TreeNode* u = t->right;
		t->right = u->left;
		u->left = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(t->right), t->height) + 1;
		return u;
	}

	TreeNode* ll_rotate(TreeNode*& t)
	{
		t->right = right_rotate(t->right);
		return left_rotate(t);
	}

	TreeNode* rr_rotate(TreeNode*& t)
	{
		t->left = left_rotate(t->left);
		return right_rotate(t);
	}

	TreeNode* findMin(TreeNode* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->left == NULL)
			return t;
		else
			return findMin(t->left);
	}

	TreeNode* findMax(TreeNode* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->right == NULL)
			return t;
		else
			return findMax(t->right);
	}

	TreeNode* remove(int x, TreeNode* t)
	{
		TreeNode* temp;

		if (t == NULL)
			return NULL;

		else if (x < t->value)
			t->left = remove(x, t->left);
		else if (x > t->value)
			t->right = remove(x, t->right);

		else if (t->left && t->right)
		{
			temp = findMin(t->right);
			t->value = temp->value;
			t->right = remove(t->value, t->right);
		}
		else
		{
			temp = t;
			if (t->left == NULL)
				t = t->right;
			else if (t->right == NULL)
				t = t->left;
			delete temp;
		}
		if (t == NULL)
			return t;

		t->height = max(height(t->left), height(t->right)) + 1;
		if (height(t->left) - height(t->right) == 2)
		{
			if (height(t->left->left) - height(t->left->right) == 1)
				return left_rotate(t);
			else
				return ll_rotate(t);
		}
		else if (height(t->right) - height(t->left) == 2)
		{
			if (height(t->right->right) - height(t->right->left) == 1)
				return right_rotate(t);
			else
				return rr_rotate(t);
		}
		return t;
	}

	int height(TreeNode* t)
	{
		return (t == NULL ? -1 : t->height);
	}

	int getBalance(TreeNode* t)
	{
		if (t == NULL)
			return 0;
		else
			return height(t->left) - height(t->right);
	}
	void print_elem(TreeNode* elem, int n, char c)
	{
		if (elem == NULL)
			return;
		n = n + 1;
		print_elem(elem->right, n, '/');
		for (int i = 0; i < n; i++)
			cout << "\t";
		cout << c << elem->value << endl;
		print_elem(elem->left, n, '\\');

	}

	Tree()
	{
		root = NULL;
	}

	void remove(int x)
	{
		root = remove(x, root);
		return;
	}

	void print_tree()
	{
		print_elem(root, 0, ' ');
		return;
	}
	void insert(int elem)
	{
		root = insert(root, elem);
		return;
	}
};

int main()
{
	Tree tree;
	tree.insert(20);
	tree.insert(25);
	tree.insert(15);
	tree.insert(10);
	tree.insert(30);
	tree.insert(5);
	tree.insert(35);
	tree.insert(67);
	tree.insert(43);
	tree.insert(21);
	tree.insert(10);
	tree.insert(89);
	tree.insert(38);
	tree.insert(69);
	tree.print_tree();
	tree.remove(5);
	tree.remove(35);
	tree.remove(65);
	tree.remove(89);
	tree.remove(43);
	tree.remove(88);
	tree.remove(20);
	tree.remove(38);
	cout << endl << endl << endl;
	tree.print_tree();
}