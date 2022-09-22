# Payment-Application-Project
This is a project done as a part of Udacity Embedded systems nano degree
This project simply simulates the payment process we go through when paying by card. There is a card module, terminal module, and server module.
The card module simply is a .c and .h files it gets the card data from the user. 
![Screenshot 2022-09-22 153715](https://user-images.githubusercontent.com/81693710/191762212-cf7b694f-c161-46d6-b239-18914e179b9d.png)


The terminal module performs some checking like is the card expired and then finaly the server module checks if the account is valid, is in the database and finally returns weather the transaction is accepted or declined.
Includes real time retrieval from to make sure that the card is not expired! This is by far the feature I am proud of the most because it wasn't clear at first but step by step I was able to implement what I had in mind
to take an input as a string "05/22" representing an expiray date then to perform a mathematical operation on this string and on the current date of the transaction.

