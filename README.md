# expression
Simple expression evaluation 简单表达式（四则运算）求值

main函数是简单的用法，求值使用的__int64类型的数据，可以自行修改为其他类型。

表达式求值先把中缀表达式转换成后缀表达式，后缀表达式计算机更容易处理

中缀表达式转后缀表达式转换规则

使用一个缓冲区或string存放转换后的后缀表达式这里用string，使用一个栈存放中缀表达式中的符号

1、如果是左括号'('直接入符号栈；

2、如果是右括号')'将符号栈中的符号按顺序出栈放入后缀表达式string中，直到遇到第一个左括号为止；

3、若是" + - * / "运算符，则与符号栈顶的元素优先级相比较，如果当前运算符优先级高则当前运算符进入符号栈，如果当前运算符优先级低于或等于符号栈顶元素的优先级则将符号栈顶元素出栈放入后缀表达式string中，然后继续比较，直到该运算符进栈或者栈空为止。

后缀表达式求值
使用一个存放数字的栈

从左到右遍历表达式，遇到数字则入栈，遇到运算符从栈中弹出两个数值进行计算，将计算结果再次入栈。最后栈中只剩下一个元素的时候为计算结果。
