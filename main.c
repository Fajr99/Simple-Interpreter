#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAXSIZE 1000


//<BST
typedef struct
{
    char key;
    float value;
    struct Node *right;
    struct Node *left;
} Node;

Node *newNode(char name)
{
    Node *n = malloc(sizeof(Node));
    n->key = name;
    n->value = 0;
    n->right = NULL;
    n->left = NULL;
    return n;
}
Node *root = NULL;

Node *insert(Node *node, char name)
{
    if (node == NULL)
        return newNode(name);
    if (name < node->key)
        node->left = insert(node->left, name);
    else if (name > node->key)
        node->right = insert(node->right, name);
    return node;
}

void setValue(Node *node,char name,float value)
{
    if (name == node->key)
        node->value=value;
    else if (name > node->key)
        return setValue(node->right, name,value);
    else
        return setValue(node->left, name,value);
}

Node *search(Node *node, char name)
{
    if (node == NULL)
        return NULL;
    if (name == node->key)
        return node;
    else if (name > node->key)
        return search(node->right, name);
    else
        return search(node->left, name);
}

void inOrder(Node* root)
{
    if(root == NULL) return;
    inOrder(root->left);
    printf("\n%c = %f",root->key,root->value);
    inOrder(root->right);
}

//BST/>

int priority(char op)
{
    switch (op)
    {
        case '+':
        case '-':
            return 0;
        case '*':
        case '/':
            return 1;
        case '^':
            return 2;
        case '(' :
            return 3;
    }
}

typedef union
{
    float fData;
    char cData;
} Item;

typedef struct
{
    Item items[MAXSIZE];
    int peak;
} Stack;

Stack *initialize()
{
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->peak = 0;
    return s;
}

int isEmpty(Stack *s)
{
    if (!(s->peak)) return 1;
    else return 0;
}

Item peak(Stack *s)
{
    return s->items[(s->peak) - 1];
}

Item pop(Stack *s)
{
    s->peak--;
    Item value = s->items[s->peak];
    return value;

}

void push(Stack *s, Item value)
{
    s->items[s->peak++] = value;
}
void swap (Node *x, Node *y)
{
    Node tmp = *x;
    *x = *y;
    *y = tmp;
}


void makeHeap(Node *arr,int arrayLength)
{

    for(int i = 1; i < arrayLength; i++)
    {
        int index = i;

        while(index)
        {

            if(index%2!=0)
            {
                if(arr[index].value > arr[index/2].value)
                {
                    swap(&arr[index], &arr[index/2]);
                    index = index/2;
                }
                else index = 0;
            }

            else if (index%2 == 0)
            {
                if(arr[index].value > arr[index/2-1].value)
                {
                    swap(&arr[index], &arr[index/2-1]);
                    index = index/2-1;
                }
                else index = 0;

            }

        }

    }

}

int is_operator(char c) //checks if the character c is an operator, if true returns 1 else returns 0
{
    if (c == '+' || c == '-' || c  == '*' || c == '/'|| c == '^' || c == '(' || c == ')')
        return 1;
    else
        return 0;
}

void heapify (Node *arr, int n, int index)
{
    int leftChild = index * 2 + 1;
    int rightChild = index * 2 + 2;
    int max = index;

    //Comparing left child node with max
    if (leftChild < n && arr[leftChild].value > arr[max].value)
    {
        max = leftChild;
    }

    //Comparing right child node with max
    if (rightChild < n && arr[rightChild].value > arr[max].value)
    {
        max = rightChild;
    }

    //Swap changes
    if (max != index)
    {
        swap(&arr[index], &arr[max]);
        heapify(arr, n, max);
    }
}
void sortHeap(Node *arr, int arrayLength)
{

    makeHeap(arr, arrayLength);
    int heapElements = arrayLength-1;

    for(int i = 0; i < arrayLength-1; i++)
    {
        swap(&arr[0], &arr[arrayLength-1-i]);
        heapElements--;
        heapify(arr, heapElements, 0);
    }

    printf("\nSort by value\n");
    printf("-------------\n");
    for(int i = 0; i < arrayLength; i++)
    {
        printf("%c = %f\n",arr[i].key, arr[i].value);
    }
}

int numberOfLines(char *filename)
{
    FILE *f = fopen(filename, "r");
    int count = 0;
    while (!feof(f))
    {
        char line[100];
        fgets(line,100,f);
        count++;
    }
    return count;
}

float evaluatePostfix(char *postfix)
{
    int i;
    float result, operand;
    Item myItem, y, x;
    Stack *s = initialize();
    char *temp = strtok(postfix, " ");
    while (temp != NULL)
    {
        if (temp[0] == '-' && (isdigit(temp[1]) != 1))
            temp[0] = '$';

        if (isdigit(temp[0]) || temp[0] == '-' || isalpha(temp[0]))
        {
            if (isalpha(temp[0]))
                operand = search(root, temp[0])->value;
            else
                sscanf(temp, "%f", &operand);

            myItem.fData = operand;
            push(s, myItem);
        }
        else
        {
            switch (temp[0])
            {
                case '+':
                {
                    x = pop(s);
                    y = pop(s);
                    result = (x.fData) + (y.fData);
                    myItem.fData = result;
                    push(s, myItem);
                    break;
                }
                case '$':
                {
                    x = pop(s);
                    y = pop(s);
                    result = (y.fData) - (x.fData);
                    myItem.fData = result;
                    push(s, myItem);
                    break;
                }
                case '*':
                {
                    x = pop(s);
                    y = pop(s);
                    result = (x.fData) * (y.fData);
                    myItem.fData = result;
                    push(s, myItem);
                    break;
                }
                case '/':
                {
                    x = pop(s);
                    y = pop(s);
                    result = (y.fData) / (x.fData);
                    myItem.fData = result;
                    push(s, myItem);
                    break;
                }
                case '^':
                {
                    x = pop(s);
                    y = pop(s);
                    result = pow((y.fData), (x.fData));
                    myItem.fData = result;
                    push(s, myItem);
                    break;
                }
            }
        }
        temp = strtok(NULL, " ");
    }
    result = pop(s).fData;
    return result;
}

