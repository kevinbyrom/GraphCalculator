#include "stdafx.h"
#include <afxtempl.h>
#include <math.h>
#include "ExpressionTree.h"




/**************************************************************************

EXPRESSION TREE

***************************************************************************/





BOOL CExpressionTree::FindSolution(float variable, float * retval, BOOL * retvalgood)
    {

    /////////////////////////////////////////////////
    //                                             //
    // Used to get the solution for the expression //
    //                                             //
    /////////////////////////////////////////////////


    if (m_pNode == NULL)
        return FALSE;

    m_pNode->GetValue(variable, retval, retvalgood);

    return TRUE;
    }





BOOL CExpressionTree::BuildExpression(CString strExpression)
    {

    /////////////////////////////////////////////////////
    //                                                 //
    // Used to build the entire expression tree from a //
    // string expression                               //
    //                                                 //
    /////////////////////////////////////////////////////


    CTokenArray Tokens;
    COperandStack OperandStack;
    COperatorStack OperatorStack;
    COperandBreakStack OperandBreakStack;
    COperatorBreakStack OperatorBreakStack;
    COperandStackItem * item;


    // Break the string into tokens

    if (!BreakStringIntoTokens(strExpression, &Tokens))
        return FALSE;


    // Verify the tokens

    if (!VerifyTokens(&Tokens))
        return FALSE;


    // Set the new expression string

    m_strExpression = strExpression;


    // Remove any previous expression

    if (m_pNode)
        delete m_pNode;


    // For each token

    for (int i = 0; i < Tokens.GetNumTokens(); i++)
        {
        switch(Tokens.GetType(i))
            {

            // If the token is an operand, push it to the operand stack

            case OPERATOR_EXPONENT:
            case OPERATOR_MULTIPLY:
            case OPERATOR_DIVIDE:
            case OPERATOR_ADD:
            case OPERATOR_SUBTRACT:
            case OPERATOR_SQUAREROOT:
            case OPERATOR_SINE:
            case OPERATOR_COSINE:
            case OPERATOR_TANGENT:
                OperatorStack.Add(Tokens.GetType(i));
                break;


            // Else if the token is a value, push it to the value stack

            case OPERAND_CONSTANT:
                item = new COperandStackItem;

                item->Type      = OPERAND_CONSTANT;
                item->Constant  = Tokens.GetValue(i);

                OperandStack.Add(item);
                break;


            case OPERAND_VARIABLE:           
                item = new COperandStackItem;

                item->Type = OPERAND_VARIABLE;
                
                OperandStack.Add(item);
                break;


            // Else if the token is an (, push the value index to the value break stack and the operand index to the operand break stack

            case OPERATOR_OPEN:
                OperandBreakStack.Add(OperandStack.GetSize());
                OperatorBreakStack.Add(OperatorStack.GetSize());
                break;


            // Else if the token is an ), convert all between () to nodes

            case OPERATOR_CLOSE:
                ConvertToNodes(&OperandStack, &OperatorStack, &OperandBreakStack, &OperatorBreakStack);
                break;
            }
        }


    // Finally, if anything is left on the stack, convert all to last value to nodes

    if (OperatorStack.GetSize() > 0)
        ConvertToNodes(&OperandStack, &OperatorStack, NULL, NULL);


    // Set the node pointer to the item on the value stack

    m_pNode = (OperandStack.GetAt(0))->pNode;

    
    // Clear the operand stack

    OperandStack.RemoveAll();


    return TRUE;
    }




