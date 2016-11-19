/*
* ============================================================================
*  Part of  : Mobile Tracker
*  Created  : 12.05.2009 by Kishoj, Meena
*  Implementation notes:
*     This class is used for extracting IMSI number and IMEI number. 
*     It demonstrate the use of active objects.
*  Version  : 1.062
*  Copyright: 062-BCT  Mobile Tracker Group
* ============================================================================
*/


#ifndef __DISPLAYIMSI_H__
#define	__DISPLAYIMSI_H__

#include <e32base.h>
#include <mobinfotypes.h>
#include <mobileinfo.h>

//class CEikonEnv;

class CDisplayIMSI : public CActive
	{
public:
	// Construct/destruct
	static CDisplayIMSI* NewL();
	~CDisplayIMSI();
	TMobileIMEI getImsi();	
	TMobileIMEI getImei();
private:
	// Construct/destruct
	CDisplayIMSI();
	void ConstructL();

	// from CActive
	void RunL();	// Handle the timer event
	void DoCancel();	// Cancel the timer
public:
	TMobileIMEI iImei;
	TMobileIMSI iImsi;
	TRequestStatus aStatus;
	
private:
	RTimer iTimer;		// Symbian OS Asynchronous Service Provider
	CMobileInfo* iMobileInfo;
	};

#endif	// _CDISPLAYIMSI_H__