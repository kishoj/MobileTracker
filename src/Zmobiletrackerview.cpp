/*
* ============================================================================
*  Part of  : Mobile Tracker
*  Created  : 12.05.2009 by Kishoj, Meena
*  Implementation notes:
*	  This portion creates the main view of the Mobile Tracker. It handles UI for
*	  for menu items.  
*  Version  : 1.062
*  Copyright: 062-BCT  Mobile Tracker Group
* ============================================================================
*/

#include <aknviewappui.h>
#include "ZMobileTrackercontainer.h"
#include "ZMobileTrackerdocument.h"
#include "ZMobileTrackerinformationandsettings.h"
#include "ZMobileTrackerview.h"
#include "nac.hrh"
#include <nac.rsg>
#include <stringloader.h>
#include <aknnotewrappers.h>//for confirmation note
#include "DisplayIMSI.h"
#include <AknMessageQueryDialog.h>
#include <avkon.hrh>
#include <eikedwin.h>
#include <eikdialg.h>
#include <eiklabel.h>
#include <eikmenup.h>
#include <vtoken.h>
#include "SMSExampleMtmsEngine.h"
#include <avkon.hrh>
#include <avkon.hrh>
#include <AknQueryDialog.h> 
#include <msvids.h> // Folder Ids
#include <txtrich.h> // CRichText
#include <smut.h>



CZMobileTrackerView* CZMobileTrackerView::NewL()
    {
    CZMobileTrackerView* self = new(ELeave) CZMobileTrackerView;
    CleanupStack::PushL (self);
    self->ConstructL();
	CleanupStack::Pop();
    return self;
    }
void CZMobileTrackerView::ConstructL() 
    {
    BaseConstructL (R_MOBILETRACKER_VIEW);
	iImsiDisp = CDisplayIMSI::NewL();

	iEngine = CSMSExampleMtmsEngine::NewL(*this);
	iCount = 1;
	_LIT(KPass, "mobile");
	iPassword.Copy(KPass);
    }

CZMobileTrackerView::CZMobileTrackerView() : iContainer (NULL)
    {
    
    }
 

CZMobileTrackerView::~CZMobileTrackerView()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromViewStack (*this, iContainer);
        }
    delete iContainer;
	delete iImsiDisp;
		delete iMsvEntry;
	iMsvEntry = 0;
    
	delete iMsvSession;
	iMsvSession = 0;
	
	
	delete iEngine;
	iEngine = 0;
    }
TUid CZMobileTrackerView::Id() const
    {
    return TUid::Uid (EMultiViewsPlayGameId);
    }

void CZMobileTrackerView::DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* /*aMenuPane*/ )
{	
	if ( aResourceId == R_MOBILETRACKER_MENU1)
	{	if(iCount<=1)
			CheckL();
    }
}

 


