// Fill out your copyright notice in the Description page of Project Settings.

#include "FMathTestActor.h"


// Sets default values
AFMathTestActor::AFMathTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFMathTestActor::BeginPlay()
{
	Super::BeginPlay();


	// http://api.unrealengine.com/INT/API/Runtime/Core/Math/index.html

	//////////////////////////////////////////////////////////////////////
	//// I. Vector Addition and Scalar Multiplication

	// Initialize v0 and v1
	FVector v0(1, 2, -3);

	FVector v1;
	v1[0] = -4;
	v1[1] = 5;
	v1[2] = 6;

	// Vector Addition 벡터 더하기
	FVector v2 = v0 + v1;

	// Scalar Multiplication 스칼라 곱하기 벡터
	FVector v3 = 2.5f * v1;

	// Logoutput에 출력해보기
	// https://wiki.unrealengine.com/Logs,_Printing_Messages_To_Yourself_During_Runtime
	UE_LOG(LogTemp, Warning, TEXT("v0 = %s"), *v0.ToString());
	UE_LOG(LogTemp, Warning, TEXT("v1 = %s"), *v1.ToString());
	UE_LOG(LogTemp, Warning, TEXT("v0 + v1 = %s"), *v2.ToString());
	UE_LOG(LogTemp, Warning, TEXT("2.5 * v1 = %s"), *v3.ToString());

	// Screen에 출력해보기
	// https://api.unrealengine.com/INT/API/Runtime/Engine/Engine/UEngine/AddOnScreenDebugMessage/1/index.html
	FString msg0;
	msg0 = "v0 = " + v0.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, msg0);

	msg0 = "v1 = " + v1.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, msg0);

	msg0 = "v0 + v1 = " + v2.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, msg0);

	msg0 = "2.5 * v1 = " + v3.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, msg0);





	//////////////////////////////////////////////////////////////////////
	//// II. Normalize, Dot Product, and Cross Product

	// Normalizing (make a unit vector) 노말라이징 방법1
	FVector unit_v1 = v1;
	unit_v1.Normalize();

	// Normalizing (make a unit vector) 노말라이징 방법2
	// FVector unit_v1 = v1 / v1.Size();	// 0으로 나누어질 위험이 있음.	

	// Length 벡터 길이
	float length_v1 = v1.Size();
	float length_unit_v1 = unit_v1.Size();

	// Dot Product 내적 
	float dot_v0_v1 = FVector::DotProduct(v0, v1);

	// Cross Product 외적
	FVector cross_v0_v1 = FVector::CrossProduct(v0, v1);

	// Logoutput 에 출력해보기
	UE_LOG(LogTemp, Warning, TEXT("unit_v1 = %s"), *unit_v1.ToString());
	UE_LOG(LogTemp, Warning, TEXT("length_v1 = %f"), length_v1);
	UE_LOG(LogTemp, Warning, TEXT("length_unit_v1 = %f"), length_unit_v1);
	UE_LOG(LogTemp, Warning, TEXT("dot_v0_v1 = %f"), dot_v0_v1);
	UE_LOG(LogTemp, Warning, TEXT("cross_v0_v1 = %s"), *cross_v0_v1.ToString());

	// Screen에 출력해보기
	FString msg1;
	msg1 = "unit_v1 = " + unit_v1.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, msg1);

	msg1 = "length_v1 = " + FString::SanitizeFloat(length_v1);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, msg1);

	msg1 = "length_unit_v1 = " + FString::SanitizeFloat(length_v1);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, msg1);

	msg1 = "dot_v0_v1 = " + FString::SanitizeFloat(length_v1);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, msg1);

	msg1 = "cross_v0_v1 = " + cross_v0_v1.ToString();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, msg1);



	//////////////////////////////////////////////////////////////////////
	//// III. Transform and Vectors for Homogenious Coordinages

	FVector4 h_p(10, 10, 10, 1);	// 3D point in Homogenious Coordinates
	FVector4 h_v(10, 10, 10, 0);	// 3D vector in Homogenious Coordinates

									// Transformations
	FTransform T1, T2, T3;
	T1.SetTranslation( FVector(10, 200, -3) );
	T2.SetScale3D( FVector(1, 0.5, 2) );
	T3.SetRotation( FQuat( FVector(0, 1, 0), FMath::DegreesToRadians(30.) ) );

	// Composition
	FTransform T = T1*T2*T3;


	// Applying Transforms
	FVector4 h_p_t1 = T3.TransformFVector4( T2.TransformFVector4( T1.TransformFVector4(h_p) ) );

	FVector4 h_p_t2 = T.TransformFVector4(h_p);

	FVector4 h_v_t = T.TransformFVector4(h_v);




	UE_LOG(LogTemp, Warning, TEXT("T1 = %s"), *(T1).ToString());
	UE_LOG(LogTemp, Warning, TEXT("T1 Matrix Form = %s"), *(T1.ToMatrixWithScale()).ToString());

	UE_LOG(LogTemp, Warning, TEXT("T = %s"), *(T).ToString());
	UE_LOG(LogTemp, Warning, TEXT("T Matrix Form = %s"), *(T.ToMatrixWithScale()).ToString());;

	UE_LOG(LogTemp, Warning, TEXT("h_p_t1 = %s"), *(h_p_t1).ToString());
	UE_LOG(LogTemp, Warning, TEXT("h_p_t2 = %s"), *(h_p_t2).ToString());
	UE_LOG(LogTemp, Warning, TEXT("h_v_t = %s"), *(h_v_t).ToString());
	
}

// Called every frame
void AFMathTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float t = GetGameTimeSinceCreation();

	FTransform A, B, C;
	A.SetTranslation( FVector(sin(t)*100, cos(t)*100, 100) );
	B.SetScale3D( FVector(1, 1, 2) );
	C.SetRotation( FQuat( FVector(1, 0, 0), FMath::DegreesToRadians(45.) ) );

	FTransform T = A*B*C;
	SetActorTransform(T);
}

