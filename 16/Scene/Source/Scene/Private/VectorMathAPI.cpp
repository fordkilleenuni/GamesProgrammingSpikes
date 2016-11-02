// Fill out your copyright notice in the Description page of Project Settings.

#include "Scene.h"
#include "VectorMathAPI.h"

// Sets default values
AVectorMathAPI::AVectorMathAPI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	x = 0;
	y = 0;
	z = 0;
}

// Called when the game starts or when spawned
void AVectorMathAPI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVectorMathAPI::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AVectorMathAPI::AddVector(float x2, float y2, float z2)
{
	x += x2;
	y += y2;
	z += z2;
}

void AVectorMathAPI::SubtractVector(float x2, float y2, float z2)
{
	x -= x2;
	y -= y2;
	z -= z2;
}

void AVectorMathAPI::MultiplyVector(float scalar)
{
	x = x * scalar;
	y = y * scalar;
	z = z * scalar;
}

void AVectorMathAPI::DivideVector(float scalar)
{
	x = x / scalar;
	y = y / scalar;
	z = z / scalar;
}

float AVectorMathAPI::DotProduct(float x2, float y2, float z2)
{
	return (x * x2) + (y * y2) + (z * z2);
}