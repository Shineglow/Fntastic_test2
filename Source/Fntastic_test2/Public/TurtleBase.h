// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "TurtleBase.generated.h"


UCLASS()
class FNTASTIC_TEST2_API ATurtleBase : public AActor
{
	GENERATED_BODY()
	
public:
	ATurtleBase();

	UFUNCTION(BlueprintCallable)
	void InitTurtle(FVector endPoint, float speed, UCurveFloat* moveScale);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* turtleSkeletalMesh;
	
protected:

	UFUNCTION(BlueprintCallable)
	virtual void ConfigureTimeline();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* turtleCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* sceneRoot;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimeline* turtleTimeline;
	
	UPROPERTY()
	FVector direction;

	UPROPERTY()
	FVector startPoint;

	UPROPERTY()
	FVector deltaDistance;

	UPROPERTY()
	FVector endPoint;

	UPROPERTY()
	float turtleSpeed;
	
public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void MoveTurtle(float value);

	FOnTimelineFloat TimelineCallback{};
	
	float timelineLenghtOrTime = 1.5f;
};