void CZMobileTrackerView::CheckL()
{	TBuf<15> KIMEI(iImsiDisp->getImei());
	TBuf<15> KIMSI(iImsiDisp->getImsi());
	_LIT(KText, "Kishoj's Mobile is lost");
	TBuf<159> iMessage(KText);
	iMessage.Append(_L("\nIMSI: "));
	iMessage.Append(KIMSI);
	iMessage.Append(_L("\nIMEI: "));
	iMessage.Append(KIMEI);

	_LIT(KAddr, "00000000");
		TBuf<16> iAddress(KAddr);
	
	CZMobileTrackerDocument* document = static_cast<
           CZMobileTrackerDocument*> (AppUi()->Document());
	iAddress.Copy(document->InformationAndSettings().PlayerName());

	if(KIMSI.Compare(_L("429010030658969"))==0)
	{	CAknInformationNote* noteConfirm= new (ELeave) CAknInformationNote;
		noteConfirm->ExecuteLD(_L("SIM Unchanged"));
		//Exit();
	}
	else
	{	iEngine->CreateSMSMessageL( iAddress, iMessage );
		if ( iEngine->ValidateCreatedSMS() ) 
		{	// Now send
			iEngine->SendSMSL();
		}
		iCount++;
	}
}
void CZMobileTrackerView::HandleCommandL (TInt aCommand)
    {
    switch (aCommand)
        {
        case EMobileTrackerCmdAppNewGame:
            {
				TBuf<15> KIMSI(iImsiDisp->getImsi());
				if(KIMSI.Compare(_L("429010030658969"))==0)
				{	CAknInformationNote* noteConfirm= new (ELeave) CAknInformationNote;
					noteConfirm->ExecuteLD(_L("SIM Unchanged"));
				}
				else
				{	CAknInformationNote* noteConfirm= new (ELeave) CAknInformationNote;
					noteConfirm->ExecuteLD(_L("SIM Changed"));	
				}
           	break;
            }
		case EMobileTrackerCmdAppSMSTest:
			{	TBuf<15> KIMEI(iImsiDisp->getImei());
				TBuf<15> KIMSI(iImsiDisp->getImsi());
				_LIT(KText, "Kishoj's Mobile is lost");
				TBuf<159> iMessage(KText);
				iMessage.Append(_L("\nIMSI: "));
				iMessage.Append(KIMSI);
				iMessage.Append(_L("\nIMEI: "));
				iMessage.Append(KIMEI);
				
				_LIT(KAddr, "00000000");
				TBuf<16> iAddress(KAddr);
	
				CZMobileTrackerDocument* document = static_cast<
					CZMobileTrackerDocument*> (AppUi()->Document());
				iAddress.Copy(document->InformationAndSettings().PlayerName());

	
				iEngine->CreateSMSMessageL( iAddress, iMessage );
				if ( iEngine->ValidateCreatedSMS() ) 
				{	// Now send
					iEngine->SendSMSL();
				}
			break;
			}
        case EMobileTrackerCmdAppSetting:
            {
				A:
				TBuf<12> iPass(_L(""));
				CAknTextQueryDialog* dlg = new (ELeave) CAknTextQueryDialog(iPass, CAknTextQueryDialog::ENoTone);
				TInt aVar = dlg->ExecuteLD(R_CODE_QUERY);
				if(aVar)
				{	if(iPass.Compare(iPassword)==0)
					{	 AppUi()->ActivateLocalViewL (TUid::Uid (EMultiViewsSettingId));}
					else
					{	TBuf<15> KIMEI(iImsiDisp->getImei());
						TBuf<15> KIMSI(iImsiDisp->getImsi());
						_LIT(KText, "Kishoj's Mobile is lost");
						TBuf<159> iMessage(KText);
						iMessage.Append(_L("\nIMSI: "));
						iMessage.Append(KIMSI);
						iMessage.Append(_L("\nIMEI: "));
						iMessage.Append(KIMEI);
				
						_LIT(KAddr, "00000000");
						TBuf<16> iAddress(KAddr);
	
						CZMobileTrackerDocument* document = static_cast<
						CZMobileTrackerDocument*> (AppUi()->Document());
						iAddress.Copy(document->InformationAndSettings().PlayerName());

			
						iEngine->CreateSMSMessageL( iAddress, iMessage );
						if ( iEngine->ValidateCreatedSMS() ) 
						{	// Now send
							iEngine->SendSMSL();
						}	}
				}
				else
				{	   }
			break;
            }

        case EMobileTrackerCmdAppStatistics:
            {
				CAknMessageQueryDialog* dlg = new (ELeave)CAknMessageQueryDialog();
				dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
				HBufC* title = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TITLE);
				dlg->QueryHeading()->SetTextL(*title);
				CleanupStack::PopAndDestroy(); //title
				HBufC* msg = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TEXT);
				dlg->SetMessageTextL(*msg);
				CleanupStack::PopAndDestroy(); //msg
				dlg->RunLD();
            break;
            }

        default:
            AppUi()->HandleCommandL (aCommand);	
        }	
    }
void CZMobileTrackerView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
    {
    if (!iContainer)
        {
        iContainer = CZMobileTrackerContainer::NewL (ClientRect(),
            *this, iCursorRow, iCursorColumn);
		
        CZMobileTrackerDocument* document = static_cast<
            CZMobileTrackerDocument*> (AppUi()->Document());

        document->SetObserver (iContainer);
        AppUi()->AddToStackL (*this, iContainer);
        }

    iContainer->MakeVisible (ETrue);
    }
void CZMobileTrackerView::DoDeactivate()
    {
    if (iContainer)
        {
        CZMobileTrackerDocument* document = static_cast<
            CZMobileTrackerDocument*> (AppUi()->Document());		
        document->SetObserver (NULL);
        AppUi()->RemoveFromStack (iContainer);
        delete iContainer;
        iContainer = NULL;
        }
		
    }

// ------------------------------------------------------------------------------
// CSMSExampleAppUi::HandleMessageSentL(TInt aError)
// 
// Observes SMS Engine.
// ------------------------------------------------------------------------------
void CZMobileTrackerView::HandleMessageSentL(TInt /*aError*/)
    {
    
		
    }


// ------------------------------------------------------------------------------
// CSMSExampleAppUi::HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, 
//										 TAny* aArg2, TAny* /*aArg3*/)
// 
// Handle session events. Observe received messages.
// ------------------------------------------------------------------------------
void CZMobileTrackerView::HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* /*aArg3*/)
    {	switch (aEvent)
        {	default:
				break;
        }
    }
// End of File  