void infixToPostfix(char *filename, char *postfix)
{
    root = NULL;
    char infix[256];
    int num, k;
    float afterEvaluation;
    num = numberOfLines(filename);
    Node nodesArray[num];
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("\nFile Not Found !!\n");
    }
    for (k = 0; k < num; k++)
    {
        fgets(infix, 256, f);
        strncat(infix," ", 1);
        Item myItem;
        char prepost[MAXSIZE];
        strcpy(prepost, infix);
        int i, j = 0;
        Stack *s = initialize();
        root = insert(root, prepost[0]);

        for (i = 0; i < strlen(prepost); i++)
        {
            if(prepost[i]=='=')
                break;
            else
            {
                if((prepost[i]!='=')&&(i==strlen(prepost)-1))
                    printf("\nInvalid infix expression, (=) is missing, results won't be affected !!\n");
            }
        }

        int countOpenBracket = 0,countCloseBracket = 0;

        for (i = 0; i < strlen(prepost); i++)
        {
            if(prepost[i] == '(')
            {
                countOpenBracket++;
            }
            else if(prepost[i] == ')')
            {
                countCloseBracket++;
            }
        }
        if(countCloseBracket != countOpenBracket)
        {
            printf("\nInvalid infix expression, a bracket is missing, results will be affected !!\n");
        }
        countOpenBracket = 0;
        countCloseBracket = 0;

        for (i = 0; i <strlen(prepost);i++)
        {
            if(!(prepost[i] == '=' || prepost[i] == '+' || prepost[i] == '-'
                 || prepost[i] == '*' || prepost[i] == '/' || prepost[i] == '.'
                 || prepost[i] == ')' || prepost[i] == '(' || prepost[i] == ' '
                 || isdigit(prepost[i]) || isalpha(prepost[i]) || prepost[i] == 10))
            {
                printf("\nInvalid symbol, results won't be affected !!\n");
                break;
            }
        }

        int countOperator = 0;
        int l;

        for (i = 0; i < strlen(prepost); i++)
        {
            if(prepost[i]=='=')
            {
                l = i;
                break;
            }
        }
        for(int m = 0; m<l; m++)
        {
            if(is_operator(prepost[m]))
                countOperator++;
            if(countOperator)
            {
                printf("\nInvalid infix expression, left hand side must have only one variable\n");
                break;
            }
        }

        for (i = 3; i < strlen(prepost); i++)
        {
            if (!i && prepost[i] == '-')
                prepost[i] = '$';

            if (prepost[i] == '-' && !isdigit(prepost[i - 1]))
                prepost[i] = '$';
        }
        for (i = 3; i < strlen(prepost); i++)
        {
            myItem.cData = prepost[i];
            if (isdigit(prepost[i]) || prepost[i] == '.' || prepost[i] == '$' || isalpha(prepost[i]))
            {
                postfix[j] = prepost[i];
                j++;
            }
            else
            {
                postfix[j] = ' ';
                j++;
                if (prepost[i] == ')')
                {
                    while (!isEmpty(s) && peak(s).cData != '(')
                    {
                        postfix[j] = pop(s).cData;
                        j++;
                        postfix[j] = ' ';
                        j++;
                    }
                    pop(s);
                }
                else if (isEmpty(s))
                    push(s, myItem);
                else
                {
                    while (!isEmpty(s) && priority(peak(s).cData) >= priority(prepost[i]) && peak(s).cData != '(')
                    {
                        postfix[j] = pop(s).cData;
                        j++;
                        postfix[j] = ' ';
                        j++;
                    }
                    push(s, myItem);
                }
            }
        }
        while (!isEmpty(s))
        {
            postfix[j] = pop(s).cData;
            j++;
            postfix[j] = ' ';
            j++;
        }
        postfix[j] = NULL;

        for (i = 0; i < strlen(postfix); i++)
            if (postfix[i] == '$')
                postfix[i] = '-';
        printf("\nPostfix: %s", postfix);
        afterEvaluation = evaluatePostfix(postfix);
        setValue(root,prepost[0],afterEvaluation);
        Node* thisNode = search(root,prepost[0]);
        printf("\nresult: %c --> %f\n",thisNode->key,thisNode->value);
        nodesArray[k].key=thisNode->key;
        nodesArray[k].value=thisNode->value;
    }

    sortHeap(&nodesArray, num);
}

int main(int argc, char **argv)
{
    char postfixExpr[256] = "";
    infixToPostfix("src.txt", postfixExpr);
    printf("\nSort by variable name\n");
    printf("---------------------\n");
    inOrder(root);
    return 0;
}
