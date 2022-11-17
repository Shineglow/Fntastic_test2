// Fill out your copyright notice in the Description page of Project Settings.


#include "TurtleBase.h"
#include "Kismet/KismetMathLibrary.h"

ATurtleBase::ATurtleBase()
{
	PrimaryActorTick.bCanEverTick = true;
    tlComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	//tlComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
    turtleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurtleMesh"));
}

void ATurtleBase::InitTurtle(FVector endPoint, float speed, UCurveFloat* moveScale)
{
    turtleSpeed = speed;
    turtleCurve = moveScale;

    ConfigureTimeline();

    if (EndPoint.Equals(FVector().ZeroVector))
        EndPoint = GetTransform().GetLocation() + FVector(0, 100, 0);
    else
        EndPoint = endPoint;
}

void ATurtleBase::StartAnimation()
{
    if (isAnimationStart)
        return;
    tlComponent->PlayFromStart();
    isAnimationStart = true;
}

void ATurtleBase::ConfigureTimeline() {
    if (turtleCurve)
    {
        FOnTimelineFloat TimelineCallback{};
        TimelineCallback.BindUFunction(this, FName("MoveTurtle"));

        tlComponent->SetLooping(true);
        tlComponent->AddInterpFloat(turtleCurve, TimelineCallback);
        tlComponent->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
        tlComponent->SetTimelineLength(timelineLenghtOrTime);
        tlComponent->RegisterComponent();
    }
}

void ATurtleBase::MoveTurtle(float value) {
    AddTurtleOffset();

    if (GetTransform().GetLocation().Equals(EndPoint))
        tlComponent->Stop();
}

void ATurtleBase::AddTurtleOffset()
{
    float currentAnimationTime = tlComponent->GetPlaybackPosition();
    float directionMultiplyer = turtleCurve->GetFloatValue(currentAnimationTime);
    AddActorWorldOffset(EndPoint * FApp::GetDeltaTime() * directionMultiplyer * turtleSpeed);
}

void ATurtleBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATurtleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, FString::SanitizeFloat(tlComponent->GetTimelineLength(), 3));
    //GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, FString::SanitizeFloat(tlComponent->GetTimeline, 3));
}
