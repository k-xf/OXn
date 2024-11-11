#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "OxnCharacter.generated.h"

// Forward declarations
struct FInputActionValue;
class UCameraComponent;
class UInputAction;
class UInputComponent;
class UInputDataConfig;
class UInputMappingContext;
class USpringArmComponent;
enum class ECharacterState : uint8;

UCLASS()
class OXN_API AOxnCharacter : public ACharacterBase
{
	GENERATED_BODY()

	using FOnCharacterStateChanged = TMulticastDelegate<void(ECharacterState Current, ECharacterState Prev)>;

public:
	AOxnCharacter();

	FOnCharacterStateChanged OnCharacterStateChanged;
	
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	
	FORCEINLINE const UCameraComponent* GetCameraComponent() const { return Camera.Get(); }

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Look(const FInputActionValue& Value);
	
	void Move(const FInputActionValue& Value);
	
	void SetCharacterState(ECharacterState NewState);

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
