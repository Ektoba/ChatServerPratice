#include "ChatController.h"
#include "Kismet/GameplayStatics.h"
#include "ChatServerPrj/GameUI/ChatWindow.h"
#include "ChatGameMode.h"
#include "ChatGameState.h"

void AChatController::ReceiveMessage_Implementation(const FString& SenderName,const FString& Message)
{
	if (ChatWindowInstance)
	{
		ChatWindowInstance->AddMessage(SenderName, Message);
	}
}

void AChatController::SendServerMessage_Implementation(APlayerController* Sender,const FString& Message)
{	
	if (AChatGameState* ChatGameState = GetWorld()->GetGameState<AChatGameState>())
	{		
		if (AChatController* Cont = Cast<AChatController>(Sender))
		{
			ChatGameState->BroadcastMessage(Cont->GetUserID(), Message);
		}
	}
}

FString AChatController::GetUserID() const
{	
	return ControllerID;
}

void AChatController::BeginPlay()
{
	Super::BeginPlay();

	if (IsServer())
	{
		ControllerID = FString::Printf(TEXT("[Host]"));
	}
	else
	{
		ControllerID = FString::Printf(TEXT("[Guest%d]"),GetUniqueID());
	}
	if (!GetRemoteRole() == ROLE_None)
	{
		//	T딜레이 줘야함
		if (ChatWindowClass)
		{
			ChatWindowInstance = CreateWidget<UChatWindow>(this, ChatWindowClass.Get());
			if (ChatWindowInstance.IsValid())
			{
				ChatWindowInstance->AddToViewport();
				bShowMouseCursor = true;
				SetInputMode(FInputModeGameAndUI());
			}
		}
	}
}

bool AChatController::IsServer()
{
	if (UWorld* World = GetWorld())
	{
		ENetMode NetMode = World->GetNetMode();

		switch (NetMode)
		{
		case NM_Standalone:
			break;
		case NM_DedicatedServer:
			return true;
			break;
		case NM_ListenServer:
			if (IsLocalController())
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		case NM_Client:
			break;
		case NM_MAX:
			break;
		default:
			break;
		}
	}
	return false;
}
