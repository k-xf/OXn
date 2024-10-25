#include "Characters/OxnCharacter.h" 
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AOxnCharacter::AOxnCharacter()
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

void AOxnCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const auto* const PlayerController = Cast<APlayerController>(Controller))
		if (auto* const Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(InputMappingContext, 0);
}

void AOxnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOxnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (auto* const EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOxnCharacter::Look);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOxnCharacter::Move);
	}
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
