// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "TurtleBase.generated.h"


UCLASS()
class FNTASTIC_TEST2_API ATurtleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurtleBase();

	UFUNCTION(BlueprintCallable)
	void StartAnimation();

protected:
	UFUNCTION(BlueprintCallable, Category = "Class")
	virtual void ConfigureTimeline();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void InitTurtle(FVector endPoint, float speed, UCurveFloat* moveScale);

	void MoveTurtle(float value);

	void AddTurtleOffset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTimelineComponent* tlComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	UCurveFloat* turtleCurve;

	UPROPERTY()
	class UStaticMeshComponent* turtleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float turtleSpeed;

private:
	bool isAnimationStart = false;

	float timelineLenghtOrTime = 1.5f;
};
