#ifndef __EXPRESSIONTREE_H
#define __EXPRESSIONTREE_H


#include <afxtempl.h>



/***********************************************************************

DEFINES

************************************************************************/



#define OPERAND_NONE            -4
#define OPERAND_NODE            -3
#define OPERAND_CONSTANT        -2
#define OPERAND_VARIABLE        -1

#define OPERATOR_SINE           0
#define OPERATOR_COSINE         1
#define OPERATOR_TANGENT        2
#define OPERATOR_EXPONENT       3
#define OPERATOR_SQUAREROOT     4
#define OPERATOR_MULTIPLY       5
#define OPERATOR_DIVIDE         6
#define OPERATOR_ADD            7
#define OPERATOR_SUBTRACT       8

#define OPERATOR_OPEN           9
#define OPERATOR_CLOSE          10

#define MAX_TOKENS              500




/***************************************************************************************

STACK CLASSES

****************************************************************************************/


class COperationNode;


class COperandStackItem
    {
    public:

        COperandStackItem()   { Type = OPERAND_CONSTANT; Constant = 0.0f; pNode = NULL; }
        
        int Type;
        float Constant;
        
        COperationNode * pNode;
    };


typedef CArray<COperandStackItem *, COperandStackItem *> COperandStack;
typedef CArray<int, int>                                 COperatorStack;
typedef CArray<int, int>                                 COperandBreakStack;
typedef CArray<int, int>                                 COperatorBreakStack;




/************************************************************************

EXPRESSION TREE CLASSES

*************************************************************************/



class COperationNode;
class CTokenArray;



class CExpressionTree
    {
    public:

        CExpressionTree()   { m_pNode = NULL; }

        BOOL HasExpression()            { return(m_pNode != NULL); }
        CString GetExpressionString()   { return m_strExpression; }

        BOOL FindSolution(float variable, float * retval, BOOL * retvalgood);
        
        BOOL BuildExpression(CString strExpression);
        BOOL BreakStringIntoTokens(CString string, CTokenArray * tokens);
        BOOL VerifyTokens(CTokenArray * tokens);
        BOOL ConvertToNodes(COperandStack * operandstack, COperatorStack * operatorstack, COperandBreakStack * operandbreakstack, COperatorBreakStack * operatorbreakstack);


    private:

        CString             m_strExpression;
        COperationNode *    m_pNode;
    };



class COperationNode
    {
    public:

        COperationNode()        { pLeftChild = NULL; pRightChild = NULL; }
        ~COperationNode()       { if (pLeftChild) delete pLeftChild; if (pRightChild) delete pRightChild; }

        void GetValue(float variable, float * retval, BOOL * retvalgood);


    public:

        int Operator;
    
        int LeftType;
        int RightType;

        float LeftConstant;
        float RightConstant;

        COperationNode * pLeftChild, * pRightChild;
    };





/***************************************************************************************

TOKEN CLASSES

****************************************************************************************/



class CToken
    {
    public:

        int Type;
        float Value;
    };



class CTokenArray
    {
    public:
        
        CTokenArray()   { m_NumTokens = 0; }

        void Add(int type, float value = 0.0f);
        void Insert(int pos, int type, float value = 0.0f);
        
        int GetType(int pos);
        float GetValue(int pos);
        int GetNumTokens()          { return m_NumTokens; }

        CToken * GetToken(int pos);
         

    private:

        int     m_NumTokens;
        CToken  m_Token[MAX_TOKENS];
    };


#endif