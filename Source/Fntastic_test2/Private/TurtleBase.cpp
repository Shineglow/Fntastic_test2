// Fill out your copyright notice in the Description page of Project Settings.


#include "TurtleBase.h"
#include "Components/TimelineComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"

ATurtleBase::ATurtleBase()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ScenComponent"));
	SetRootComponent(sceneRoot);
	turtleSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurtleMesh"));
	turtleSkeletalMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	TimelineCallback.BindUFunction(this, FName("MoveTurtle"));
}

void ATurtleBase::InitTurtle(FVector endPoint, float speed, UCurveFloat* moveScale)
{
	turtleCurve = moveScale;
	turtleSpeed = speed;
	
	EndPoint = endPoint;
	StartPoint = GetTransform().GetLocation();
	
	direction = (EndPoint - StartPoint).GetSafeNormal();

	ConfigureTimeline();
	
}

void ATurtleBase::ConfigureTimeline() {
	if (turtleCurve)
	{
		turtleTimeline = new FTimeline();
		turtleTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
		turtleTimeline->SetTimelineLength(timelineLenghtOrTime);
		turtleTimeline->AddInterpFloat(turtleCurve, TimelineCallback);
		turtleTimeline->SetLooping(true);
		turtleTimeline->Play();
	}
}

void ATurtleBase::MoveTurtle(float value) {
	float c = turtleCurve->GetFloatValue(turtleTimeline->GetPlaybackPosition());
	FVector a = direction * turtleSpeed * FApp::GetDeltaTime() * (value);
	FVector b = (EndPoint - GetTransform().GetLocation());

	if (a.SizeSquared() > b.SizeSquared())
	{
		AddActorWorldOffset(b);
		turtleTimeline->SetLooping(false);
		turtleTimeline->Stop();
		return;
	}
	AddActorWorldOffset(a);
}

void ATurtleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	turtleTimeline->TickTimeline(DeltaTime);
}
