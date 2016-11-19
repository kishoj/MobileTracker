/*
* ============================================================================
*  Part of  : Mobile Tracker
*  Created  : 12.05.2009 by Kishoj, Meena
*  Implementation notes:
*     Initial content was generated by Series 60 Application Wizard.
*	  It contains display of data on the screen, manages controls that are visible
*  Version  : 1.062
*  Copyright: 062-BCT  Mobile Tracker Group
* ============================================================================
*/



#ifndef __ZMobileTrackerCONTAINER_H__
#define __ZMobileTrackerCONTAINER_H__

// INCLUDES
#include <coecntrl.h>

#include "ZMobileTrackerengine.h"


// FORWARD DECLARATIONS
class CZMobileTrackerView;


// CLASS DECLARATION
/**
*  CZMobileTrackerContainer container control class.
*
*/
class CZMobileTrackerContainer : public CCoeControl,
    public CZMobileTrackerEngine::MObserver
    {
    public: // TYPES
        typedef CZMobileTrackerEngine::TPlayer TPlayer;

    public: // Constructors and destructor

        /**
        * NewL.
        * Two-phased constructor.
        * @param aRect The rectangle this container will be drawn to.
        * @return Pointer to the created instance of CZMobileTrackerContainer.
        */
        static CZMobileTrackerContainer* NewL(const TRect& aRect,
            CZMobileTrackerView& view, TInt aCursorRow, TInt aCursorColumn);

        /**
        * ~CZMobileTrackerContainer.
        * Destructor.
        */
        virtual ~CZMobileTrackerContainer();

    private: // Constructors

        CZMobileTrackerContainer (CZMobileTrackerView& aView, 
            TInt aCursorRow, TInt aCursorColumn);

        /**
        * ConstructL.
        * 2nd phase constructor.
        * @param aRect The rectangle this container will be drawn to.
        */
        void ConstructL (const TRect& aRect);

    private: // Functions from base classes

        /**
        * From CoeControl, SizeChanged.
        * Called by framework when the view size is changed.
        */
        virtual void SizeChanged();

        /**
        * From CoeControl, CountComponentControls.
        * Returns the number of components owned by this container.
        * @return Number of component controls
        */
        virtual TInt CountComponentControls() const;

        /**
        * From CCoeControl, ComponentControl.
        * Returns pointer to a particular control.
        * @param aIndex Index of wanted control
        * @return Pointer to component control
        */
        virtual CCoeControl* ComponentControl (TInt aIndex) const;

        /**
        * From CCoeControl, Draw.
        * Draws this container to the screen
        * @param aRect The region of the control to be redrawn.
        */
        virtual void Draw (const TRect& aRect) const;

        /**
        * From CCoeControl, OfferKeyEventL.
        * Handles the key events.
        * @return if key-event is consumed, EKeyWasConsumed. Else EKeyWasNotConsumed
        * @param aKeyEvent Key event
        * @param aType Type of key event ( EEventKey, EEventKeyUp or EEventKeyDown )
        */
        virtual TKeyResponse OfferKeyEventL (const TKeyEvent& aKeyEvent, TEventCode aType);

        /**
        * From CoeControl, HandleResourceChange.
        * Called by framework when the view layout is changed.
        */
        virtual void HandleResourceChange(TInt aType);
 
    private: // CZMobileTrackerEngine::MObserver

        virtual void HandleMove (TPlayer aPlayer, TUint aRow, TUint aColumn);

        virtual void HandleWinner (TBool aHumanWins, TUint aXRow,
            TUint aXColumn, TUint aZRow, TUint aZColumn);

        virtual void HandleBoardReset();
        
    private: // New functions

        void DrawGrid (const TRect& aRect) const;
		
        void DrawNought (TInt aRow, TInt aColumn) const;

        void DrawCross (TInt aRow, TInt aColumn) const;

        void DrawWinnersLine (TInt aXRow, TInt aXColumn, TInt aYRow, TInt aYColumn) const;

        void DrawCursor (const TRgb& aCursorColour, const TRgb& aReturnColour, 
            TInt aRow, TInt aColumn) const;

    private: // Data

        CZMobileTrackerView& iView;
        TUint iCursorRow;
        TUint iCursorColumn;
    };


#endif // __ZMobileTrackerCONTAINER_H__

// End of File