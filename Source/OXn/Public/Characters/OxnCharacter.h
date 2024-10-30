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
enum class ECharacterState : uint8;

UCLASS()
class OXN_API AOxnCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AOxnCharacter();

	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }

	using FOnCharacterStateChanged = TMulticastDelegate<void(ECharacterState Current, ECharacterState Prev)>;
	FOnCharacterStateChanged OnCharacterStateChanged;

	FORCEINLINE const UCameraComponent* GetCameraComponent() const { return Camera.Get(); }

protected:
	virtual void BeginPlay() override;

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
