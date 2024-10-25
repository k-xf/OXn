#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OxnCharacter.generated.h"

// Forward declarations
struct FInputActionValue;
class UCameraComponent;
class UInputAction;
class UInputComponent;
class UInputDataConfig;
class UInputMappingContext;
class USpringArmComponent;
enum ECharacterState : uint8;

using FOnCharacterStateChanged = TMulticastDelegate<void(ECharacterState Current, ECharacterState Prev)>;

UCLASS()
class OXN_API AOxnCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AOxnCharacter();

	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }

	FOnCharacterStateChanged OnCharacterStateChanged;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Look(const FInputActionValue& Value);
	
	void Move(const FInputActionValue& Value);

	void SetCharacterState(ECharacterState Current);
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputDataConfig> InputActions;

	ECharacterState CharacterState;
};
