#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

enum type { ADD, MUL, NUMBER };

struct node 
{
    type t;
    int64_t num = 0;
    node* left = nullptr;
    node* right = nullptr;

    node(node* l = nullptr, node* r = nullptr)
    {

    }

    node(type p, int64_t k, node* l = nullptr, node* r = nullptr)
    {
        t = p;
        num = k;
        left = l;
        right =  r;
    }

    void set_right(node* r)
    {
        right = r;
    }

    static node* mul_node(node* l = nullptr, node* r = nullptr)
    {
        return new node(MUL, 0, l, r);
    }

    static node* add_node(node* l = nullptr, node* r = nullptr)
    {
        return new node(ADD, 0, l, r);
    }

    static node* num_node(int64_t k, node* l = nullptr, node* r = nullptr)
    {
        return new node(NUMBER, k, l, r);
    }
};

int64_t eval_ast(node* root)
{
    if (root->t == NUMBER)
    {
        return root->num;
    }
    else if (root->t == ADD)
    {
        return eval_ast(root->left) + eval_ast(root->right);
    }
    else if (root->t == MUL)
    {
        return eval_ast(root->left) * eval_ast(root->right);
    }
    return 0;
}

void delete_ast(node* root)
{
    if (root->left)
    {
        delete_ast(root->left);
    }
    if (root->right)
    {
        delete_ast(root->right);
    }
    delete root;
}

node* build_ast(std::string in)
{
    node* root = nullptr;
    node* left = nullptr;
    node* right = nullptr;

    bool first = true;
    for (int i = 0; i < in.size(); i++)
    {
        if (root)
        {
            if (in.at(i) == '(')
            {
                int brackets = 1;
                int begin = i;
                i++;
                while (i < in.size() && brackets != 0)
                {
                    if (in.at(i) == '(')
                    {
                        brackets++;
                    }
                    else if (in.at(i) == ')')
                    {
                        brackets--;
                    }
                    i++;
                }
                int end = i;
                std::string sub = in.substr(begin, end - begin);
                right = build_ast(sub);
                root->set_right(right);
                left = root;
                root = nullptr;
                right = nullptr;
            }
            else if (in.at(i) == ' ')
            {
                continue;
            }
            else
            {
                int k = 0;
                while (i < in.size() && in.at(i) != ' ' && in.at(i) != ')')
                {
                    k *= 10;
                    k += in.at(i) - '0';
                    i++;
                }
                right = node::num_node(k);
                root->set_right(right);
                left = root;
                root = nullptr;
                right = nullptr;
            }
        }
        else 
        {
            if (in.at(i) == '(')
            {
                continue;
            }
            if (in.at(i) == '+')
            {
                root =node::add_node(left);
            }
            else if (in.at(i) == '*')
            {
                root = node::mul_node(left);
            }
            else if (in.at(i) == ' ')
            {
                continue;
            }
            else if (in.at(i) == ')')
            {
                continue;
            }
            else
            {
                int k = 0;
                while (i < in.size() && in.at(i) != ' ')
                {
                    k *= 10;
                    k += in.at(i) - '0';
                    i++;
                }
                left = node::num_node(k);
            }
        }
    }
    return left;
}

std::string format(std::string in)
{
    std::string result;
    for (int i = 0; i < in.size(); i++)
    {
        if (in.at(i) == '+')
        {
            // left side
            if (result.at(result.size() - 2) == ')')
            {
                int brackets = 1;
                int j = result.size() - 3;
                std::string result_copy(result);
                result.pop_back();
                result.pop_back();
                while (j >= 0 && brackets != 0)
                {
                    if (result.at(j) == '(')
                    {
                        brackets--;
                    }
                    if (result.at(j) == ')')
                    {
                        brackets++;
                    }
                    j--;
                    result.pop_back();
                }
                j += 2;
                std::string sub = result_copy.substr(j, result_copy.size() - 2 - j);
                result.push_back('(');
                result.push_back('(');
                for (auto const& c : sub)
                {
                    result.push_back(c);
                }
                result.push_back(')');
                result.push_back(' ');
            }
            else 
            {
                int j = i - 2;
                result.pop_back();
                while (j >= 0 && in.at(j) != ' ')
                {
                    j--;
                    result.pop_back();
                }
                result.push_back('(');
                for (int k = j + 1; k < i; k++)
                {
                    result.push_back(in.at(k));
                }
            }

            result.push_back('+');
            result.push_back(' ');
            i += 2;

            if (in.at(i) == '(')
            {
                int brackets = 1;
                int begin = i + 1;
                i = i + 1;
                while (i < in.size() && brackets != 0)
                {
                    if (in.at(i) == '(')
                    {
                        brackets++;
                    }
                    if (in.at(i) == ')')
                    {
                        brackets--;
                    }
                    i++;
                }
                i-= 2;
                std::string sub = in.substr(begin, i - begin + 1);
                std::string formatted = format(sub);
                result.push_back('(');
                for (auto const& c : formatted)
                {
                    result.push_back(c);
                }
                result.push_back(')');
            }
            else 
            {
                while (i < in.size() && in.at(i) != ' ')
                {
                    result.push_back(in.at(i));
                    i++;
                }
                result.push_back(')');
                i--;
            }
        }
        else 
        {
            result.push_back(in.at(i));
        }
    }
    return result;
}

int main(int arg, char* argv[])
{
    std::ifstream file { std::string(argv[1]) };
    std::string line;

    int64_t p1 = 0;
    int64_t p2 = 0;
    while (getline(file, line))
    {
        node* root_p1 = build_ast(line);
        std::string fline = format(line);
        node* root_p2 = build_ast(fline);
        p1 += eval_ast(root_p1);
        p2 += eval_ast(root_p2);
        delete_ast(root_p1);
        delete_ast(root_p2);
    }
    std::cout << p1 << "\n";
    std::cout << p2 << "\n";
}