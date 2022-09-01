#include "Terminal.h"
#include"Card.h"
#include<time.h>
#include <stdio.h>

/*


typedef enum EN_terminalError_t
{
	TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;



*/

void getTransactionDate(ST_terminalData_t* termData) 
{	//gets transaction live date from local time functions and saves into the terminal struct
	//date is NOT input by user

/*getting realtime date referenced from the source mentioned bellow*/
//for reference code please read more on
//https ://reactgo.com/c-program-current-date-time/#:~:text=In%20C%20language%2C%20we%20can,()%20and%20ctime()%20functions.

	time_t t = time(NULL);
	struct tm* tm = localtime(&t);

	termData->transactionDate_totalmonths = (tm->tm_year - 100) * 12 + tm->tm_mon + 1;
	//note : tm->tm_year gets year = 122 if year is 2022 for example so we minus 100 and multiply
	//		by 12 to get months










}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
//pointers that access 2 bytes for an input "05/25"
// to access the parts of the string the i want the month 05/ and then the year /25

	uint8_t* month_s[2] = { NULL }, * year_s[2] = { NULL };

	/******************************************************************/

	int16_t month_i = 0, year_i = 0;
	int32_t total_months = 0, current_total_months = 0;
	current_total_months = termData->transactionDate_totalmonths;

	for (uint8_t i = 0; i < 2; i++)
	{
		month_s[i] = cardData->cardExpirationDate[i];
		year_s[i] = cardData->cardExpirationDate[i+3]; // to take the point to the char after the month and the / value, example "05/25" it now is pointing to the address of 2 
	}
	month_i = atoi(month_s) * 10 + atoi(month_s + 1);
	
	year_i = atoi(year_s) * 10 + atoi(year_s + 1);

	year_i = year_i * 12; // to calculate total months
	

	
	// i am proud of this ! array of pointer to char month_s is accessing address 0 of the array and transofroming 
	//it by atoi func to integer multiply by 10 since its in tens then adds the seconds month_s+1 accessing address 1 of the array and transofrming it to int 
	//month_i now has the month variable that we can subtract from the transaction date 


/*
	(total_months - current_total_months)<0 checks if the difference is negative means the card is expired!
	since total months represents the card's input date while current total months represents current
	transaction date
*/
	total_months = year_i + month_i;

	
	if ((total_months - current_total_months) < 0) {

		return EXPIRED_CARD;
	}
	else 
	{
		
			return TERMINAL_OK;
		
	

	}
	
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
 {
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	else 
	{
		return TERMINAL_OK;
	}
	
 }

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	termData->maxTransAmount = 20000;

	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}

}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->maxTransAmount < termData->transAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}
