// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksModeBase::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(ToonTanksPlayerController)
        {
             ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);

    }
    else if(ATower* DestroyTower = Cast<ATower>(DeadActor))
    {
        DestroyTower->HandleDestruction();
        --TargetTowers;
        if(!TargetTowers)
        {
            GameOver(true);
        }
    }
}
void AToonTanksModeBase::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}
void AToonTanksModeBase::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));

    StartGame();
    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelgate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
        );
        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle,
            PlayerEnableTimerDelgate,
            StartDelay,
            false
        );
    }
}
int32 AToonTanksModeBase::GetTargetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();

}

