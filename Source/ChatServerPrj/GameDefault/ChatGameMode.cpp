#include "ChatGameMode.h"
#include "ChatController.h"
#include "../GameUI/ChatWindow.h"
#include "GameFramework/PlayerState.h"

//	검증하는 기능이다.
//bool AChatGameMode::ReceiveClientMessage_Validate(APlayerController* Sender, const FString& Message)
//{
//	return true;
//}
////	Client에서 서버로 전송하는 함수이다.
//void AChatGameMode::ReceiveClientMessage_Implementation(APlayerController* Sender, const FString& Message)
//{
//    if (HasAuthority())
//    {
//        UE_LOG(LogTemp, Warning, TEXT("[Server] ReceiveClientMessage_Implementation called"));
//        if (AChatController* Cont = Cast<AChatController>(Sender))
//        {
//            Cont->BroadcastMessage(Cont->GetUserID(), Message);
//        }
//    }
//}

//	서버에서 모든 클라이언트에게 전송하는 메시지다.
//void AChatGameMode::BroadcastMessage_Implementation(const FString& SenderName, const FString& Message)
//{
//	if (HasAuthority())
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Server has authority, calling BroadcastMessage"));
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Client called BroadcastMessage!"));
//	}
//	// FConstPlayerControllerIterator은 값이 없으면 암묵적으로 false가 리턴된다.
//	//if (HasAuthority())
//	//{
//	//	for (auto iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
//	//	{
//	//		if (AChatController* Cont = Cast<AChatController>(*iter))
//	//		{
//	//			Cont->ReceiveMessage(SenderName, Message);
//	//		}
//	//	}
//	//}	
//	
//	//if (GetNetMode() != NM_DedicatedServer) // 전용 서버 제외
//	//{
//	//	if (AChatController* Cont = Cast<AChatController>(GetWorld()->GetFirstPlayerController()))
//	//	{
//	//		UE_LOG(LogTemp, Warning, TEXT("호출된 Client : %s"), *Cont->GetUserID());
//	//		if (!Cont->ChatWindowInstance.IsValid())
//	//		{
//	//			Cont->ChatWindowInstance = CreateWidget<UChatWindow>(Cont, Cont->ChatWindowClass.Get());
//	//			if (Cont->ChatWindowInstance)
//	//			{
//	//				Cont->ChatWindowInstance->AddToViewport();
//	//			}
//	//		}
//	//		if (Cont->ChatWindowInstance)
//	//		{
//	//			Cont->ChatWindowInstance->AddMessage(SenderName, Message);
//	//		}
//	//	}
//	//}
//}
void AChatGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (uint32 i = 1; i <= 9; ++i)
	{
		NumArray.Add(i);
	}

	int32 Half = NumArray.Num() / 2;

	for (uint32 i = 0; i < 100; ++i)
	{
		int32 Start = FMath::RandRange(0, Half-1);
		int32 End = FMath::RandRange(Half, NumArray.Num()-1);

		NumArray.Swap(Start, End);
	}

	SystemAnswer.Add(NumArray[0]);
	SystemAnswer.Add(NumArray[1]);
	SystemAnswer.Add(NumArray[2]);
}

FBaseballResult AChatGameMode::ServerBaseballResult(const TArray<int32>& Answer)
{
	FBaseballResult Result = {};

	for (int32 i = 0; i < 3; ++i)
	{
		for (int32 j = 0; j < 3; ++j)
		{
			if (Answer[i] == SystemAnswer[j])
			{
				if (i == j)
				{
					Result.StrikeCount++;
				}
				else
				{
					Result.BallCount++;
				}
				break; // 같은 숫자를 찾았으면 더 찾을 필요 없음
			}
		}
	}

	if (Result.BallCount == 0 && Result.StrikeCount == 0)
	{
		Result.Out = true;
	}
	return Result;
}

bool AChatGameMode::AnswerCheck(const FText& Answer)
{
	FString AnswerString = Answer.ToString();

	if (AnswerString.Len() != 4)
	{
		return false;
	}

	if (AnswerString[0] != TEXT('/'))
	{
		return false;
	}

	FString NumberPart = AnswerString.Mid(1); 
	if (NumberPart.Len() != 3) 
	{
		return false;
	}
	if (NumberPart[0] == NumberPart[1] || 
		NumberPart[1] == NumberPart[2] || 
		NumberPart[0] == NumberPart[2])
	{
		return false; 
	}
	for (int32 i = 0; i < 3; ++i)
	{
		if (!FChar::IsDigit(NumberPart[i]))
		{
			return false;
		}
	}

	return true;
}

TArray<int32> AChatGameMode::SplitAnswer(const FText& Answer)
{
	FString AnswerString = Answer.ToString();

	TArray<int32> Result;
	if (AnswerCheck(Answer))
	{
		Result.Add(FChar::ConvertCharDigitToInt(AnswerString[1]));
		Result.Add(FChar::ConvertCharDigitToInt(AnswerString[2]));
		Result.Add(FChar::ConvertCharDigitToInt(AnswerString[3]));
	}
	return Result;
}

FBaseballResult AChatGameMode::SendAnswer(const FText& Answer)
{
	FBaseballResult Result;

	if (AnswerCheck(Answer))
	{
		Result = ServerBaseballResult(SplitAnswer(Answer));
	}
	else
	{
		Result.Out = true;
	}
	return Result;
}

FText AChatGameMode::MakeMessage(const FBaseballResult& Result)
{
	if (Result.Out)
		return FText::FromString(FString(TEXT("<Server> : 아이고~ 아쉬워라 아웃입니다.")));

	return FText::Format(
		FText::FromString(TEXT("<Server> : Strike: {0}, Ball: {1} 입니다.")),
		Result.StrikeCount,
		Result.BallCount
	);
}