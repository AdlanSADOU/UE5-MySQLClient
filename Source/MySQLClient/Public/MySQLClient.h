// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MySQLClient.generated.h"

struct MYSQL;

MYSQLCLIENT_API DECLARE_LOG_CATEGORY_EXTERN(MySQLClient, Log, All);

UENUM()
enum ENetAsyncStatus {
    ASYNC_COMPLETE = 0,
    ASYNC_NOT_READY,
    ASYNC_ERROR,
    ASYNC_COMPLETE_NO_MORE_RESULTS
};

/**
 *
 */
UCLASS()
class MYSQLCLIENT_API UMySQLClient : public UObject
{
    GENERATED_BODY()

public:
    UMySQLClient();
    ~UMySQLClient();

    UFUNCTION()
        void Init();
      
    bool Connect(const TCHAR *host, const TCHAR *user, const TCHAR *password);
    void Close();
    void LogLastError();
    TCHAR *GetLastError();
    void Query(const TCHAR *query);
    ENetAsyncStatus AsyncQuery(const TCHAR *query);

private:
    MYSQL *mysql;

};
