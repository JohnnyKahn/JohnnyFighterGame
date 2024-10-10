
#include "Widget/EndWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

void UEndWidget::UpdateResultText(FText NewText)
{
	if(ResultText)
		ResultText->SetText(NewText);
}

bool UEndWidget::Initialize()
{

	if (Super::Initialize() == false) return false;

	if (PlayAgainButton)
		PlayAgainButton->OnClicked.AddDynamic(this, &UEndWidget::PlayAgainClick);

	if (ExitButton)
		ExitButton->OnClicked.AddDynamic(this, &UEndWidget::ExitClick);

	return true;
}

void UEndWidget::PlayAgainClick()
{
	if (GetOwningPlayer() == nullptr) return;

	UGameplayStatics::SetGamePaused(GetWorld(), false);

	FInputModeGameOnly MyInputMode;

	GetOwningPlayer()->SetInputMode(MyInputMode);
	GetOwningPlayer()->SetShowMouseCursor(false);

	auto LevelString = UGameplayStatics::GetCurrentLevelName(GetWorld());
	auto LevelName = FName(*LevelString);

	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void UEndWidget::ExitClick()
{
	TEnumAsByte < EQuitPreference::Type> QuitPreference = EQuitPreference::Quit;
	auto PlayerController =  UGameplayStatics::GetPlayerController(GetWorld(), 0);

	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, QuitPreference, true);
}
