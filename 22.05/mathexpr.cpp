#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <map>
#include <set>

using namespace std;

bool is_number(string num) {
	if (num.empty()) {
		return false;
	}
	for (int i = num[0] == '-' ? 1 : 0; i < num.length(); i++) {
		if (num[i] < '0' || num[i] > '9') {
			return false;
		}
	}
	return true;
}

enum node_type { number, operation, variable };
struct ast_node {
	node_type type;
	string name;
	int value;
	ast_node *left = nullptr;
	ast_node *right = nullptr;
};

ast_node *parse_expr(string input) {
	stringstream in_stream(input);
	string token;
	int value;

	stack<ast_node *> nodes;
	while (!in_stream.eof()) {
		in_stream >> token;
		if (token.empty()) {
			continue;
		}

		if (token == "*" || token == "/" || token == "+" || token == "-" || token == "^") {
			if (nodes.empty()) {
				return nullptr;
			}
			auto right = nodes.top();
			nodes.pop();
			if (nodes.empty()) {
				return nullptr;
			}
			auto left = nodes.top();
			nodes.pop();

			auto new_node = new ast_node();
			new_node->type = node_type::operation;
			new_node->name = token;
			new_node->left = left;
			new_node->right = right;
			nodes.push(new_node);
		} else if (is_number(token)) {
			auto new_node = new ast_node();
			new_node->type = node_type::number;
			new_node->value = stoi(token);
			nodes.push(new_node);
		} else {
			auto variable_node = new ast_node();
			variable_node->type = node_type::variable;
			variable_node->name = token;

			auto new_node = variable_node;
			if (token[0] == '-') {
				if (token.length() < 2) {
					return nullptr;
				}
				variable_node->name = variable_node->name.substr(1); // Exclude minus

				new_node = new ast_node();
				new_node->type = node_type::operation;
				new_node->name = "*";
				new_node->left = variable_node;

				auto minus_one = new ast_node();
				minus_one->type = node_type::number;
				minus_one->value = -1;
				new_node->right = minus_one;
			}
			nodes.push(new_node);
		}
	}
	if (nodes.size() != 1) {
		return nullptr;
	}
	return nodes.top();
}

void dealloc_ast(ast_node *root) {
	if (root == nullptr) {
		return;
	}
	dealloc_ast(root->left);
	dealloc_ast(root->right);
	delete root;
}

int eval_expr(ast_node *root, map<string, int> &variables) {
	assert(root != nullptr);
	if (root->type == node_type::number) {
		return root->value;
	}
	if (root->type == node_type::variable) {
		auto iter = variables.find(root->name);
		if (iter != variables.end()) {
			return iter->second;
		}

		int value;
		cout << "Enter value for " << root->name << ": ";
		cin >> value;
		variables[root->name] = value;
		return value;
	}

	assert(root->type == node_type::operation);
	auto left_value = eval_expr(root->left, variables);
	auto right_value = eval_expr(root->right, variables);
	switch (root->name[0])
	{
	case '*':
		return left_value * right_value;
	case '/':
		return left_value / right_value;
	case '+':
		return left_value + right_value;
	case '-':
		return left_value - right_value;
	case '^':
		return pow(left_value, right_value);
	default:
		assert(false); // Expected a correct operation
	}
}
int eval_expr(ast_node* root) {
	map<string, int> variables;
	return eval_expr(root, variables);
}

int main() {
	string input;
	getline(cin, input);

	auto root = parse_expr(input);
	if (root == nullptr) {
		cout << "Incorrect expression." << endl;
		return 1;
	}
	cout << eval_expr(root) << endl;
	dealloc_ast(root);
	return 0;
}
