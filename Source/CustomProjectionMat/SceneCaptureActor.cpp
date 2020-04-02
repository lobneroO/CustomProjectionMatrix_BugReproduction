// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneCaptureActor.h"
#include <Components/SceneCaptureComponent2D.h>
#include "Engine/TextureRenderTarget2D.h"

// Sets default values
ASceneCaptureActor::ASceneCaptureActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Camera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Sensor Camera"));
	if (RootComponent)
	{
		Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}
	else
	{
		RootComponent = Camera;
	}
	Camera->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;
	Camera->bCaptureEveryFrame = true;
	if (RenderTarget)
	{
		Camera->TextureTarget = RenderTarget;
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString("No render target during Construction!"));
		}
	}
	//RenderTarget = NewObject<UTextureRenderTarget2D>();
	//RenderTarget->ClearColor = FLinearColor::Black;

	//RenderTarget->InitAutoFormat(512, 512);
}

// Called when the game starts or when spawned
void ASceneCaptureActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASceneCaptureActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Camera->TextureTarget)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString("No render target!"));
		Camera->TextureTarget = RenderTarget;
	}
}

void ASceneCaptureActor::SetUseCustomProjMat(bool useCustomProjMat)
{
	bUseCustomProjMat = useCustomProjMat;

	FVector2D fov;

	if (!Camera->bUseCustomProjectionMatrix && bUseCustomProjMat)
	{
		fov = FVector2D(Camera->FOVAngle, Camera->FOVAngle);
	}

	Camera->bUseCustomProjectionMatrix = bUseCustomProjMat;

	if (bUseCustomProjMat)
	{
		Camera->CustomProjectionMatrix = FPerspectiveMatrix::FPerspectiveMatrix(fov.X, fov.Y, 1, 1, 1, 10000);
	}
}

void ASceneCaptureActor::SetRenderTarget(UTextureRenderTarget2D* renderTarget)
{
	RenderTarget = renderTarget;
	Camera->TextureTarget = RenderTarget;
}
