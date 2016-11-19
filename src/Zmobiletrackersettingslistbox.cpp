/*
* ============================================================================
*  Part of  : Mobile Tracker
*  Created  : 12.05.2009 by Kishoj, Meena
*  Implementation notes:
*     This portion helps to create listbox for setting list view.
*  Version  : 1.062
*  Copyright: 062-BCT  Mobile Tracker Group
* ============================================================================
*/


#include "ZMobileTrackerinformationandsettings.h"
#include "ZMobileTrackersettingslistbox.h"
#include "nac.hrh"
#include "DisplayIMSI.h"

CZMobileTrackerSettingListbox::CZMobileTrackerSettingListbox(
    CZMobileTrackerInformationAndSettings& aSettings) : iSettings (aSettings)
    {	idisplayImsi = CDisplayIMSI::NewL();
		_LIT(KDestiny, "mobile");
		iPassword.Copy(KDestiny); 

		iSMSMess.Copy(_L("Kishoj's mobile is lost"));
		_LIT(KIMSI, "429010030658969");
		iIMSI.Copy(KIMSI);
		TBuf<15> KImei(idisplayImsi->getImei());
		iIMEI.Copy(KImei);
    }

CAknSettingItem* CZMobileTrackerSettingListbox::CreateSettingItemL(TInt aIdentifier)
    {
    switch (aIdentifier)
        {
        case EMobileTrackerPlayerNameText:
            return new (ELeave) CAknTextSettingItem(
                aIdentifier, iSettings.Addr());
		case EDestinationSettingItem:
            return new (ELeave) CAknTextSettingItem(
                aIdentifier, iSettings.PlayerName());//iDestiny);
        case EMobileTrackerPlayerFirstBinary:
            return new (ELeave) CAknBinaryPopupSettingItem(
                aIdentifier, iSettings.HumanPlayFirst());
		case EMyPasswordSettingItem:
			return new (ELeave) CAknPasswordSettingItem(
                aIdentifier, CAknPasswordSettingItem::EAlpha,iPassword);
		case EIMSISettingItem:
            return new (ELeave) CAknTextSettingItem(
                aIdentifier, iIMSI);
		case EIMEISettingItem:
            return new (ELeave) CAknTextSettingItem(
                aIdentifier, iIMEI);
		default:
			return NULL;
        }
    }

void CZMobileTrackerSettingListbox::HandleResourceChange(TInt aType)
    {

    }

void CZMobileTrackerSettingListbox::SizeChanged()
    {	if (ListBox()) 
        {
        ListBox()->SetRect(Rect());
        }
    }
