// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealtChange, AActor*, InstigatorActor, class USAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASTEROIDREMAKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="Attribute")
	static USAttributeComponent* GetAttribute(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category="Attribute")
	static bool IsActorAlive(AActor* Actor);
	
	USAttributeComponent();

protected:

	UPROPERTY(EditDefaultsOnly, Replicated, BlueprintReadOnly, Category="Attribute")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, Replicated, BlueprintReadOnly, Category="Attribute")
	float Health;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastHealthChange(AActor* InstigatorActor, float NewValue, float Delta);
	
public:	

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealtChange OnHealtChange;

	UFUNCTION(BlueprintCallable, Category="Attribute")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

	UFUNCTION(BlueprintCallable, Category="Attribute")
	bool IsFullHealth() const;

	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category="Attribute")
	float GetHealth() const;
		
};