BOOL CExpressionTree::BreakStringIntoTokens(CString string, CTokenArray * tokens)
    {

    /////////////////////////////////////////////
    //                                         //
    // Used to break up the string into tokens //
    //                                         //
    /////////////////////////////////////////////


    int beginchar = 0;
    BOOL tokenisvalue = FALSE;
    BOOL lasttokenwasvalue = FALSE;
    BOOL lasttokenwasoperator = FALSE;


    for (int i = 0; i < strlen(string); i++)
        {
        switch(string[i])
            {
            // White space

            case ' ':
                if (tokenisvalue)
                    tokens->Add(OPERAND_CONSTANT, atof(string.Mid(beginchar, i - beginchar + 1)));

                tokenisvalue = FALSE;
                beginchar = i + 1;
                break;


            // If the character is a number then 

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                if (!tokenisvalue && lasttokenwasvalue)
                    return FALSE;

                tokenisvalue = TRUE;
                lasttokenwasvalue = TRUE;
                break;


            // If the character is x or X, then set the token as being the x variable

            case 'x':
            case 'X':
                if (tokenisvalue)
                    return FALSE;

                tokens->Add(OPERAND_VARIABLE);
                tokenisvalue = FALSE;
                beginchar = i + 1;
                break;


            // If the character is an ( or ), then set the token as being that operator

            case '(':
                if (tokenisvalue || lasttokenwasvalue)
                    return FALSE;

                tokens->Add(OPERATOR_OPEN);
                tokenisvalue = FALSE;
                beginchar = i + 1;
                break;


            case ')':
                if (tokenisvalue)
                    tokens->Add(OPERAND_CONSTANT, atof(string.Mid(beginchar, i - beginchar)));

                tokens->Add(OPERATOR_CLOSE);
                tokenisvalue = FALSE;
                beginchar = i + 1;
                break;


            // If the character is an operator, then set the token as being the operator

            case '+':
                if (tokenisvalue)
                    tokens->Add(OPERAND_CONSTANT, atof(string.Mid(beginchar, i - beginchar)));

                tokens->Add(OPERATOR_ADD);
                tokenisvalue = FALSE;
                lasttokenwasvalue = FALSE;
                beginchar = i + 1;
                break;

            case '-':
                if (tokenisvalue)
                    tokens->Add(OPERAND_CONSTANT, atof(string.Mid(beginchar, i - beginchar)));

                tokens->Add(OPERATOR_SUBTRACT);
                tokenisvalue = FALSE;
                lasttokenwasvalue = FALSE;
                beginchar = i + 1;
                break;

            case '*':
                if (tokenisvalue)
                    tokens->Add(OPERAND_CONSTANT, atof(string.Mid(beginchar, i - beginchar)));

                tokens->Add(OPERATOR_MULTIPLY);
                tokenisvalue = FALSE;
                lasttokenwasvalue = FALSE;
                beginchar = i + 1;
                break;

            case '/':
                if (tokenisvalue)
                    tokens->Add(OPERAND_CONSTANT, atof(string.Mid(beginchar, i - beginchar)));

                tokens->Add(OPERATOR_DIVIDE);
                tokenisvalue = FALSE;
                lasttokenwasvalue = FALSE;
                beginchar = i + 1;
                break;

            case '^':
                if (tokenisvalue)
                    tokens->Add(OPERAND_CONSTANT, atof(string.Mid(beginchar, i - beginchar)));

                tokens->Add(OPERATOR_EXPONENT);
                tokenisvalue = FALSE;
                lasttokenwasvalue = FALSE;
                beginchar = i + 1;
                break;

            case '&':
                if (tokenisvalue)
                    tokens->Add(OPERAND_CONSTANT, atof(string.Mid(beginchar, i - beginchar)));

                tokens->Add(OPERATOR_SQUAREROOT);
                tokenisvalue = FALSE;
                lasttokenwasvalue = FALSE;
                beginchar = i + 1;
                break;


            // If the character is s or S, then set the token as being the Sin operator

            case 's':
            case 'S':
                if (tokenisvalue)
                    return FALSE;

                tokens->Add(OPERATOR_SINE);
                tokenisvalue = FALSE;
                lasttokenwasvalue = FALSE;
                beginchar = i + 1;
                break;


            // If the character is c or C, then set the token as being the Cosine operator

            case 'c':
            case 'C':
                if (tokenisvalue)
                    return FALSE;

                tokens->Add(OPERATOR_COSINE);
                tokenisvalue = FALSE;
                lasttokenwasvalue = FALSE;
                beginchar = i + 1;
                break;


            // If the character is t or T, then set the token as being the Tangent operator

            case 't':
            case 'T':
                if (tokenisvalue)
                    return FALSE;

                tokens->Add(OPERATOR_TANGENT);
                tokenisvalue = FALSE;
                lasttokenwasvalue = FALSE;
                beginchar = i + 1;
                break;


            // Otherwise, return as an error

            default:
                break;
            }
        }

    if (tokenisvalue)
        tokens->Add(OPERAND_CONSTANT, atof(string.Mid(beginchar, strlen(string) - beginchar)));

    return TRUE;
    }




