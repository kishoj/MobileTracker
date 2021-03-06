/*
* ============================================================================
*  Part of  : Mobile Tracker
*  Created  : 12.05.2009 by Kishoj, Meena
*  Implementation notes:
*     Initial content was generated by Series 60 Application Wizard.
*  Version  : 1.062
*  Copyright: 062-BCT  Mobile Tracker Group
* ============================================================================
*/



#ifndef __ZMobileTrackerENGINE_H__
#define __ZMobileTrackerENGINE_H__

// INCLUDES
#include <e32base.h>


// CONSTANTS
#define BOARD_SIZE 3


// CLASS DECLARATION
class CZMobileTrackerEngine : public CTimer
	{
	public:
		enum TPlayer
			{
			ENone = -1,
			ENought,
			ECross
			};

	public:
		typedef TFixedArray<TPlayer, BOARD_SIZE> TCellContainer;
		typedef TFixedArray<TCellContainer, BOARD_SIZE> TBoard;

	public:
		class MObserver
			{
			public:
				virtual void HandleMove (TPlayer aPlayer, TUint aRow, 
					TUint aColumn) = 0;

				virtual void HandleWinner (TBool aHumanWins, TUint aXRow,
					TUint aXColumn, TUint aZRow, TUint aZColumn) = 0;

				virtual void HandleBoardReset() = 0;
		};

	public:
		static CZMobileTrackerEngine* NewLC (TPlayer aHumanPlayer = ECross);

		static CZMobileTrackerEngine* NewL (TPlayer aHumanPlayer = ECross);

		virtual ~CZMobileTrackerEngine();

	public:
		void SetObserver (MObserver* aObserver);

		void StartNewGame (TPlayer aHumanPlayer);

		TBool Winner();

		TBool IsDraw();

		TBool CanMove();

		TBool MakeHumanMove (TUint aRow, TUint aColumn);

		TBool MakeComputerMove();

		const TBoard& Board() const;

	protected: // CTimer
		virtual void RunL();

	private:
		CZMobileTrackerEngine (TPlayer aHumanPlayer);

		void ConstructL();

		void ClearBoard();

		TBool DetermineMove (TUint& aRow, TUint& aColumn) const;

		void CheckForWinner (TPlayer& aResult);

	private:
		TBoard iBoard;
		MObserver* iObserver;
		TPlayer iHumanPlayer;
		TPlayer iComputerPlayer;
		TPlayer iPlayerToGo;
		TUint iComputerMoveRow;
		TUint iComputerMoveColumn;

		TUint winningRowStartIndex;
		TUint winningRowEndIndex;
		TUint winningColumnStartIndex;
		TUint winningColumnEndIndex;
	};

#endif // __ZMobileTrackerENGINE_H__

// End of File
