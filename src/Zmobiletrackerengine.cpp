/*
* ============================================================================
*  Part of  : Mobile Tracker
*  Created  : 12.05.2009 by Kishoj, Meena
*  Implementation notes:
*     Initial content was generated by Series 60 Application Wizard.
*  Version  : 1.062
*  Copyright: 062-BCT  Mobile Tracker Group
* ============================================================================
*/

#include "ZMobileTrackerengine.h"
#define TIMEWAIT 1000000
CZMobileTrackerEngine* CZMobileTrackerEngine::NewLC(TPlayer aHumanPlayer)
	{
	CZMobileTrackerEngine* self = new(ELeave) CZMobileTrackerEngine (
		aHumanPlayer);
	CleanupStack::PushL (self);
	self->ConstructL();
	return self;
	}
CZMobileTrackerEngine* CZMobileTrackerEngine::NewL(TPlayer aHumanPlayer)
	{
	CZMobileTrackerEngine* self = CZMobileTrackerEngine::NewLC(
		aHumanPlayer);
	CleanupStack::Pop();
	return self;
	}
CZMobileTrackerEngine::~CZMobileTrackerEngine()
	{
	Cancel();
	}
void CZMobileTrackerEngine::SetObserver(MObserver* aObserver)
	{
	iObserver  = aObserver;
	}
void CZMobileTrackerEngine::StartNewGame(TPlayer aHumanPlayer)
	{
	}


TBool CZMobileTrackerEngine::CanMove()
	{
	
	return EFalse;
	}

TBool CZMobileTrackerEngine::MakeHumanMove (TUint aRow, TUint aColumn)
	{
	

	return ETrue;
	}

TBool CZMobileTrackerEngine::MakeComputerMove()
	{

	return ETrue;
	}


void CZMobileTrackerEngine::RunL()
	{

	}

CZMobileTrackerEngine::CZMobileTrackerEngine (TPlayer aHumanPlayer) :
	CTimer (CActive::EPriorityStandard), iObserver (NULL),
	iHumanPlayer (aHumanPlayer), iPlayerToGo (aHumanPlayer)
	{
	
	}

void CZMobileTrackerEngine::ConstructL()
	{
	
	}
