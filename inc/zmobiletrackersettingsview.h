/*
* ============================================================================
*  Part of  : Mobile Tracker
*  Created  : 12.05.2009 by Kishoj, Meena
*  Implementation notes:
*     This class creates the setting view of Mobile Tracker that contains setting adjustments.
*  Version  : 1.062
*  Copyright: 062-BCT  Mobile Tracker Group
* ============================================================================
*/



#ifndef __ZMobileTrackerSETTINGSVIEW_H__
#define __ZMobileTrackerSETTINGSVIEW_H__

// INCLUDES
#include <aknview.h>



// FORWARD DECLARATIONS
class CZMobileTrackerSettingListbox;


// CLASS DECLARATION
/**
*  CZMobileTrackerSettingsView view class.
*
*/
class CZMobileTrackerSettingsView : public CAknView
    {
    public:

        /**
        * NewL.
        * Two-phased constructor.
        * Construct a CZMobileTrackerSettingsView using two phase construction,
        * and return a pointer to the created object
        * @return A pointer to the created instance of CZMobileTrackerSettingsView
        */
        static CZMobileTrackerSettingsView* NewL();

        /**
        * ~CZMobileTrackerView
        * Virtual Destructor.
        */
        virtual ~CZMobileTrackerSettingsView();

    public: // Functions from base classes

        /**
        * From CAknView, Id.
        * Returns the ID of view.
        * @return The ID of view.
        */
        virtual TUid Id() const;

        /**
        * From CAknView, HandleCommandL.
        * Handles the commands.
        * @param aCommand Command to be handled.
        */
        virtual void HandleCommandL (TInt aCommand);
		
	
    private: // Functions from base classes

        /**
        * From CAknView, DoActivateL.
        * Creates the Container class object.
        * @param aPrevViewId Specified TVwsViewId.
        * @param aCustomMessageId Specified TUid.
        * @param aCustomMessage Specified custom message.
        */
        virtual void DoActivateL (const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId, const TDesC8& aCustomMessage);

        /**
        * From CAknView, DoDeactivate.
        * Deletes the Container class object.
        */
        virtual void DoDeactivate();

    private:

        /**
        * CZMobileTrackerSettingsView.
        * C++ default constructor.
        */
        CZMobileTrackerSettingsView();

        /**
        * ConstructL.
        * 2nd phase constructor.
        */
        void ConstructL();

    private: // Data

       CZMobileTrackerSettingListbox* iListBox;
	 
    };

#endif // __ZMobileTrackerSETTINGSVIEW_H__

// End of File

