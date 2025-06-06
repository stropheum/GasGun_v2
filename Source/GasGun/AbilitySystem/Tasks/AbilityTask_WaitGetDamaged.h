﻿// Copyright 2025 Dale "Stropheum" Diaz

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitGetDamaged.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FWaitGetDamagedDelegate, float, DamageDone, float, DamageDoneRatio, const FHitResult&, HitResult, const FGameplayEffectSpec&, Spec, const FGameplayTagContainer&, SourceTags);

/**
 * Task that waits until the character is damaged by a projectile or other source
 */
UCLASS()
class GASGUN_API UAbilityTask_WaitGetDamaged : public UAbilityTask
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FWaitGetDamagedDelegate	OnGetDamagedDelegate;

	virtual void Activate() override;

	UFUNCTION()
	void OnGetDamaged(float DamageDone, float DamageDoneRatio, const FHitResult& HitResult, const FGameplayEffectSpec& Spec, const FGameplayTagContainer& SourceTags);

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_WaitGetDamaged* WaitForDamage(UGameplayAbility* OwningAbility, bool TriggerOnce=true);

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_WaitGetDamaged* WaitForDamageWithThreshold(UGameplayAbility* OwningAbility, float Threshold, bool TriggerOnce = true);

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_WaitGetDamaged* WaitForDamageWithThresholdRatio(UGameplayAbility* OwningAbility, float ThresholdRatio, bool TriggerOnce=true);

	bool TriggerOnce;
	float Threshold;
	float ThresholdRatio;

protected:
	virtual void OnDestroy(bool AbilityEnded) override;

	FDelegateHandle OnGetDamagedActivateDelegateHandle;

private:
	UFUNCTION()
	void OnReplicatedDamageEvent();
};
