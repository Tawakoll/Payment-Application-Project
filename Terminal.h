#ifndef TERMINAL_H
#define TERMINAL_H

#include"Card.h"
#include "common_types.h"
typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint16_t transactionDate_totalmonths;
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
	TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

void getTransactionDate(ST_terminalData_t* termData); //adjusting to void because we return nothing since 
//this function will get data from local time and store it into the term data struct only no need for return
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);



#endif