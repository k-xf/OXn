#include "Characters/OxnCharacter.h" 
#include "Camera/CameraComponent.h"
#include "Data/InputDataConfig.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Characters/CharacterEnums.h"

AOxnCharacter::AOxnCharacter() : CharacterState(ECharacterState::Grounded)
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 350.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
}

void AOxnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOxnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const auto* const PlayerController = Cast<APlayerController>(Controller);
	auto const Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);

	auto* const EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(InputActions->LookAction, ETriggerEvent::Triggered, this, &AOxnCharacter::Look);
	EnhancedInputComponent->BindAction(InputActions->MoveAction, ETriggerEvent::Triggered, this, &AOxnCharacter::Move);
	EnhancedInputComponent->BindAction(InputActions->JumpAction, ETriggerEvent::Started, this, &AOxnCharacter::Jump);
	EnhancedInputComponent->BindAction(InputActions->JumpAction, ETriggerEvent::Completed, this, &AOxnCharacter::StopJumping);
}

void AOxnCharacter::Look(const FInputActionValue& Value)
{
	const auto Vec = Value.Get<FVector2D>();

	AddControllerYawInput(Vec.X);
	AddControllerPitchInput(Vec.Y);
}

void AOxnCharacter::Move(const FInputActionValue& Value)
{
	const auto InputVec = Value.Get<FVector2D>();

	const auto ControlRotation = Controller->GetControlRotation();
	const auto YawRotation = FRotator{ 0, ControlRotation.Yaw, 0 };

	const auto ForwardDir = FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::X);
	const auto RightDir = FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::Y);
	
	AddMovementInput(ForwardDir, InputVec.Y);
	AddMovementInput(RightDir, InputVec.X);
}

void AOxnCharacter::SetCharacterState(const ECharacterState NewState)
{
	if (CharacterState == NewState) return;
	const auto Prev = CharacterState;
	CharacterState = NewState;

	OnCharacterStateChanged.Broadcast(NewState, Prev);
}