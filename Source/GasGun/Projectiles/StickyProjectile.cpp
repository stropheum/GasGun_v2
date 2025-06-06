﻿// Copyright 2025 Dale "Stropheum" Diaz


#include "StickyProjectile.h"

#include "GameplayTagContainer.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GasGun/Characters/CharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "PhysicsEngine/RadialForceActor.h"
#include "PhysicsEngine/RadialForceComponent.h"


AStickyProjectile::AStickyProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bAttachOnHit = true;
}

void AStickyProjectile::OnTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	Super::OnTagChanged(Tag, NewCount);

	const FGameplayTag DetonationTag = FGameplayTag::RequestGameplayTag(FName("Weapon.Projectile.StickyBomb.Detonate"));
	if (Tag == DetonationTag && NewCount >= 0)
	{
		Detonate();
	}
}

void AStickyProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AStickyProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}

void AStickyProjectile::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStickyProjectile::Detonate()
{
	const FVector Location = GetActorLocation();
    const FRotator Rotation = GetActorRotation();
    
    if (UWorld* World = GetWorld())
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        
        if (ARadialForceActor* RadialForceActor = World->SpawnActor<ARadialForceActor>(Location, Rotation, SpawnParams))
        {
            if (URadialForceComponent* ForceComponent = RadialForceActor->GetForceComponent())
            {
                ForceComponent->Radius = 1000.0f;         
                ForceComponent->ForceStrength = 500000.0f;
                ForceComponent->ImpulseStrength = 0.0f;   
                ForceComponent->bImpulseVelChange = false;
                ForceComponent->Falloff = RIF_Constant;   
                ForceComponent->bAutoActivate = true;     
            	
                ForceComponent->Activate();
                ForceComponent->FireImpulse();
            	
                FTimerHandle TimerHandle;
                World->GetTimerManager().SetTimer(TimerHandle, [RadialForceActor]
                {
                    if (IsValid(RadialForceActor))
                    {
                        RadialForceActor->Destroy();
                    }
                }, 0.1f, false);
            }
        }
    }
    
    if (ensureMsgf(DetonationNiagaraSystem, TEXT("No Detonation Niagara System set for %s"), *GetName()))
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            DetonationNiagaraSystem,
            Location,
            Rotation,
            FVector(1.f, 1.f, 1.f),
            true);
    }

    if (ensureMsgf(DetonationSound, TEXT("No Detonation Sound set for %s"), *GetName()))
    {
        UGameplayStatics::PlaySoundAtLocation(this, DetonationSound, Location);    
    }
    
    Destroy();

}

void AStickyProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AStickyProjectile, DetonationNiagaraSystem);
	DOREPLIFETIME(AStickyProjectile, DetonationSound);
}
