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

protected:
	UFUNCTION(BlueprintCallable, Category = "Class")
	virtual void ConfigureTimeline();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveTurtle();

	void TurtleRichFinish();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTimelineComponent* tlComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	UCurveFloat* turtleCurve;

	UFUNCTION()
	void StartMove();

	UFUNCTION()
	void StopMove();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndPoint;

	bool isOnFinish;
	float turtleSpeed;
	UTimelineComponent* MyTimeline;
};
