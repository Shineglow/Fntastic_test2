// Fill out your copyright notice in the Description page of Project Settings.


#include "TurtleBase.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATurtleBase::ATurtleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	tlComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	ConfigureTimeline();
}


void ATurtleBase::ConfigureTimeline() {
    if (turtleCurve)
    {
        FOnTimelineFloat TimelineCallback;
        FOnTimelineEventStatic TimelineFinishedCallback;

        TimelineCallback.BindUFunction(this, FName("MoveTurtle"));
        TimelineFinishedCallback.BindUFunction(this, FName("TurtleRichFinish"));

        tlComponent = NewObject<UTimelineComponent>(this, FName("DoorAnimation"));
        tlComponent->SetLooping(true);
        tlComponent->AddInterpFloat(turtleCurve, TimelineCallback);
        tlComponent->SetTimelineFinishedFunc(TimelineFinishedCallback);
        tlComponent->RegisterComponent();
    }
}

// Called when the game starts or when spawned
void ATurtleBase::BeginPlay()
{
	Super::BeginPlay();

    ConfigureTimeline();
}

void ATurtleBase::MoveTurtle() {
    if (isOnFinish)
    {
        tlComponent->Stop();
        return;
    }
    float currentAnimationTime = MyTimeline->GetPlaybackPosition();
    float directionMultiplyer = turtleCurve->GetFloatValue(currentAnimationTime);
    AddActorWorldOffset(EndPoint * FApp::GetDeltaTime() * directionMultiplyer * turtleSpeed);
}

void ATurtleBase::TurtleRichFinish() {

}

// Called every frame
void ATurtleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

