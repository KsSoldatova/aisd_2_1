#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

struct binary_tree
{
	int data;
	binary_tree* left;
	binary_tree* right;
	binary_tree(int data = 0, binary_tree* left = NULL, binary_tree* right = NULL)
	{
		this->data = data;
		this->left = left;
		this->right = right;
	}
};


class b_tree
{
private:
	binary_tree* root;
public:
	b_tree() { root = NULL; }

	b_tree(int data) { root = new binary_tree(data, NULL, NULL); }

	b_tree(const b_tree& tr)
	{
		root = new binary_tree();
		root = copy(tr.root, root);
	}
	binary_tree* copy(binary_tree* old_tree, binary_tree* new_tree)
	{
		if (!old_tree) { return NULL; }
		new_tree = new binary_tree(old_tree->data, NULL, NULL);
		if (old_tree->left != NULL)
			new_tree->left = copy(old_tree->left, new_tree->left);
		else
			new_tree->left = NULL;

		if (old_tree->right != NULL)
			new_tree->right = copy(old_tree->right, new_tree->right);
		else
			new_tree->right = NULL;

		return new_tree;
	}

	~b_tree() { delete_tree(root); }
	void delete_tree(binary_tree* root)
	{
		if (root)
		{
			delete_tree(root->left);
			delete_tree(root->right);
			delete(root);
			root = NULL;
		}
	}

	b_tree operator =(const b_tree& bt)
	{
		root = new binary_tree(0, NULL, NULL);
		root = copy(bt.root, root);
		return *this;
	}
	binary_tree* get_root() { return root; }

	void print_tree(binary_tree* root, int ident=0, int level=3) const
	{
		if (root)
		{
			print_tree(root->right, 1, level + 2);
			for (int i = 0; i < level; i++) cout << " ";
			if (ident == 0) cout <<"к: "<< root->data << "--------------" << endl;
			if (ident == 1) cout << "п: "<<root->data << endl;
			if (ident == -1) cout <<"л: "<< root->data << endl;
			print_tree(root->left, -1, level + 2);
		}
	}

	bool insert(int data)
	{
		if (!root)
		{
			root = new binary_tree(data);
			return true;
		}
		binary_tree* tmp = root;
		while (tmp && tmp->data != data)
		{
			if (tmp->data > data && tmp->left == NULL)
			{
				tmp->left = new binary_tree(data);
				return true;
			}

			if (tmp->data < data && tmp->right == NULL)
			{
				tmp->right = new binary_tree(data);
				return true;
			}

			if (tmp->data > data) tmp = tmp->left;
			else tmp = tmp->right;
		}
		return false;
	}

	bool contains(int data) const
	{
		binary_tree* tmp = root;
		while (tmp)
		{
			if (tmp->data == data) return true;
			if (tmp->data > data) tmp = tmp->left;
			else if (tmp->data < data) tmp = tmp->right;
		}
		return false;
	}

	bool erase(int data)
	{
		if (!root) return false;
		binary_tree* erase_root = find(data);
		if (erase_root == NULL) return false;
		if (erase_root == root)
		{
			if (root->left == NULL && root->right == NULL)
			{
				root = NULL;
				return true;
			}
			if (erase_root->left != NULL && erase_root->right == NULL)
			{
				root = root->left;
				delete erase_root;
				return true;
			}
			if (erase_root->left == NULL && erase_root->right != NULL)
			{
				root = root->right;
				delete erase_root;
				return true;
			}
		}

		if (erase_root->left == NULL && erase_root->right == NULL)
		{
			binary_tree* p_erase = find_p(data, root);
			if (p_erase->left == erase_root) p_erase->left = NULL;
			else p_erase->right = NULL;
			delete erase_root;
			return true;
		}
		if (erase_root->left != NULL && erase_root->right == NULL)
		{
			binary_tree* p_erase = find_p(data, root);
			if (p_erase->left == erase_root) p_erase->left = erase_root->left;
			else p_erase->right = erase_root->left;
			delete erase_root;
			return true;
		}
		if (erase_root->left == NULL && erase_root->right != NULL)
		{
			binary_tree* p_erase = find_p(data, root);
			if (p_erase->left == erase_root) p_erase->left = erase_root->right;
			else p_erase->right = erase_root->right;
			delete erase_root;
			return true;
		}
		if (erase_root->left != NULL && erase_root->right != NULL)
		{
			binary_tree* min_node = find_min(erase_root->right);
			binary_tree* p_min_node = find_p(min_node->data, root);
			if (min_node->right == NULL)
			{
				erase_root->data = min_node->data;
				if (p_min_node->right == min_node)
					p_min_node->right = NULL;
				else
					p_min_node->left = NULL;
				delete min_node;
				return true;
			}
			else
			{
				erase_root->data = min_node->data;
				if (p_min_node->right == min_node)
					p_min_node->right = min_node->right;
				else
					p_min_node->left = min_node->right;

				delete min_node;
				return true;
			}
		}

	}
	binary_tree* find(int data) const
	{
		binary_tree* tmp = root;
		while (tmp)
		{
			if (tmp->data == data) return tmp;
			if (tmp->data > data) tmp = tmp->left;
			else if (tmp->data < data)tmp = tmp->right;
		}
		return NULL;
	}
	binary_tree* find_p(int data, binary_tree* root) const
	{
		binary_tree* tmp = root;
		while (tmp)
		{
			if (tmp->left && (tmp->left)->data == data) return tmp;
			if (tmp->right && (tmp->right)->data == data) return tmp;
			if (tmp->data > data) tmp = tmp->left;
			else if (tmp->data < data) tmp = tmp->right;
		}
		return NULL;
	}
	binary_tree* find_min(binary_tree* root) const
	{
		if (!root) return NULL;
		binary_tree* tmp = root;
		while (tmp->left) tmp = tmp->left;
		return tmp;
	}

};
