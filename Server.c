#include"Server.h"
#include <string.h>

ST_accountsDB_t accounts[255] = {

	{2000.0, RUNNING,"8989374615436851"},
	{12000.0, RUNNING,"1234574615436851"},
	{500.0, RUNNING,"786902615456127"},
	{100000.0, BLOCKED,"5807007076043875"},
	{1000000.0, RUNNING,"7869007076043875"},
};

ST_transaction_t transactions[255] = { 0 };
ST_accountsDB_t server_account;
uint8_t g_account_index,g_transactions_index = 0;
uint32_t g_transactionSeqNo=0;
EN_transState_t g_transState;

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t *accountRefrence) 
{	
	uint8_t *DBaddress,  *targetPANadd = cardData->primaryAccountNumber;
	uint8_t i = 0, CMPreturn = 5;
	bool_t foundPANFlag = FALSE;
	//printf("%s\n", accounts[i].primaryAccountNumber);
	//printf("%s\n", targetPANadd);
	for( i=0;i<255;i++)
	{
		CMPreturn=strncmp(cardData->primaryAccountNumber, accounts[i].primaryAccountNumber,16);
		bool_t identical_flag = TRUE;


		//
		if (CMPreturn == 0)
		{
			
			accountRefrence->balance = accounts[i].balance;
			
			accountRefrence->state = accounts[i].state;

			g_account_index=i;
			//printf("in isvalid function %d balance = %f\n" , i, accounts[i].balance);
			foundPANFlag = TRUE;
			break;
			
		}
		
	}
	//printf(" compare return = %d \n", CMPreturn);
	//printf(" found flag = %d \n", foundPANFlag);

		
	if (foundPANFlag==TRUE) 
	{
	
		return SERVER_OK;

	
	}


	else 
	{
		return ACCOUNT_NOT_FOUND;
	}

}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {

	if (termData->transAmount > server_account.balance)
	{
		return LOW_BALANCE;
	}
	else
	{
		return SERVER_OK;
	}
}


EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) 
{
	if (accountRefrence->state == RUNNING)
{	
		return SERVER_OK;
}
else 
{
		return BLOCKED_ACCOUNT;
}
	

	

}


EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	g_transactions_index++;
	g_transactionSeqNo++;
	transactions[g_transactions_index].cardHolderData = transData->cardHolderData;
	transactions[g_transactions_index].terminalData = transData->terminalData;
	transactions[g_transactions_index].transactionSequenceNumber = g_transactionSeqNo;
	transactions[g_transactions_index].transState = g_transState;


	printf("in saveTransaction function \n");
	printf("Transaction sequence: %d  \n", transactions[g_transactions_index].transactionSequenceNumber);


	
}

EN_transState_t recieveTransactionData(ST_transaction_t* transData) 
{
	EN_transState_t isValidAccReturn = isValidAccount(&transData->cardHolderData, &server_account);
	if (isValidAccReturn == ACCOUNT_NOT_FOUND)
	{
		//printf("in rec trans data function account not found \n");
		g_transState = FRAUD_CARD;
	
	}
	else 
	{
		EN_serverError_t amountAvailableRet =isAmountAvailable(&transData->terminalData);

		if (amountAvailableRet == LOW_BALANCE)
		{
			g_transState= DECLINED_INSUFFECIENT_FUND;
		
		}
		else
		{
			EN_serverError_t blockedRetrun = isBlockedAccount(&server_account);
				if (blockedRetrun == BLOCKED_ACCOUNT)
				{
					g_transState= DECLINED_STOLEN_CARD;
				
				}
			

				else
				{
					

					printf("Account balance before transaction = %g\n", accounts[g_account_index].balance);
					accounts[g_account_index].balance = accounts[g_account_index].balance - transData->terminalData.transAmount;
					printf("Account balance AFTER transaction = %g\n", accounts[g_account_index].balance);

					g_transState = APPROVED;



				}
			


		}


	}
	
	saveTransaction(transData);
	return g_transState;
	


}
