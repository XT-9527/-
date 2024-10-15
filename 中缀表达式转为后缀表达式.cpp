#include<iostream>
#include<stack>
#include<string>
#include<cctype>
#include<vector>
using namespace std;

class cal {
public:
	vector<string> output; //����Ľ��
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
		stack<char> op; // ���ڱ��������
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
			else { // ���������
				while (!op.empty() && Priority(s[i]) <= Priority(op.top())) {
					output.push_back(string(1, op.top())); // ���������������
					op.pop();
				}
				op.push(s[i]); // ��ǰ��������ջ
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
			cout << str << " "; // �����׺���ʽ
		}
		cout << endl; // �������
	}
};

int main()
{
	cal c;
	c.in_post("2*(9+6/3-5)+4");
	c.show_post(c.output);
	return 0;
}