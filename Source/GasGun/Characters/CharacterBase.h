﻿// Copyright 2025 Dale "Stropheum" Diaz

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "CharacterBase.generated.h"

class UCharacterBaseAttributeSet;
class UAttributeSetBase;
class UAbilitySystemComponent;

UCLASS()
class GASGUN_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

	UFUNCTION()
	UGameplayTasksComponent* GetGameplayTasksComponent() const { return GameplayTasksComponent; }

protected:
	void OnHealthChangeCallback(const FOnAttributeChangeData& OnAttributeChangeData);
	void OnMaxHealthChangeCallback(const FOnAttributeChangeData& OnAttributeChangeData);
	void OnShieldChangeCallback(const FOnAttributeChangeData& OnAttributeChangeData);
	void OnMaxShieldChangeCallback(const FOnAttributeChangeData& OnAttributeChangeData);
	void OnShieldRegenRateChangeCallback(const FOnAttributeChangeData& OnAttributeChangeData);
	void OnShieldRegenDelayChangeCallback(const FOnAttributeChangeData& OnAttributeChangeData);
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UCharacterBaseAttributeSet* GetAttributeSet() const;

	virtual void PostInitProperties() override;

	virtual void Kill();

	UFUNCTION(Server, Reliable)
	virtual void Server_Kill();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_Ragdoll();
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{};

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterBaseAttributeSet> AttributeSet{};

	UPROPERTY(Replicated)
	TObjectPtr<UGameplayTasksComponent> GameplayTasksComponent{};
};
