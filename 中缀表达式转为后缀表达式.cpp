#include<iostream>
#include<stack>
#include<string>
#include<cctype>
#include<vector>
using namespace std;

class cal {
public:
	vector<string> output; //输出的结果
	int Priority(char c) {
		switch (c)
		{
		case '+' :	return 1;
		case '-':	return 1;
		case '/':	return 2;
		case '*':	return 2;
		case '^':	return 3;
		default:
			return -1;
			break;
		}
	}
	void in_post(const string &s)
	{
		stack<char> op; // 用于保存操作符
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == ' ')	continue;
			if (s[0] == '-')	continue;
			if (isdigit(s[i]))
			{
				int num = s[i] - '0';
				while (isdigit(s[i+1]))
				{
					num = num * 10 + (s[i + 1] - '0');
					i++;
				}
				output.push_back(to_string(num));
			}
			else if (isalpha(s[i]))
			{
				output.push_back(string(1,s[i]));
			}
			else if (s[i]=='(')
			{
				op.push(s[i]);
			}
			else if (s[i]==')')
			{
				while (!op.empty()&&op.top()!='(')
				{
					output.push_back(string(1,op.top()));
					op.pop();
				}
				op.pop();
			}
			else { // 处理操作符
				while (!op.empty() && Priority(s[i]) <= Priority(op.top())) {
					output.push_back(string(1, op.top())); // 将操作符加入输出
					op.pop();
				}
				op.push(s[i]); // 当前操作符入栈
			}
		}
		while (!op.empty())
		{
			output.push_back(string(1,op.top()));
			op.pop();
		}
	}
	void show_post(const vector<string>& out) {
		for (const auto& str : out) {
			cout << str << " "; // 输出后缀表达式
		}
		cout << endl; // 输出换行
	}
};

int main()
{
	cal c;
	c.in_post("2*(9+6/3-5)+4");
	c.show_post(c.output);
	return 0;
}