/* 
 * Message Queue Multicast Implementation
 * CS551 Group 21  
 * 
 * Multicast Message Queue Kernel Functions and Structures
 * 
 */
 #include <minix/libmsgque.h>
 #include "msgque_const.h"

/* This structure hold all MQ users who are registered
 * 
 */
struct MQUser {   /* Dynamically allocated */
	int messageNo; 			 /* This is the last message recieve used */
	int procNr; 			 /* Receiver's process number */
	int state;				 /* Blocked or Active */
	int type; 				 /* Sender or reciever = has meaning only with 'state' */
	struct MQUser *next; /* If many are waiting to read message */
};

 /* 
  * Linked list maintaining all the message posted by msend
  * 
  * Elements are removed by mrecv() if there are no more
  * recievers pending to read the message.
  * 
  * There exist maximum of MQ_MAX_MESSAGES MsgNode per MQueue.
  * 
  */
struct MsgNode {
	int messageNo;
	char *message;   
	struct MsgNode *next;
};
  
struct MQueue {	  
	int token;	/* Unique identifier for this message queue, 
	             * user gives this */
	int queueLen;
	struct MsgNode *msgHead; 
	struct MQUser *userHead;
};
#define INVALID_MQ( mq, tok ) (mq < mQueue[0] || mq > mQueue[MQ_MAX_MSGQUES] || mq->token != tok )
	
 /* 
  * struct MsgQues holds list of all message queue that are 
  * created by applications.
  * 
  * Data structure that is initialized by PM when it starts.
  * queues[*].token should be initialized with MQ_FREE, if its free.
  * 
  * There can only be MQ_MAX_MSGQUES created in Minix
  * 
  * &queue[*].token with MQ_FREE is returned to user in MsgQue->queue by
  * minit(). Future calls to msend(), mrecv() and mclose() will
  * use MsgQue->queue to get its MQueue.
  * 
  */
 
 struct MQueues {
	 struct MQueue queues[MQ_MAX_MSGQUES]; /* 16 * MQ_MAX_MSGQUES bytes */
 };



 

