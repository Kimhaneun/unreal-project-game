// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Project0Player.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameData/Project0CharacterStat.h"
#include "CharacterStat/Project0CharacterComponent.h"
#include "UI/Project0PlayerHUDWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/Project0GameInterface.h"

AProject0Player::AProject0Player()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 700.0f;

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Camera->bUsePawnControlRotation = false;

	// Player HUD Widget
	static ConstructorHelpers::FClassFinder<UProject0PlayerHUDWidget> PlayerHUDWidgetClassRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_PlayerHUD.WBP_PlayerHUD_C'"));
	if (PlayerHUDWidgetClassRef.Succeeded())
	{
		PlayerHUDWidgetClass = PlayerHUDWidgetClassRef.Class;
	}

	struct ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCDefaultRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/03Input/IMC_Default.IMC_Default'"));
	if (IMCDefaultRef.Succeeded())
	{
		InputMappingContext = IMCDefaultRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> AttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/03Input/Actions/Project0Attack.Project0Attack'"));
	if (AttackActionRef.Succeeded())
	{
		AttackAction = AttackActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MovementActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/03Input/Actions/Project0Movement.Project0Movement'"));
	if (MovementActionRef.Succeeded())
	{
		MovementAction = MovementActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> TurnActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/03Input/Actions/Project0Turn.Project0Turn'"));
	if (TurnActionRef.Succeeded())
	{
		TurnAction = TurnActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/03Input/Actions/Project0Jump.Project0Jump'"));
	if (JumpActionRef.Succeeded())
	{
		JumpAction = JumpActionRef.Object;
	}
}

void AProject0Player::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}

		EnableInput(PlayerController);
	}

	PlayerHUDWidget = CreateWidget<UProject0PlayerHUDWidget>(PlayerController, PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}

	if (PlayerHUDWidget && StatComponent)
	{
		PlayerHUDWidget->UpdateStat(StatComponent->GetBaseStat(), StatComponent->GetModifierStat());
		PlayerHUDWidget->UpdateHP(StatComponent->GetCurrentHP());

		StatComponent->OnHpChangedDelegate.AddUObject(PlayerHUDWidget, &UProject0PlayerHUDWidget::UpdateHP);
		StatComponent->OnStatChangedDelegage.AddUObject(PlayerHUDWidget, &UProject0PlayerHUDWidget::UpdateStat);
	}
}

void AProject0Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProject0Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AProject0Player::InputAttack);
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AProject0Player::InputMovement);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &AProject0Player::InputTurn);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AProject0Player::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AProject0Player::StopJumping);
	}
}

void AProject0Player::SetDead()
{
	Super::SetDead();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		DisableInput(PlayerController);
	}

	IProject0GameInterface* Project0GameMode = Cast<IProject0GameInterface>(GetWorld()->GetAuthGameMode());
	if (Project0GameMode)
	{
		Project0GameMode->OnPlayerDead();
	}
}

void AProject0Player::InputAttack(const FInputActionValue& InputValue)
{
	// GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Blue, TEXT("Attack"));

	// ProcessAttack();
	ProcessComboAttack();
}

void AProject0Player::InputMovement(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AProject0Player::InputTurn(const FInputActionValue& InputValue)
{
	float XValue = InputValue.Get<float>();
	AddControllerYawInput(XValue);
}
