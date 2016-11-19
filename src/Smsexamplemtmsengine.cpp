/*
* ============================================================================
*  Name     : CSMSExampleMtmsEngine from SMSExampleMtmsEngine.h
*  Part of  : SMSExample to be used for Mobile Tracker.
*  Created  : 12.03.2005 by Forum Nokia 
*  Edited by: Kishoj, Meena
*  Implementation notes:
*     We have edited & used this Class from Forum Nokia. This portion of code
*	contains many functions that is used for handling of SMS. 
*  Version  : 1.0
*  Copyright: Nokia Corporation
* ============================================================================
*/

// INCLUDE FILES
#include "SMSExampleMtmsEngine.h"

// SYSTEM FILES
#include <f32file.h>        // TParsePtrC
#include <mmsclient.h>      // CMmsClientMtm
#include <mtclreg.h>        // CClientMtmRegistry 
#include <mtmdef.h>         // KMsvMessagePartBody 
#include <smsclnt.h>        // CSmsClientMtm
#include <smscmds.h>        // ESmsMtmCommandScheduleCopy
#include <smuthdr.h>        // CSmsHeader
#include <smutset.h>        // CSmsSettings
#include <txtrich.h>        // CRichText
#include <eikenv.h>

const TInt KMessageAddressLength = 100;
const TInt KMessageBodySize = 159;

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::NewL(MSMSExampleMtmsEngineObserver& aObserver)
//
// Symbian OS 2 phase constructor.
// ----------------------------------------------------------------------------
CSMSExampleMtmsEngine* CSMSExampleMtmsEngine::NewL(MSMSExampleMtmsEngineObserver& aObserver)
    {
    CSMSExampleMtmsEngine* self = new (ELeave) CSMSExampleMtmsEngine(aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::CSMSExampleMtmsEngine(MSMSExampleMtmsEngineObserver& 
//												aObserver)
//
// Symbian OS 2 phase constructor.
// ----------------------------------------------------------------------------
CSMSExampleMtmsEngine::CSMSExampleMtmsEngine(MSMSExampleMtmsEngineObserver& aObserver)
: CActive(0),
  iObserver(aObserver),
  iSmsId(KMsvNullIndexEntryId)
    {
    }

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::ConstructL()
//
// Symbian OS 2nd phase constructor.
// ----------------------------------------------------------------------------
void CSMSExampleMtmsEngine::ConstructL()
    {
    CActiveScheduler::Add(this);

    // iEntrySelection encapsulates an array of entry IDs
    iEntrySelection = new (ELeave) CMsvEntrySelection;

    // Represents a channel of communication between a client thread (Client-side MTM, User
	// Interface MTM, or message client application) and the Message Server thread. 
	// Session is opened asynchorously. CreateMtmClientL() is called afterwards.
	// Another possibility is use OpenSyncL which is synchronous.
    iSession = CMsvSession::OpenAsyncL(*this);
    }

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::CreateMtmClientL()
//
// Create a CSmsClientMtm after session has been opened.
// ----------------------------------------------------------------------------
void CSMSExampleMtmsEngine::CreateMtmClientL()
    {
    // Client-side MTM registry. 
    iClientMtmReg = CClientMtmRegistry::NewL(*iSession);

    // Get the SMS Mtm client from the registry
    iSmsMtm = static_cast<CSmsClientMtm*>(iClientMtmReg->NewMtmL(KUidMsgTypeSMS));
  
    }

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::~CSMSExampleMtmsEngine()
//
// Destructor.
// ----------------------------------------------------------------------------
CSMSExampleMtmsEngine::~CSMSExampleMtmsEngine()
    {
    Cancel();
    delete iMsvOper;
    delete iEntrySelection;
    delete iSmsMtm;
    delete iClientMtmReg;
    delete iSession;
    }
 
// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::DoCancel()
//
// From CActive, cancel CMsvOperation 
// ----------------------------------------------------------------------------
void CSMSExampleMtmsEngine::DoCancel()
    {
    if (iMsvOper)
        {
        iMsvOper->Cancel();
        delete iMsvOper;
        iMsvOper = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::RunL()
//
// Sending SMS is asynchronous operation.
// ----------------------------------------------------------------------------
void CSMSExampleMtmsEngine::RunL()
    {
    iObserver.HandleMessageSentL(iStatus.Int());
    }

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::CreateSMSMessageL(const TDesC& aAddress, 
//											const TDesC& aMessage)
//
// Create an SMS message
// ----------------------------------------------------------------------------
void CSMSExampleMtmsEngine::CreateSMSMessageL(const TDesC& aAddress, const TDesC& aMessage)
    {
    // Set SMS parameters 
    TMsvEntry indexEntry;
	indexEntry.iDate.HomeTime();



	//indexEntry.SetVisible( EFalse );          // set message as invisible


    
	indexEntry.SetInPreparation(ETrue);
	// This is an SMS message
    indexEntry.iMtm = KUidMsgTypeSMS;
    indexEntry.iType = KUidMsvMessageEntry;
	//Gets the ID of the current SMS service.
    indexEntry.iServiceId = iSmsMtm->ServiceId();
    
    // Create entry to drafts
    iSmsMtm->SwitchCurrentEntryL(KMsvDraftEntryId);

	// Creates a new child entry owned by the context synchronously.
    iSmsMtm->Entry().CreateL(indexEntry);

    // Set the MTM's active context to the new message
    iSmsId = indexEntry.Id();
    iSmsMtm->SwitchCurrentEntryL(iSmsId);

    // Add message body. Body is set twice because index entry keeps a copy
	// of some summary information. Index entry and full stored entry
	// must be in sync.
    CRichText& body = iSmsMtm->Body();
    body.Reset();
    body.InsertL(0, aMessage);
    indexEntry.iDescription.Set(aMessage);

    // Add destination address (recipient). Copy address also to the index entry
    iSmsMtm->AddAddresseeL(aAddress);
    indexEntry.iDetails.Set(aAddress);

    // Commit changes because index entry is only a local variable
    iSmsMtm->Entry().ChangeL(indexEntry);

    // Save full message data to the store
    iSmsMtm->SaveMessageL();
    }

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::ValidateCreatedSMS()
//
// Validate message. This should be done before sending the SMS.
// ----------------------------------------------------------------------------
TBool CSMSExampleMtmsEngine::ValidateCreatedSMS()
    {
    TMsvPartList partsToBeChecked = KMsvMessagePartBody | KMsvMessagePartRecipient |
        KMsvMessagePartOriginator | KMsvMessagePartDate;

	// ValidateMessage return KErrNone if message is valid.
    TMsvPartList failedParts = iSmsMtm->ValidateMessage(partsToBeChecked);
    
	if (failedParts == KMsvMessagePartNone)
		{
		return ETrue;
		}
	else 
		{
		return EFalse;
		}
    }

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::SendSMSL()
//
// Before sending sms message should be created CreateSMSMessageL() and
// Validated ValidateCreatedSMS().
// ----------------------------------------------------------------------------
void CSMSExampleMtmsEngine::SendSMSL()
    {
    // Changes the entry on which later actions are performed to the entry with the 
	// specified TMsvId. 
    iSmsMtm->SwitchCurrentEntryL(iSmsId);

    // Load the created message
    iSmsMtm->LoadMessageL();

    // Gets the current SMS service settings
    CSmsSettings& serviceSettings = iSmsMtm->ServiceSettings();

	// Gets the number of service centre addresses stored in this object.
    const TInt numSCAddresses = serviceSettings.NumSCAddresses();
    
	// There should always be a service center number
	if (numSCAddresses > 0)
		{
        CSmsNumber*	serviceCentreNumber = NULL;

        // get the service center number
        if ((serviceSettings.DefaultSC() >= 0)  &&  (serviceSettings.DefaultSC() < numSCAddresses))
            serviceCentreNumber = &(serviceSettings.SCAddress(serviceSettings.DefaultSC()));
        else
            serviceCentreNumber = &(serviceSettings.SCAddress(0));

        iSmsMtm->SmsHeader().SetServiceCenterAddressL(serviceCentreNumber->Address());
        }
	else 
		{
		// Leave if there is no service center number
		User::Leave(0);
		}

    iSmsMtm->SaveMessageL();

    // Index entry must be Updated
    
	TMsvEntry indexEntry = iSmsMtm->Entry().Entry();

	/*It is used to hide message sent*/
	
	
	/**************************  change this if error occurs  ***************************/
	
	indexEntry.SetVisible( EFalse );   
	

	/**************************  change this if error occurs  ***************************/





	
	// Set in-preparation flag
    indexEntry.SetInPreparation(EFalse);
	// Sets the sending state
    indexEntry.SetSendingState(KMsvSendStateWaiting);
    iSmsMtm->Entry().ChangeL(indexEntry);

    // Time to send the message
    Cancel(); // prepare iMsvOper for use
	iEntrySelection->Reset();
	iEntrySelection->AppendL(iSmsId);

    TBuf8<1> dummyParam;
	// There is also InvokeSyncFunctionL which is synchronous.
	iMsvOper = iSmsMtm->InvokeAsyncFunctionL(ESmsMtmCommandScheduleCopy, *iEntrySelection, dummyParam, iStatus);
    SetActive();
    }

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::MoveToFolderL( TMsvId aMessageId,  TMsvId aFolder )
//
// Move message to folder. Notice that the iSmsMtm points to the parent, not
// to the message itself. If you move messages from inbox to drafts, those
// messages cannot be edited because their complete flag is true.
// ----------------------------------------------------------------------------
void CSMSExampleMtmsEngine::MoveToFolderL( TMsvId aMessageId,  TMsvId aFolder )
	{
	iSmsMtm->SwitchCurrentEntryL( aMessageId );
	TMsvSelectionOrdering selection;
	selection.SetShowInvisibleEntries(ETrue);
	CMsvEntry* parentEntry = CMsvEntry::NewL( iSmsMtm->Session(), 
		iSmsMtm->Entry().Entry().Parent(), selection );
	CleanupStack::PushL(parentEntry);
	// Move the message
	parentEntry->MoveL( aMessageId, aFolder );
	CleanupStack::PopAndDestroy(); // parentEntry
	}

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::DeleteMessageL( TMsvId aMessageId )
//
// Delete message from a folder. Notice that the iSmsMtm points to the parent, 
// not to the message itself.
// ----------------------------------------------------------------------------
void CSMSExampleMtmsEngine::DeleteMessageL( TMsvId aMessageId )
	{
	iSmsMtm->SwitchCurrentEntryL( aMessageId );
	TMsvId parent = iSmsMtm->Entry().Entry().Parent();

	iSmsMtm->SwitchCurrentEntryL( parent );
	iSmsMtm->Entry().DeleteL( aMessageId );
	}

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::GetMessageAddressL( TMsvId aMessageId, 
//										      TDes& aAddress )
//
// Get originator address from SmsHeader.
// ----------------------------------------------------------------------------
void CSMSExampleMtmsEngine::GetMessageAddressL( TMsvId aMessageId, TDes& aAddress )
	{
	iSmsMtm->SwitchCurrentEntryL( aMessageId );	
	
	// Remember to load before using the SmsHeader
	iSmsMtm->LoadMessageL();

	CSmsHeader&	header = iSmsMtm->SmsHeader();

	aAddress.Append( header.FromAddress() );
	// Other possibility is this: (It's little bit faster than the previous one).
	// aAddress.Append( iSmsMtm->Entry().Entry().iDetails );
	}

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::GetMessageL( TMsvId aMessageId, TDes& aMessage)
//
// Get message body from entry storage (CMsvStore). CMsvStore stores whole
// message, not summary information ( see GetMessageIndexBodyTextL() ).
// ----------------------------------------------------------------------------
TBool CSMSExampleMtmsEngine::GetMessageL( TMsvId aMessageId, TDes& aMessage)
	{
	iSmsMtm->SwitchCurrentEntryL( aMessageId );

	if ( iSmsMtm->Entry().HasStoreL() ) 
		{
		// SMS message is stored inside Messaging store.
		CMsvStore* store = iSmsMtm->Entry().ReadStoreL();
		CleanupStack::PushL(store);
	
		if (store->HasBodyTextL())
			{
			CRichText* richText = CRichText::NewL(
			                  CEikonEnv::Static()->SystemParaFormatLayerL(),
			                  CEikonEnv::Static()->SystemCharFormatLayerL());
			richText->Reset();
			CleanupStack::PushL(richText);

			// Get the SMS body text.
			store->RestoreBodyTextL(*richText);
			const TInt length = richText->DocumentLength();
			TBuf<KMessageBodySize> message;

			// Check length because message is read to limited size TBuf.
			if ( length >= KMessageBodySize ) 
				{
				message.Append( richText->Read(0, KMessageBodySize -1) );
				}
			else 
				{
				message.Append( richText->Read(0, length) );
				}

			aMessage.Append( message );

			CleanupStack::PopAndDestroy(richText);
			}
		CleanupStack::PopAndDestroy(store);
		}
	else
		{
		return EFalse;
		}

	return ETrue;
	}
	
// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::GetMessageIndexBodyTextL( TMsvId aMessageId, TDes& aMessage)
//
// Get beginning of message's body. Index entry is just a summary of the whole
// message.
// ----------------------------------------------------------------------------
TBool CSMSExampleMtmsEngine::GetMessageIndexBodyTextL( TMsvId aMessageId, TDes& aMessage)
	{
	iSmsMtm->SwitchCurrentEntryL( aMessageId );

	aMessage.Append(iSmsMtm->Entry().Entry().iDescription );
	return ETrue;
	}
	

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::CopyMessageL( TMsvId aMessageId, TMsvId aFolder )
//
// Copy message to another folder. 
// ----------------------------------------------------------------------------
void CSMSExampleMtmsEngine::CopyMessageL( TMsvId aMessageId, TMsvId aFolder )
	{
	iSmsMtm->SwitchCurrentEntryL( aMessageId );
	TMsvSelectionOrdering selection;
	selection.SetShowInvisibleEntries(ETrue);
	CMsvEntry* parentEntry = CMsvEntry::NewL( iSmsMtm->Session(), 
		iSmsMtm->Entry().Entry().Parent(), selection );
	CleanupStack::PushL(parentEntry);
	// iSmsMtm points to the parent
	parentEntry->CopyL( aMessageId, aFolder );
	CleanupStack::PopAndDestroy(); // parentEntry
	}

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::GetMessageIds()
//
// ids of messages that has been got using ListMessagesL
// ----------------------------------------------------------------------------
RArray<TMsvId>* CSMSExampleMtmsEngine::GetMessageIds()
	{
	return iIdArray;
	}

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::GetFolderSMSMessageInformation( TMsvId aFolderID, 
//														   CDesCArrayFlat* aAddresses, 
//														   CDesCArrayFlat* aMessages )
//
// Get all folder's children which are SMS messages.
// Note that the folder can contain .sis files which have to be filtered out.
// IdArray is made here because it makes finding the SMS easier later on.
// ----------------------------------------------------------------------------
void CSMSExampleMtmsEngine::GetFolderSMSMessageInformation( TMsvId aFolderID, 
														   CDesCArrayFlat*& aAddresses, 
														   CDesCArrayFlat*& aMessages )
	{

	iSmsMtm->SwitchCurrentEntryL( aFolderID );
	CMsvEntry& entry = iSmsMtm->Entry();

	// Remember to delete this entry after no longer needed!
	// Only intrested in messages. Filter out service etries.
	CMsvEntrySelection* entries = entry.ChildrenWithMtmL(KUidMsgTypeSMS);

	CDesCArrayFlat* arrayAddr = new (ELeave) CDesCArrayFlat(10);
	CDesCArrayFlat* arrayMsgBody = new (ELeave) CDesCArrayFlat(10);

	iIdArray = new (ELeave) RArray<TMsvId>;

	for (TInt i = 0; i < entries->Count(); i++ ) 
		{
		TBuf<KMessageBodySize> body;
		TBuf<KMessageAddressLength> address;
		
		// Append only SMS messages, .sis files etc. are disregarded.
		// Take only beginning of SMS body, because listbox only shows beginning
		// of message.
		if ( GetMessageIndexBodyTextL( (*entries)[i], body ) ) // SMS body
			{
			iIdArray->Append( (*entries)[i] );
			arrayMsgBody->AppendL ( body );	

			// Recipient address
			GetMessageAddressL( (*entries)[i], address );
			arrayAddr->AppendL ( address );
			}
		}
		
	// Delete entries. This is your responsibility.
	entries->Reset();
	delete entries;
	entries = 0;

	aAddresses = arrayAddr; // address array
	aMessages = arrayMsgBody; // msg body array
	}

// ----------------------------------------------------------------------------
// CSMSExampleMtmsEngine::HandleSessionEventL(TMsvSessionEvent aEvent, TAny* 
//	/*aArg1*/, TAny* /*aArg2*/, TAny* /*aArg3*/)
//
// Tells when the session has been opened
// ----------------------------------------------------------------------------
void CSMSExampleMtmsEngine::HandleSessionEventL(TMsvSessionEvent aEvent, TAny* /*aArg1*/, TAny* /*aArg2*/, TAny* /*aArg3*/)
    {
    switch (aEvent)
        {
        // This event tells us that the session has been opened
        case EMsvServerReady:
            CreateMtmClientL();
            break;

        default:
            // do nothing
            break;
        }
    }

