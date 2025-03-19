#include "ChatGameMode.h"
#include "ChatController.h"
#include "../GameUI/ChatWindow.h"
#include "GameFramework/PlayerState.h"
AChatGameMode::AChatGameMode()
{
	//bNetLoadOnClient = true;
	bReplicates = true;
}

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
}