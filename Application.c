#include"Application.h"
#include"common_types.h"
#include"Card.h"
#include"Terminal.h"
#include <stdio.h>
#include"Server.h"
#include <stdlib.h>
#include <string.h>

#define NO_OF_TRIALS 2
#define SUCCESS 1
#define FAIL 0





int main(void)
{
	//if (appStart() == FAIL)
	//{
	//	for (uint8_t i = 0; i < NO_OF_TRIALS; i++)
	//	{
	//		printf("%d Trial(s) left \n", NO_OF_TRIALS - i);
	//		appStart();

	//	}
	//}

	//else
	//{
	//	return 0;
	//}

	appStart();


	return 0;
}


void appStart(void)
{
	ST_cardData_t myCardData;
	ST_terminalData_t myTerminal;
	ST_accountsDB_t ReferenceAccount;
	EN_cardError_t cardNameReturn = 0xFF, cardDateReturn = 0xFF, cardPanReturn;
	EN_terminalError_t ExpiredReturn ,SETMaxAmountRet,BelowMaxRet,TransAmountRet;
	EN_transState_t TransactionState;
	/****************************************  Step 1 ****************************************************/
		/****************************************  get card data from CARD module functions ******************************************/
	
	printf("Please input name on the card between 20 and 24 characters\n");
	cardNameReturn = getCardHolderName(&myCardData);


	/*implementing the getcardholder name function we should add some printf functions to be able to interface
		with the user so we can get the input
		there are two options, 1 input name is correct return is CARD_OK and there are errors where he needs to try again
		so we call the function appStart Again*/

		if (cardNameReturn == WRONG_NAME)
		{
			printf("Name should be between 20 and 24 letters try again! \n");
			//return FAIL;
			return;

		}
		else if (cardNameReturn == CARD_OK)
		{	
			printf("Name saved \n");

		}
		else {
			printf("ERROR in card module implementing the getcard name function\n");
		}

		/****************************************  Get Expiry date function  ****************************************************/
		/*The application is  getting card info is getting the card expiry date : we have 2 expected outputs date
		is uptodate and less than transaction date or date passed the transaction date which will result in failure of the transaction*/

	printf("Please input the card expiry date  in format mm/yy \n");

	cardDateReturn = getCardExpiryDate(&myCardData);


	if (cardDateReturn == WRONG_EXP_DATE)
	{
		printf("Wrong format please try again\n");
		return;
		//return FAIL;

	}


	else if (cardDateReturn == CARD_OK)
	{
		//printf("Card expiry date saved successfuly \n");

	}

	else
	{
		printf("ERROR in card module implementing the get expiry date  function\n");
	}


	/****************************************  Get PAN function ****************************************************/
	/*The application gets the primary account number PAN should be from 16 to 19 numeric characters*/

	printf("Please input Primary Account Number (PAN)  16 to 19 numbers \n");

	cardPanReturn = getCardPAN(&myCardData);

//	printf(" PAN RETURN =%d \n", cardPanReturn);

	if (cardPanReturn == CARD_OK)
	{
		printf("PAN saved successfuly \n");

	}
	else if (cardPanReturn == WRONG_PAN)
	{
		printf("Wrong format please try again\n");
				return ;



	}




	else
	{
		printf("ERROR in card module implementing the PAN function\n");
	}

		/****************************************  Step 2 ****************************************************/
		/************************************ Terminal functions ****************************************************/

	 /*get transaction date and check if card is expired by calling terminal module functions*/
	//
	getTransactionDate(&myTerminal);
	//printf("current date = %d \n",myTerminal.transactionDate_totalmonths);


	switch (isCardExpired(&myCardData, &myTerminal))
	{
	case TERMINAL_OK :
		printf("Valid expiry date !\n");

		break;
		
	case EXPIRED_CARD:
	
	printf("card is Expired try another card !\n");
			//return FAIL;
	return;

		break;
	
	default :
	
	printf("ERROR in TERMINAL module implementing the  expiry date  function\n");
	break;
	
	}

/*********************************   enter max amount   ***************************************************/
printf("Enter max transaction amount !\n");
SETMaxAmountRet= setMaxAmount(&myTerminal);

if (SETMaxAmountRet == INVALID_MAX_AMOUNT)
{
	
	printf("Invalid max amount !\n");
	return;

}
else if(SETMaxAmountRet==TERMINAL_OK)
{

	printf("Max amount is = %g  \n", myTerminal.maxTransAmount);

}
else
{

	printf("ERROR in TERMINAL module implementing the  set max amount  function\n");

}
/*********************************   enter transaction amount   ***************************************************/

printf("Enter  transaction amount !\n");
TransAmountRet = getTransactionAmount(&myTerminal);

if (TransAmountRet == INVALID_AMOUNT)
{

	printf("Invalid amount !\n");
	return;
}
else if (TransAmountRet == TERMINAL_OK)
{

	printf("Transaction Amount is = %g  \n", myTerminal.transAmount);

}
else
{

	printf("ERROR in TERMINAL module implementing the  set max amount  function\n");

}
/*********************************   call is bellow max to check   ***************************************************/

BelowMaxRet = isBelowMaxAmount(&myTerminal);

if (BelowMaxRet == EXCEED_MAX_AMOUNT) 
{
	printf("Exceeded max amount\n");
	return;
}
else if (BelowMaxRet == TERMINAL_OK)
{

	printf("Valid amount  \n");

}
else
{

	printf("ERROR in TERMINAL module implementing the is below amount  function\n");

}
///****************************************  Step 3 ****************************************************/
///************************************ Server functions ****************************************************/

ST_transaction_t myTransaction = {
myCardData, myTerminal


};


TransactionState = recieveTransactionData(&myTransaction);

if (TransactionState == APPROVED)
{
	printf("Transaction Approved \n");




}
else if (TransactionState == FRAUD_CARD)
{
	printf("Fraud Card Account not found \n");

}

else if (TransactionState == DECLINED_INSUFFECIENT_FUND)
{
	printf("Declined Insuffecient funds \n");


}

else if (TransactionState == DECLINED_STOLEN_CARD)
{
	printf("Declined STOLEN CARD	 \n");


}

else if (TransactionState == INTERNAL_SERVER_ERROR)
{


}


else 
{

}

return;

}