/*
* ============================================================================
*  Part of  : Mobile Tracker
*  Created  : 12.05.2009 by Kishoj, Meena
*  Implementation notes:
*     This class helps to create listbox for setting list view.
*  Version  : 1.062
*  Copyright: 062-BCT  Mobile Tracker Group
* ============================================================================
*/



#ifndef __ZMobileTrackerSETTINGSLISTBOX_H__
#define __ZMobileTrackerSETTINGSLISTBOX_H__

// INCLUDES
#include <AknSettingItemList.h>
#include "DisplayIMSI.h"

// FORWARD DECLARATIONS
class CZMobileTrackerInformationAndSettings;
class CDisplayIMSI;

// CLASS DECLARATION

/**
*  CZMobileTrackerSettingListbox.
*  
*/
class CZMobileTrackerSettingListbox : public CAknSettingItemList 
    {
    public: // Constructors and destructor
	
        /**
        * CZMobileTrackerSettingListbox
        * C++ default constructor.
        */
        CZMobileTrackerSettingListbox(
            CZMobileTrackerInformationAndSettings& aSettings);

    public: // Functions from base classes
		

        /**
        * From CAknSettingItemList, CreateSettingItemL.
        */
        virtual CAknSettingItem* CreateSettingItemL(TInt identifier);

    private: // Functions from base classes

        /**
        * From CoeControl, HandleResourceChange.
        */
        virtual void HandleResourceChange(TInt aType);

        /**
        * From CoeControl, SizeChanged.
        */
        virtual void SizeChanged();

    private: // Data

        CZMobileTrackerInformationAndSettings& iSettings;

        TBool iPlayerType;
		TBuf<12> iPlayerName;
		TBool iPlayFirst;
		TBool iCross;
		TBuf<12> iPassword;
		TBuf<11> iDestiny;
		TBuf<15> iIMSI;
		TBuf<15> iIMEI;
		TBuf<159> iSMSMess;
		CDisplayIMSI* idisplayImsi;
		
    };

#endif // __CZMobileTrackerSETTINGSLISTBOX_H__

// End of File
