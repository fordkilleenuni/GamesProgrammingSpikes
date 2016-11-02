// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "VectorMathAPI.generated.h"

UCLASS()
class SCENE_API AVectorMathAPI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVectorMathAPI();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(BlueprintReadWrite)
	float x;

	UPROPERTY(BlueprintReadWrite)
	float y;

	UPROPERTY(BlueprintReadWrite)
	float z;

	UFUNCTION(BlueprintCallable, Category = "VectorMathAPI")
	void AddVector(float x2, float y2, float z2);

	UFUNCTION(BlueprintCallable, Category = "VectorMathAPI")
	void SubtractVector(float x2, float y2, float z2);

	UFUNCTION(BlueprintCallable, Category = "VectorMathAPI")
	void MultiplyVector(float scalar);

	UFUNCTION(BlueprintCallable, Category = "VectorMathAPI")
	void DivideVector(float scalar);

	UFUNCTION(BlueprintCallable, Category = "VectorMathAPI")
	float DotProduct(float x2, float y2, float z2);
};
