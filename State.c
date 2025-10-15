/****************************************************************************************************
| Author	| 	 Date	   |   Version	|				Description						|
|-----------|--------------|------------|-----------------------------------------------|
| bin.chen  | 2025/09/30   |	V1.0	|			Table-driven state machine			|
|-----------|--------------|------------|-----------------------------------------------| 	
****************************************************************************************************/

#include<stdio.h>
#include<string.h>

#define VERSION 2				  //Version Select


#if (VERSION == 1)

	#define S_MAX 3
	#define E_MAX 3

	typedef enum {S0, S1, S2} State;  //One-dimensional: State
	typedef enum {E0, E1, E2} Event;  //Two-dimensional: Event
	typedef void (*StaActFun)(State* _State, Event _Event);

	void Node_S0E0(State* pSta, Event eEve) { printf("Node_S0E0\n"); *pSta = S0; }  //*pSta = S0; For state switching, it can be modified
	void Node_S1E0(State* pSta, Event eEve) { printf("Node_S1E0\n"); *pSta = S1; }
	void Node_S2E0(State* pSta, Event eEve) { printf("Node_S2E0\n"); *pSta = S2; }

	void Node_S0E1(State* pSta, Event Eve) { printf("Node_S0E1\n"); *pSta = S1; }
	void Node_S1E1(State* pSta, Event Eve) { printf("Node_S1E1\n"); *pSta = S1; }
	void Node_S2E1(State* pSta, Event Eve) { printf("Node_S2E1\n"); *pSta = S2; }

	void Node_S0E2(State* pSta, Event Eve) { printf("Node_S0E2\n"); *pSta = S2; }
	void Node_S1E2(State* pSta, Event Eve) { printf("Node_S1E2\n"); *pSta = S2; }
	void Node_S2E2(State* pSta, Event Eve) { printf("Node_S2E2\n"); *pSta = S2; }

	StaActFun Table[S_MAX][E_MAX] = 
	{
		{ Node_S0E0, Node_S0E1, Node_S0E2 },
		{ Node_S1E0, Node_S1E1, Node_S1E2 },
		{ Node_S2E0, Node_S2E1, Node_S2E2 }
	};

	void StateMachine(State* pSta, Event eEve) 
	{
		if ((eEve >= E0) && (eEve <= E2) && (*pSta >= S0) && (*pSta <= S2)) //Prevent array out-of-bounds
		{
			Table[*pSta][eEve](pSta, eEve);
		}
	}

	int main(void)
	{
		State StateTest = 1;          //Limit:0-2
		StateMachine(&StateTest, E0);
		StateMachine(&StateTest, E1);

		return 0;
	}

#else if (VERSION == 2)
	typedef enum {S0, S1, S2, STATE_COUNT} State;  //One-dimensional: State
	typedef enum {E0, E1, E2, EVENT_COUNT} Event;  //Two-dimensional: Event

	typedef void (*StaActFun)(State* _State, Event _Event);

	void Node_S0E0(State* pSta, Event eEve) { printf("Node_S0E0\n"); *pSta = S0; }  //*pSta = S0; For state switching, it can be modified
	void Node_S1E0(State* pSta, Event eEve) { printf("Node_S1E0\n"); *pSta = S1; }
	void Node_S2E0(State* pSta, Event eEve) { printf("Node_S2E0\n"); *pSta = S2; }

	void Node_S0E1(State* pSta, Event Eve) { printf("Node_S0E1\n"); *pSta = S1; }
	void Node_S1E1(State* pSta, Event Eve) { printf("Node_S1E1\n"); *pSta = S1; }
	void Node_S2E1(State* pSta, Event Eve) { printf("Node_S2E1\n"); *pSta = S2; }

	void Node_S0E2(State* pSta, Event Eve) { printf("Node_S0E2\n"); *pSta = S2; }
	void Node_S1E2(State* pSta, Event Eve) { printf("Node_S1E2\n"); *pSta = S2; }
	void Node_S2E2(State* pSta, Event Eve) { printf("Node_S2E2\n"); *pSta = S2; }
	#define INIT_TABLE  \
	{ \
		{ Node_S0E0, Node_S0E1, Node_S0E2 }, \
		{ Node_S1E0, Node_S1E1, Node_S1E2 }, \
		{ Node_S2E0, Node_S2E1, Node_S2E2 }  \
	} //ºê¶¨Òå±í......You can add tables later

	StaActFun Table[STATE_COUNT][EVENT_COUNT] = INIT_TABLE;

	void StateMachine(State* pSta, Event eEve)
	{
		if ((eEve >= E0) && (eEve < EVENT_COUNT) && (*pSta >= S0) && (*pSta < STATE_COUNT))  //Prevent array out-of-bounds
		{
			Table[*pSta][eEve](pSta, eEve);
		}
		else
		{
			printf("Invalid state or event!\n");
		}
	}

	int main(void)
	{
		State StateTest = S1;  
		StateMachine(&StateTest, E0);  
		StateMachine(&StateTest, E1);  

		return 0;
	}

#endif