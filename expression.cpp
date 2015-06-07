
#include <iostream>
#include <string>
#include <stack>

using namespace std;

int getPriority(char opt);
bool InfixToPostfix(string strInfix,string &strPostfix);
bool PostCalcValue(string strPostfix, __int64 *pi64RetValue);


int main(int argc, char* argv[])
{
	//string strInfix = "1 + ((2 + 3) * 4) -   5.";
	string strInfix;
	cin >> strInfix;
 	string strPostret;
	__int64 i64Value;

	if (!InfixToPostfix(strInfix, strPostret)){
		cout << "expression error";
		return 1;
	}
	if (!PostCalcValue(strPostret, &i64Value)){
		cout << "CalcValue error";
		return 1;
	}
	cout << i64Value;
	return 0;
}

//后缀表达式求值
bool PostCalcValue(string strPostfix, __int64 *pi64RetValue)
{
	if (strPostfix.empty()){
		return false;
	}
	stack<__int64> stNum;
	char *next_token = NULL;
	const char *pstrsub = strtok_s((char *)strPostfix.c_str(), " ", &next_token);
	if (pstrsub==NULL){
		return false;
	}
	char *chRet;
	__int64 i64num,i64Num1,i64Num2;

	while(pstrsub){
		switch(*pstrsub){
		case '+':{
			if (stNum.empty()){
				return false;
			}
			i64Num1 = stNum.top();
			stNum.pop();
			if (stNum.empty()){
				return false;
			}
			i64Num2 = stNum.top();
			stNum.pop();
			i64num = i64Num1 + i64Num2;
			stNum.push(i64num);
				 }
				 break;
		case '-':{
			if (stNum.empty()){
				return false;
			}
			i64Num1 = stNum.top();
			stNum.pop();
			if (stNum.empty()){
				return false;
			}
			i64Num2 = stNum.top();
			stNum.pop();
			i64num = i64Num2 - i64Num1;
			stNum.push(i64num);
				 }
				 break;
		case '*':{
			if (stNum.empty()){
				return false;
			}
			i64Num1 = stNum.top();
			stNum.pop();
			if (stNum.empty()){
				return false;
			}
			i64Num2 = stNum.top();
			stNum.pop();
			i64num = i64Num1 * i64Num2;
			stNum.push(i64num);
				 }
				 break;
		case '/':{
			if (stNum.empty()){
				return false;
			}
			i64Num1 = stNum.top();
			stNum.pop();
			if (stNum.empty()){
				return false;
			}
			i64Num2 = stNum.top();
			stNum.pop();
			if (i64Num1 == 0){
				return false;
			}
			i64num = i64Num2 / i64Num1;
			stNum.push(i64num);
				 }
				 break;
		default:
			{
				i64num = _strtoui64(pstrsub,&chRet,10);
				if (chRet==NULL){
					return false;
				}
				stNum.push(i64num);
			}
		}
		pstrsub = strtok_s(NULL, " ", &next_token);
	}
	if (stNum.size()!=1){
		return false;
	}
	*pi64RetValue = stNum.top();
	return true;
}

//中缀表达式转成后缀表达式
bool InfixToPostfix(string strInfix,string &strPostfix)
{
	if (strInfix.empty()){
		return false;
	}
	strPostfix.clear();
	stack<char> stOpe;	//符号栈
	string::iterator itIn = strInfix.begin();
	char chstOpe;

	while(itIn!=strInfix.end())
	{
		if (*itIn=='.'){						////////////////结束标志
			break;
		}
		if(*itIn==' '){							////////////////空格处理
			while(itIn!=strInfix.end()){
				if (*itIn!=' '){
					break;
				}
				itIn++;
			}
			continue;
		}
		if(*itIn>='0' && *itIn<='9')					////////////////数字处理
		{
			while(itIn!=strInfix.end()){
				if (*itIn<='0' || *itIn>='9'){
					break;
				}
				strPostfix += *itIn;
				itIn++;
			}
			strPostfix += ' ';	//数字后面的空格分隔符
			continue;
		}
		if (*itIn == '('){						////////////////'('符号处理
			stOpe.push(*itIn);
		}else if (*itIn == ')'){					////////////////'）'符号处理
			bool isOK = false;
			while(!stOpe.empty()){
				chstOpe = stOpe.top();
				stOpe.pop();
				if (chstOpe=='('){
					isOK = true;
					break;
				}
				strPostfix += chstOpe;
				strPostfix += ' ';
			}
			if (!isOK){			//没有匹配'('错误
				return false;
			}
		}else if (*itIn=='+'||*itIn=='-'||*itIn=='*'||*itIn=='/'){	////////////////四则运算符号处理
			int nCurOpePriority;			//当前操作符优先级
			int nSttopOpePriority;			//栈顶操作符优先级

			if (stOpe.empty()){
				stOpe.push(*itIn);
			}else{
				while(true){
					chstOpe = stOpe.top();
					nSttopOpePriority = getPriority(chstOpe);
					if (nSttopOpePriority == 0){
						return false;
					}
					nCurOpePriority = getPriority(*itIn);
					if (nCurOpePriority == 0){
						return false;
					}

					if (nCurOpePriority > nSttopOpePriority){	//当前操作符优先级高，当前操作符入栈
						stOpe.push(*itIn);
						break;
					}else{						//当前操作符优先级低或相等，栈中的操作符出栈
						strPostfix += chstOpe;
						strPostfix += ' ';

						stOpe.pop();
						if (stOpe.empty()){
							stOpe.push(*itIn);
							break;
						}
					}
				}
			}
		}else{
			return false;							////////////////其他字符错误
		}
		itIn++;
	}
	while(!stOpe.empty()){		//栈中剩余的符号出栈
		chstOpe = stOpe.top();
		stOpe.pop();
		strPostfix += chstOpe;
		strPostfix += ' ';
	}
	return true;
}

//获得操作符优先级
int getPriority(char opt)
{
	switch(opt){
	case '(':
		return 1; break;
	case '+':
	case '-':
		return 2; break;
	case '*':
	case '/':
		return 3; break;
	default:
		return 0;
	}
}