BOOL CExpressionTree::VerifyTokens(CTokenArray * tokens)
    {

    //////////////////////////////////////////////////////////////////////////////////////
    //                                                                                  //
    // Used to make sure the tokens are properly set, such as adding a 1 before single  //
	// operand operations to make sure that the expression can be properly built		//
    //                                                                                  //
    //////////////////////////////////////////////////////////////////////////////////////


    int i;
    int pos = 0;


    while(pos < tokens->GetNumTokens() - 1)
        {
        switch(tokens->GetType(pos))
            {
            case OPERATOR_SINE:
            case OPERATOR_COSINE:
            case OPERATOR_TANGENT:
            case OPERATOR_SQUAREROOT:
				tokens->Insert(pos, OPERAND_CONSTANT, 1.0f);
				pos += 2;
				break;

            default:
                pos++;
                break;
            }
        }

    return TRUE;
    }



        
BOOL CExpressionTree::ConvertToNodes(COperandStack * operandstack, COperatorStack * operatorstack, COperandBreakStack * operandbreakstack, COperatorBreakStack * operatorbreakstack)
    {
    int operandstackpos;
    int operatorstackpos;
    int operatorstackcount;
    COperandStackItem * item, * newitem;



    // Get the starting position of the operand stack to work with
    // If we have a pointer to the operand break stack, start at whatever
    // position was last set in the stack and remove that node

    if (operandbreakstack != NULL)
        {
        operandstackpos = operandbreakstack->GetAt(operandbreakstack->GetSize() - 1);
        operandbreakstack->RemoveAt(operandbreakstack->GetSize() - 1);
        }

    // Otherwise, start at the beginning

    else
        {
        operandstackpos = 0;
        }



    // Get the starting position of the operator stack to work with
    // If we have a pointer to the operator break stack, start at whatever
    // position was last set in the stack and remove that node

    if (operatorbreakstack != NULL)
        {
        operatorstackpos = operatorbreakstack->GetAt(operatorbreakstack->GetSize() - 1);
        operatorbreakstack->RemoveAt(operatorbreakstack->GetSize() - 1);
        }

    // Otherwise, start at the beginning

    else
        {
        operatorstackpos = 0;
        }



    // Convert the nodes based on each operator in order of EXPONENT, MULTIPLY, 
    // DIVIDE, ADD, SUBTRACT, SIN, COSINE, TANGENT

    for (int oper = OPERATOR_SINE; oper <= OPERATOR_SUBTRACT; oper++)
        {
		int thisoper, oper2;
        int i;
        int operatorpos;
        int operandpos;

        
		// Set the value of oper2 based on the current operator because 
		// when checking for multiplication operator you should also handle division
		// and when checking adding you should also check subtraction

		if (oper == OPERATOR_MULTIPLY)
			oper2 = OPERATOR_DIVIDE;
		else if (oper == OPERATOR_ADD)
			oper2 = OPERATOR_SUBTRACT;
		else
			oper2 = oper;


        operatorpos = operatorstackpos;
        operandpos = operandstackpos;


        // Check every operator in the stack to see if it matches the operator we are 
        // looking for (oper)

        while(operatorpos < operatorstack->GetSize())
            {


            // If this nodes operator matches what we are looking for

            if (operatorstack->GetAt(operatorpos) == oper || operatorstack->GetAt(operatorpos) == oper2)
                {
				
				// Set a variable to store exactly which operator we found

				if (operatorstack->GetAt(operatorpos) == oper)
					thisoper = oper;
				else
					thisoper = oper2;


                // Create the new node to add

                newitem = new COperandStackItem;
                newitem->Type = OPERAND_NODE;
                newitem->pNode = new COperationNode;
                newitem->pNode->Operator = thisoper;
                

                // If the current operator is one with a single operand then only work with
                // the left side of the operation on the new node

                if (thisoper == OPERATOR_SQUAREROOT || thisoper == OPERATOR_SINE || thisoper == OPERATOR_COSINE || thisoper == OPERATOR_TANGENT)
                    {

					// Remove the first operand, which should be a constant 1 

                    item = operandstack->GetAt(operandpos);
					operandstack->RemoveAt(operandpos);
                    delete item;


					// Get the second operand, which is the one to work with

					item = operandstack->GetAt(operandpos);


                    switch(item->Type)
                        {
                        case OPERAND_CONSTANT:
                            newitem->pNode->LeftConstant    = item->Constant;
                            newitem->pNode->LeftType        = OPERAND_CONSTANT;
                            break;

                        case OPERAND_VARIABLE:
                            newitem->pNode->LeftType        = OPERAND_VARIABLE;
                            break;

                        case OPERAND_NODE:
                            newitem->pNode->pLeftChild      = item->pNode;
                            newitem->pNode->LeftType        = OPERAND_NODE;
                            break;
                        }
                 
                    // Delete the old node

                    operandstack->RemoveAt(operandpos);
                    delete item;


                    // Insert the new operand node

                    operandstack->InsertAt(operandpos, newitem);

                    operandpos++;
                    }

                // Otherwise if the current operator is one with two operands then work with
                // the left side and right side of the operation on the new node

                else
                    {

                    // Left side 

                    item = operandstack->GetAt(operandpos);

                    switch(item->Type)
                        {
                        case OPERAND_CONSTANT:
                            newitem->pNode->LeftConstant    = item->Constant;
                            newitem->pNode->LeftType        = OPERAND_CONSTANT;
                            break;

                        case OPERAND_VARIABLE:
                            newitem->pNode->LeftType        = OPERAND_VARIABLE;
                            break;

                        case OPERAND_NODE:
                            newitem->pNode->pLeftChild      = item->pNode;
                            newitem->pNode->LeftType        = OPERAND_NODE;
                            break;
                        }

                    // Delete the old node

                    operandstack->RemoveAt(operandpos);
                    delete item;


                    // Right side

                    item = operandstack->GetAt(operandpos);

                    switch(item->Type)
                        {
                        case OPERAND_CONSTANT:
                            newitem->pNode->RightConstant    = item->Constant;
                            newitem->pNode->RightType        = OPERAND_CONSTANT;
                            break;

                        case OPERAND_VARIABLE:
                            newitem->pNode->RightType        = OPERAND_VARIABLE;
                            break;

                        case OPERAND_NODE:
                            newitem->pNode->pRightChild      = item->pNode;
                            newitem->pNode->RightType        = OPERAND_NODE;
                            break;
                        }


                    // Delete the old node

                    operandstack->RemoveAt(operandpos);
                    delete item;


                    // Insert the new operand node

                    operandstack->InsertAt(operandpos, newitem);
                    }



                // Remove the operator from the stack

                operatorstack->RemoveAt(operatorpos);
                }
            else
                {
                operatorpos++;
                operandpos++;
                }
            }
        }


    return TRUE;
    }



