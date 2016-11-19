/*
* ============================================================================
*  Part of  : Mobile Tracker
*  Created  : 12.05.2009 by Kishoj, Meena
*  Implementation notes:
*     This class is used for file handling to insert and retrieve user information
*  Version  : 1.062
*  Copyright: 062-BCT  Mobile Tracker Group
* ============================================================================
*/



#ifndef __ZMobileTrackerINFORMATIONANDSETTINGS_H__
#define __ZMobileTrackerINFORMATIONANDSETTINGS_H__

// INCLUDES
#include <s32std.h>


// CONSTANTS
#define USERNAME_SIZE 12
#define PASS_SIZE 12

// CLASS DECLARATION
class CZMobileTrackerInformationAndSettings : public CBase
	{
	public:
		typedef TBuf<USERNAME_SIZE> TPlayerName;
		typedef TBuf<PASS_SIZE> TPass;

	public:
		CZMobileTrackerInformationAndSettings();

		void SetPlayerName (const TPlayerName& aPlayerName);

		TPlayerName& PlayerName();

		const TPlayerName& PlayerName() const;

		
		void SetAddr (const TPlayerName& );

		TPlayerName& Addr();

		const TPlayerName& Addr() const;




		void SetHumanPlayFirst (TBool aPlayFirst);

		TBool& HumanPlayFirst();

		TBool HumanPlayFirst() const;

		void SetHumanTypeCross (TBool aPlayTypeCross);

		TBool& HumanTypeCross();

		TBool HumanTypeCross() const;

		void ExternalizeL (RWriteStream& aStream) const;
		
		void InternalizeL (RReadStream& aStream);

	private:
		CZMobileTrackerInformationAndSettings (
			const CZMobileTrackerInformationAndSettings& aCopy);

		CZMobileTrackerInformationAndSettings& operator= (
			const CZMobileTrackerInformationAndSettings& aOther);

	public:
		TPlayerName iPlayerName;
		TPass iPass;
		TBool iPlayFirst;
		TBool iPlayTypeCross;
		TInt iHumanWins;
		TInt iHumanLosses;
		TPlayerName iDest;
	};

#endif // __ZMobileTrackerINFORMATIONANDSETTINGS_H__

// End of File

