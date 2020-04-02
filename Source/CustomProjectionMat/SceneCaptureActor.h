// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneCaptureActor.generated.h"

class USceneCaptureComponent2D;

UCLASS()
class CUSTOMPROJECTIONMAT_API ASceneCaptureActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneCaptureActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetUseCustomProjMat(bool useCustomProjMat);

	UFUNCTION(BlueprintGetter)
	UTextureRenderTarget2D* GetRenderTarget()
	{
		return RenderTarget;
	}
	
	UFUNCTION(BlueprintCallable)
	void SetRenderTarget(UTextureRenderTarget2D* renderTarget);

public:
	UPROPERTY(EditAnywhere)
	USceneCaptureComponent2D* Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetRenderTarget, BlueprintSetter = SetRenderTarget)
	UTextureRenderTarget2D* RenderTarget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintSetter = SetUseCustomProjMat)
	bool bUseCustomProjMat = false;

};