/**************************************************************************************

OPERATION NODE

***************************************************************************************/





void COperationNode::GetValue(float variable, float * retval, BOOL * retvalgood)
    {

    //////////////////////////////////////////////////////////////
    //                                                          //
    // Used to get a value of an operation node using recursion //
    //                                                          //
    //////////////////////////////////////////////////////////////


    float leftval[2];
    float rightval[2];
    BOOL leftgood[2];
    BOOL rightgood[2];


    // Get the left operand value of the operation

    leftgood[0]     = TRUE;
    rightgood[0]    = TRUE;
    leftgood[1]     = TRUE;
    rightgood[1]    = TRUE;


    switch(LeftType)
        {
        case OPERAND_NODE:
            pLeftChild->GetValue(variable, leftval, leftgood);
            break;

        case OPERAND_CONSTANT:
            leftval[0]  = LeftConstant;
            leftval[1]  = LeftConstant;
            leftgood[0] = TRUE;
            leftgood[1] = TRUE;
            break;

        case OPERAND_VARIABLE:
            leftval[0] = variable;
            leftval[1] = variable;
            leftgood[0] = TRUE;
            leftgood[1] = TRUE;
            break;
        }



    // Get the right operand value of the operation

    switch(RightType)
        {
        case OPERAND_NODE:
            pRightChild->GetValue(variable, rightval, rightgood);
            break;

        case OPERAND_CONSTANT:
            rightval[0]  = RightConstant;
            rightval[1]  = RightConstant;
            rightgood[0] = TRUE;
            rightgood[1] = TRUE;
            break;

        case OPERAND_VARIABLE:
            rightval[0] = variable;
            rightval[1] = variable;
            rightgood[0] = TRUE;
            rightgood[1] = TRUE;
            break;
        }  


    for (int i = 0; i < 2; i++)
        {
        if (leftgood[i] && rightgood[i])
            {
            switch(Operator)
                {
                case OPERATOR_EXPONENT:
                    retval[i]       = pow(leftval[i], rightval[i]); 
                    retvalgood[i]   = TRUE;
                    break;


                case OPERATOR_MULTIPLY:
                    retval[i]       = leftval[i] * rightval[i];
                    retvalgood[i]   = TRUE;
                    break;


                case OPERATOR_DIVIDE:
                    if (rightval[i] != 0.0f)
                        {
                        retval[i]       = leftval[i] / rightval[i];
                        retvalgood[i]   = TRUE;
                        }
                    else
                        {
                        retvalgood[i] = FALSE;
                        }
                    break;


                case OPERATOR_ADD:
                    retval[i]       = leftval[i] + rightval[i];
                    retvalgood[i]   = TRUE;
                    break;


                case OPERATOR_SUBTRACT:
                    retval[i]       = leftval[i] - rightval[i];
                    retvalgood[i]   = TRUE;
                    break;


                case OPERATOR_SQUAREROOT:
                    if (leftval[i] >= 0)
                        {
                        retval[0]       = sqrtf(leftval[i]);
                        retval[1]       = -retval[0];
                        retvalgood[0]   = TRUE;
                        retvalgood[1]   = TRUE;
                        return;
                        }
                    else
                        {
                        retvalgood[i] = FALSE;
                        }
                    break;

                case OPERATOR_SINE:
                    retval[0]       = sinf(leftval[0]);
                    retval[1]       = sinf(leftval[1]);
                    retvalgood[0]   = TRUE;
                    retvalgood[0]   = TRUE;
                    break;

                case OPERATOR_COSINE:
                    retval[0]       = cosf(leftval[0]);
                    retval[1]       = cosf(leftval[1]);
                    retvalgood[0]   = TRUE;
                    retvalgood[0]   = TRUE;
                    break;

                case OPERATOR_TANGENT:
                    retval[0]       = tanf(leftval[0]);
                    retval[1]       = tanf(leftval[1]);
                    retvalgood[0]   = TRUE;
                    retvalgood[0]   = TRUE;
                    break;
                }
            }
        else
            {
            retvalgood[i] = FALSE;
            }
        }
    }





