/*
* ============================================================================
*  Part of  : Mobile Tracker
*  Created  : 12.05.2009 by Kishoj, Meena
*  Implementation notes:
*     This portion creates the setting view of Mobile Tracker that contains setting adjustments.
*  Version  : 1.062	
*  Copyright: 062-BCT  Mobile Tracker Group
* ============================================================================
*/


#include <aknviewappui.h>
#include "ZMobileTrackersettingslistbox.h"
#include "ZMobileTrackersettingsview.h"
#include "ZMobileTrackerdocument.h"
#include "nac.hrh"
#include <nac.rsg>







CZMobileTrackerSettingsView* CZMobileTrackerSettingsView::NewL()
    {
    CZMobileTrackerSettingsView* self = new (ELeave) CZMobileTrackerSettingsView;
    CleanupStack::PushL (self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }
void CZMobileTrackerSettingsView::ConstructL()
    {
    BaseConstructL (R_MOBILETRACKER_SETTING_VIEW);
    }
CZMobileTrackerSettingsView::CZMobileTrackerSettingsView() : iListBox (NULL)
    {    }

CZMobileTrackerSettingsView::~CZMobileTrackerSettingsView()
    {
    if (iListBox)
        {
        AppUi()->RemoveFromStack (iListBox);
        }
    delete iListBox;
    }
TUid CZMobileTrackerSettingsView::Id() const
    {
    return TUid::Uid (EMultiViewsSettingId);
    }



void CZMobileTrackerSettingsView::HandleCommandL (TInt aCommand)
    {
    switch (aCommand)
        {
        case EAknSoftkeyOk:
            {
            CZMobileTrackerDocument* document = static_cast<
                CZMobileTrackerDocument*> (AppUi()->Document());
            iListBox->StoreSettingsL();
            document->SaveSettingsAndInformationL();
            document->NewGame();
            AppUi()->ActivateLocalViewL (TUid::Uid (EMultiViewsPlayGameId));
            break;
            }

        case EAknSoftkeyCancel:
            {
            AppUi()->ActivateLocalViewL (TUid::Uid (EMultiViewsPlayGameId));
            break;
            }

        default:
            AppUi()->HandleCommandL (aCommand);	
        }
    }
void CZMobileTrackerSettingsView::DoActivateL (const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
    {
    if (!iListBox)
        {
        CZMobileTrackerDocument* document = static_cast<
            CZMobileTrackerDocument*> (AppUi()->Document());

        iListBox = new (ELeave) CZMobileTrackerSettingListbox (document->InformationAndSettings());

        iListBox->SetMopParent (this);
        iListBox->ConstructFromResourceL (R_MOBTRAC_SETTING_LIST_PLAYER_NAME_TEXT);
        AppUi()->AddToStackL (*this, iListBox);
        }

    iListBox->MakeVisible (ETrue);
    iListBox->SetRect(ClientRect());
    iListBox->ActivateL();
    iListBox->DrawNow();
	
    }
void CZMobileTrackerSettingsView::DoDeactivate()
    {
    if (iListBox)
        {
        iListBox->MakeVisible (EFalse);
        }
    }
