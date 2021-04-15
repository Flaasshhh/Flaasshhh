#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct Stack_char
{
	char* arr;
	int sp;
	int size;

	Stack_char() //Constructor
	{
		sp = -1;
		size = 0;
		arr = NULL;
	}

};

struct Stack_int
{
	int* arr1;
	int sp1;
	int size1;

	Stack_int() //Constructor
	{
		sp1 = -1;
		size1 = 0;
		arr1 = NULL;
	}

};

bool initialize_char(Stack_char* s, int n)
{
	s->arr = (char*)malloc(sizeof(char) * n);
	if (s->arr == NULL)
		return false;
	s->size = n;
	return true;
}

bool initialize_int(Stack_int* s, int n)
{
	s->arr1 = (int*)malloc(sizeof(int) * n);
	if (s->arr1 == NULL)
		return false;
	s->size1 = n;
	return true;
}

int push_char(Stack_char* s, char item)
{
	if (s->arr == NULL)
		return -1; //Stack not initialized
	if (s->sp + 1 == s->size)
		return -2; //Stack over flow
	s->sp++;
	s->arr[s->sp] = item;
	return 1; //No errors encountred
}

int push_int(Stack_int* s, int item)
{
	if (s->arr1 == NULL)
		return -1; //Stack not initialized
	if (s->sp1 + 1 == s->size1)
		return -2; //Stack over flow
	// s->sp1++;
	s->arr1[++s->sp1] = item;
	return 1; //No errors encountred
}
 
int pop_char(Stack_char* s, char* item)
{
	if (s->arr == NULL)
		return -1; //Stack not initialized
	if (s->sp == -1)
		return -2; //Stack under flow
	*item = s->arr[s->sp];
	s->sp--;
	return 1; //No errors encountred
}

int pop_int(Stack_int* s, int* item)
{
	if (s->arr1 == NULL)
		return -1; //Stack not initialized
	if (s->sp1 == -1)
		return -2; //Stack under flow
	*item = s->arr1[s->sp1];
	s->sp1--;
	return 1; //No errors encountred
}

bool peek(Stack_char s, char* item)
{
	if (s.sp == -1)
		return false; //Stack empty
	*item = s.arr[s.sp];
	return true; //No errors encountred
}

bool isEmpty(Stack_char s)
{
	if (s.sp == -1)
		return true; //Stack empty
	else
		return false; //No errors encountred
}

bool isOperator(char c)
{
	char ops[] = { '*', '/', '+', '-', '^' };
	for (int i = 0; i < strlen(ops); i++)
	{
		if (c == ops[i])
			return true; //Character is Operator
	}
	return false; //Character is not Operator
}

int getPriority(char c)
{
	if (c == '^')
		return 3;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else return 0;
}

int main()
{
	Stack_char st;

	char infix[100];
	char postfix[100];
	int pIndex = 0;

	printf("Enter infix expression: ");
	gets_s(infix);

	initialize_char(&st, strlen(infix));

	for (int i = 0; i < strlen(infix); i++)
	{
		if (infix[i] == '(')
			push_char(&st, infix[i]);
		else if (infix[i] == ')')
		{
			char sTop;
			peek(st, &sTop);
			while (sTop != '(')
			{
				pop_char(&st, &postfix[pIndex++]);
				peek(st, &sTop);
			}
			pop_char(&st, &sTop);	//Dispose the '('
		}
		else if (isOperator(infix[i]))
		{
			char stackTop;
			peek(st, &stackTop);
			if (getPriority(infix[i]) <= getPriority(stackTop))
			{
				pop_char(&st, &postfix[pIndex++]);
				peek(st, &stackTop);
			}
			push_char(&st, infix[i]);
		}
		else //Operand
			postfix[pIndex++] = infix[i];

	}
	while (isEmpty(st) == false)
		pop_char(&st, &postfix[pIndex++]);

	postfix[pIndex] = '\0';
	printf("\n");
	printf("Expression in Postfix form: ");
	for (int i = 0; i < strlen(postfix); i++)
		printf("%c ", postfix[i]);
	
	// Evaluation
	Stack_int se;
	initialize_int(&se, strlen(postfix));
	int answer;
	int converted;
	int temp1;
	int temp2;
	for (int j = 0; j < strlen(postfix); j++)
	{
		if (isOperator(postfix[j]))
		{
			pop_int(&se, &temp2);
			pop_int(&se, &temp1);

			if (postfix[j] == '+')
				push_int(&se, (temp1 + temp2));
			else if (postfix[j] == '-')
				push_int(&se, (temp1 - temp2));
			else if (postfix[j] == '*')
				push_int(&se, (temp1 * temp2));
			else if (postfix[j] == '/')
				push_int(&se, (temp1 / temp2));
			else if (postfix[j] == '^')
				push_int(&se, (temp1 ^ temp2));
		}
		else 
		{
			push_int(&se, (postfix[j] - 48));
		}
	}
	pop_int(&se, &answer);
	printf("\n\nFinal Evaluation: %d\n", answer);
	return 0;
}