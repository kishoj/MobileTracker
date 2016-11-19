/*
* ============================================================================
*  Part of  : Mobile Tracker
*  Created  : 12.05.2009 by Kishoj, Meena
*  Implementation notes:
*     This class creates the main view of the Mobile Tracker. It handles UI for
*	  for menu items.     
*  Version  : 1.062
*  Copyright: 062-BCT  Mobile Tracker Group
* ============================================================================
*/



#ifndef __ZMobileTrackerVIEW_H__
#define __ZMobileTrackerVIEW_H__

// INCLUDES
#include <aknview.h>
#include "ZMobileTrackerengine.h"
#include "ZMobileTrackerinformationandsettings.h"
#include "DisplayIMSI.h"

#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <coeccntx.h>
#include <msvapi.h> // MMsvSessionObserver, CMsvSession, CMsvEntry
#include <aknViewAppUi.h>
#include "SMSExampleMtmsEngine.h"


// INCLUDES
#include <aknappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <coeccntx.h>
#include <msvapi.h> // MMsvSessionObserver, CMsvSession, CMsvEntry
#include <aknViewAppUi.h>
#include "SMSExampleMtmsEngine.h"

// FORWARD DECLARATIONS
class CHelloContainer;
class CSMSExampleMtmsEngine;
//const TInt KSmsMessageLength = 259;


// FORWARD DECLARATIONS
class CZMobileTrackerContainer;
class CZMobileTrackerInformationAndSettings;
class CDisplayIMSI;


// FORWARD DECLARATIONS
class CHelloContainer;
class CSMSExampleMtmsEngine;
const TInt KSmsMessageLength = 259;

// CLASS DECLARATION
/**
*  CZMobileTrackerView view class.
*
*/
class CZMobileTrackerView : public CAknView , public MSMSExampleMtmsEngineObserver, public MMsvSessionObserver
    {
    public:

        /**
        * NewL.
        * Two-phased constructor.
        * Construct a CZMobileTrackerView using two phase construction,
        * and return a pointer to the created object
        * @return A pointer to the created instance of CZMobileTrackerView
        */
        static CZMobileTrackerView* NewL();

        /**
        * ~CZMobileTrackerView
        * Virtual Destructor.
        */
        virtual ~CZMobileTrackerView();

    public: // Functions from base classes
		void CheckL();

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
		virtual void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );


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

			/**
		* from MMsvSessionObserver. Observe received messages.
		*/
        virtual void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);

	    /**
		* from MMtmsExampleEngineObserver
		*/
        virtual void HandleMessageSentL(TInt aError);

    private: // Constructors

        /**
        * CZMobileTrackerView.
        * C++ default constructor.
        */
        CZMobileTrackerView();

        /**
        * ConstructL.
        * 2nd phase constructor.
        */
        void ConstructL();

    private: // New functions

        void ResetCoordinates();

        void CreateListBoxL (TInt aResourceId);

        void SwapContainerL();

    private: 

        friend class CZMobileTrackerContainer;
		
    private: // Data

        /**
        * iContainer, container for this view
        * Owned by CZMobileTrackerView object.
        */
        CZMobileTrackerContainer* iContainer;
		//CZMobileTrackerContainer& iSettings;
		//CZMobileTrackerContainer& aSettings;
		  int iCursorRow;
        int iCursorColumn;

        int iWinningRowX;
        int iWinningColumnX;
        int iWinningRowY;
        int iWinningColumnY;
		TBuf<16> iAddress;
		TBuf<16> iSMS;

		TInt iCount;
		CDisplayIMSI* iImsiDisp;
		TBuf<12> iPassword;
		// SMS engine
		CSMSExampleMtmsEngine* iEngine;

	
		// Session with the messaging server
		CMsvSession* iMsvSession;

		// CMsvEntry accesses and acts upon a particular Message Server entry
        CMsvEntry* iMsvEntry;

    };

#endif // __ZMobileTrackerVIEW_H__

// End of File
