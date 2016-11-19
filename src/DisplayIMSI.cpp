/*
* ============================================================================
*  Part of  : Mobile Tracker
*  Created  : 12.05.2009 by Kishoj, Meena
*  Implementation notes:
*     This portion of code is used for extracting IMSI number and IMEI number.
*     It demonstrate the use of active objects.
*  Version  : 1.062
*  Copyright: 062-BCT  Mobile Tracker Group
* ============================================================================
*/


#include "DisplayIMSI.h"
#include <eikenv.h>
#include <mobinfotypes.h>
#include <mobileinfo.h>
#include <plpvariant.h>
#include <stringloader.h>
#include <aknnotewrappers.h>//for confirmation note

CDisplayIMSI* CDisplayIMSI::NewL()
	{
	CDisplayIMSI* self = new (ELeave) CDisplayIMSI();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CDisplayIMSI::CDisplayIMSI()
: CActive(0)
	{	
	CActiveScheduler::Add(this);
	}

void CDisplayIMSI::ConstructL()
	{
	iMobileInfo = CMobileInfo::NewL();
	User::LeaveIfError(iTimer.CreateLocal());	//Create the timer object (= Asynch. Service Provider)
	iTimer.After(aStatus,10);	//asynchronous function
	iMobileInfo->GetIMSI(iImsi, aStatus);
	User::WaitForRequest(aStatus); // enable thread to wait until the timer has completed. 
	//Timer request completes when aStatus != KRequestPending, not when the function returns
	SetActive();	// to inform the Active Scheduler that we’re waiting for a request
	}

CDisplayIMSI::~CDisplayIMSI()
	{
	Cancel();
	iMobileInfo->CancelGetIMSI();
	iTimer.Close();
	delete iMobileInfo;
	}
	
TMobileIMEI  CDisplayIMSI::getImsi()
	{	
	iMobileInfo->CancelGetIMSI();
	return iImsi;
	}


TMobileIMEI  CDisplayIMSI::getImei()
#if !defined(__WINS__) && !defined( __WINSCW__ ) 
// This only works on target machine
// This code is exclusively for the target machine i.e.Mobile
	{
	TPlpVariantMachineId imei;
	PlpVariant::GetMachineIdL(imei);
	iImei.Copy(imei);
	return iImei;
	}

#else
//It is possible to write code exclusively for the emulator.
// Return a fake IMEI when working on emulator.
	{
	_LIT(KEmulatorImei, "000000000000000");
	iImei.Copy(KEmulatorImei);
	return iImei;
	}
#endif

// from CActive
void CDisplayIMSI::RunL()
{	}

void CDisplayIMSI::DoCancel()
	{
	iTimer.Cancel();
	iMobileInfo->CancelGetIMSI();
	}
