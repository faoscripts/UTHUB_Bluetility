// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

void UMyBlueprintFunctionLibrary::ListAssetDependencies()
{
    // Obtener referencia al módulo de AssetRegistry
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

    TArray<FAssetData> AllAssets;
    AssetRegistry.GetAllAssets(AllAssets, true);

    FString Output;
    for (const FAssetData& Asset : AllAssets)
    {
        TArray<FName> Dependencies;
        AssetRegistry.GetDependencies(Asset.PackageName, Dependencies);

        if (Dependencies.Num() > 0)
        {
            Output += FString::Printf(TEXT("%s [ROOT]\n"), *Asset.AssetName.ToString());
            for (const FName& Dependency : Dependencies)
            {
                Output += FString::Printf(TEXT(" |- %s\n"), *Dependency.ToString());
            }
        }
    }

    FString FilePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Logs"), FString::Printf(TEXT("RefLogOut_%s.log"), *FDateTime::Now().ToString(TEXT("%Y%m%d"))));
    FFileHelper::SaveStringToFile(Output, *FilePath);

    // Mostrar notificación en pantalla
    FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("Lista de dependencias exportada correctamente.")));
}