/*******************************************************************

TOKEN ARRAY

********************************************************************/




void CTokenArray::Add(int type, float value)  
    { 

    ////////////////////////////////////////////
    //                                        //
    // Used to add a token to the token array //
    //                                        //
    ////////////////////////////////////////////


    // If all tokens available are in use, just return

    if (m_NumTokens >= MAX_TOKENS) 
        return; 
    

    // Set the new token type and value

    m_Token[m_NumTokens].Type = type; 
    m_Token[m_NumTokens].Value = value; 
    

    // Increment the token count

    m_NumTokens++; 
    }




void CTokenArray::Insert(int pos, int type, float value)
    {

    /////////////////////////////////////////////////
    //                                             //
    // Used to insert a token into the token array //
    //                                             //
    /////////////////////////////////////////////////


    // If all tokens available are in use, just return

    if (m_NumTokens >= MAX_TOKENS && pos >= 0 && pos < m_NumTokens) 
        return; 
    

    // Offset the tokens after the position inserted to

    memcpy(&m_Token[pos + 1], &m_Token[pos], sizeof(CToken) * (m_NumTokens - pos));


    // Set the new token type and value

    m_Token[pos].Type = type; 
    m_Token[pos].Value = value; 
    

    // Increment the token count

    m_NumTokens++; 
    }




int CTokenArray::GetType(int pos)
    {

    /////////////////////////////////////////////////////////////
    //                                                         //
    // Used to get the type of a token at a specified position //
    //                                                         //
    /////////////////////////////////////////////////////////////


    if (pos < 0 || pos >= m_NumTokens)
        return OPERAND_NONE;

    return m_Token[pos].Type;
    }




float CTokenArray::GetValue(int pos)
    {

    //////////////////////////////////////////////////////////////
    //                                                          //
    // Used to get the value of a token at a specified position //
    //                                                          //
    //////////////////////////////////////////////////////////////


    if (pos < 0 || pos >= m_NumTokens)
        return 0.0f;

    return m_Token[pos].Value;
    }



CToken * CTokenArray::GetToken(int pos)
    {

    //////////////////////////////////////////////////////////////
    //                                                          //
    // Used to get a pointer to a token at a specified position //
    //                                                          //
    //////////////////////////////////////////////////////////////


    if (pos < 0 || pos >= m_NumTokens)
        return NULL;

    return &m_Token[pos];
    }
