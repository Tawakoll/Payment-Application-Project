
#include"Card.h"
#include<stdio.h>//to use standard c functions
#include <string.h>// to use strlen function
#include<stdlib.h>// using atoi function
#include<time.h>// to use time function to get date!
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)

{
	int32_t num_of_chars = 0;
	//declared as int data type because 
	//it carries the return of strlen function which returns int data type to avoid warnings
	
	
	fgets(cardData->cardHolderName, sizeof(cardData->cardHolderName), stdin);

	//gets(cardData->cardHolderName);

	num_of_chars = strlen(cardData->cardHolderName);



	if (num_of_chars < 20 || num_of_chars>24)
	{

		return WRONG_NAME;

	}
	else 
	{

		return CARD_OK;
	} 

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) 
{
	int32_t num_of_chars = 5;
	//declared as int data type because it carries the return of strlen function which returns int data type to avoid warnings


	
	gets(cardData->cardExpirationDate, sizeof(cardData->cardExpirationDate), stdin);
	num_of_chars = strlen(cardData->cardExpirationDate);
	if ( num_of_chars < 5 )
	{

		return WRONG_EXP_DATE;
	}
	
	else
	{

		return CARD_OK;
	}

	

}


EN_cardError_t getCardPAN(ST_cardData_t* cardData)
 {
	int32_t num_of_chars = 15; // int data type because it carries the return of strlen function which returns int data type to avoid warnings



	fgets(cardData->primaryAccountNumber, sizeof(cardData->primaryAccountNumber), stdin);

	

	num_of_chars = strlen(cardData->primaryAccountNumber);



	if (num_of_chars < 16 || num_of_chars>19)
	{

		return WRONG_PAN;

	}
	else
	{

		return CARD_OK;
	}

}