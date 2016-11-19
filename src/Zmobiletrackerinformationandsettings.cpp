/*
* ============================================================================
*  Part of  : Mobile Tracker
*  Created  : 12.05.2009 by Kishoj, Meena
*  Implementation notes:
*      This portion is used for file handling to insert and retrieve user information
*  Version  : 1.062
*  Copyright: 062-BCT  Mobile Tracker Group
* ============================================================================
*/

#include <s32file.h>
#include "ZMobileTrackerinformationandsettings.h"

CZMobileTrackerInformationAndSettings::CZMobileTrackerInformationAndSettings() 
{	_LIT(KSMSADDR, "9841599938");
	iPlayerName.Copy(KSMSADDR); 
}

void CZMobileTrackerInformationAndSettings::SetPlayerName (const TPlayerName& aPlayerName)
	{	iPlayerName = aPlayerName;}
CZMobileTrackerInformationAndSettings::TPlayerName& CZMobileTrackerInformationAndSettings::PlayerName()
	{	return iPlayerName;}
const CZMobileTrackerInformationAndSettings::TPlayerName& CZMobileTrackerInformationAndSettings::PlayerName() const
	{	return iPlayerName;}


void CZMobileTrackerInformationAndSettings::SetAddr (const TPlayerName& aDest)
	{	iDest = aDest;}
CZMobileTrackerInformationAndSettings::TPlayerName& CZMobileTrackerInformationAndSettings::Addr()
	{	return iDest;}
const CZMobileTrackerInformationAndSettings::TPlayerName& CZMobileTrackerInformationAndSettings::Addr() const
	{	return iDest;}




void CZMobileTrackerInformationAndSettings::SetHumanPlayFirst (TBool aPlayFirst)
	{	iPlayFirst = aPlayFirst;}
TBool& CZMobileTrackerInformationAndSettings::HumanPlayFirst()
	{	return iPlayFirst;}
TBool CZMobileTrackerInformationAndSettings::HumanPlayFirst() const
	{	return iPlayFirst;}

void CZMobileTrackerInformationAndSettings::SetHumanTypeCross (TBool aPlayTypeCross)
	{	iPlayTypeCross = aPlayTypeCross;}
TInt& CZMobileTrackerInformationAndSettings::HumanTypeCross()
	{	return iPlayTypeCross;}
TInt CZMobileTrackerInformationAndSettings::HumanTypeCross() const
	{	return iPlayTypeCross;}


void CZMobileTrackerInformationAndSettings::ExternalizeL (RWriteStream& aStream) const
	{	//aStream << iDest;
		aStream << iPlayerName;
		
		aStream.WriteInt32L (iPlayFirst);
		aStream.WriteInt32L (iPlayTypeCross);
		//	aStream.WriteInt32L (iHumanWins);
		aStream.WriteInt32L (iHumanLosses);
		
	}
void CZMobileTrackerInformationAndSettings::InternalizeL (RReadStream& aStream)
	{	//aStream >> iDest;
		aStream >> iPlayerName;
		
		iPlayFirst = aStream.ReadInt32L();
		iPlayTypeCross = aStream.ReadInt32L();
		//iHumanWins = aStream.ReadInt32L();
		iHumanLosses = aStream.ReadInt32L();
	}

