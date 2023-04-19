// Fill out your copyright notice in the Description page of Project Settings.


#include "MySQLClient.h"
#include "CoreMinimal.h"

// https://docs.unrealengine.com/4.26/en-US/ProductionPipelines/BuildTools/UnrealBuildTool/ThirdPartyLibraries/ @C++ Warnings And Errors
THIRD_PARTY_INCLUDES_START
#include "MySQLClientLib/include/mysql.h"
THIRD_PARTY_INCLUDES_END

DEFINE_LOG_CATEGORY(MySQLClient);

UMySQLClient::UMySQLClient()
{
}

UMySQLClient::~UMySQLClient()
{
}

void UMySQLClient::Init()
{
    mysql = mysql_init(nullptr);

    if (!mysql)
    {
        GetLastError();
        return;
    }

    UE_LOG(MySQLClient, Warning, TEXT("Initialized with mysql library version: %s"), *FString(mysql_get_client_info()));
}

bool UMySQLClient::Connect(const TCHAR *host, const TCHAR *user, const TCHAR *password)
{
    if (!mysql)
    {
        GetLastError();
        return false;
    }

    ///* TODO:
    //* Upon connection, mysql_real_connect() sets the reconnect flag (part of the MYSQL structure) to a value of 0.
    //* You can use the MYSQL_OPT_RECONNECT option to mysql_options() to control reconnection behavior.
    //* Setting the flag to 1 causes the client to attempt reconnecting to the server before giving up
    //* if a statement cannot be performed because of a lost connection.
    //*/
    if (!mysql_real_connect(mysql, TCHAR_TO_ANSI(host), TCHAR_TO_ANSI(user), TCHAR_TO_ANSI(password), nullptr, 0, nullptr, 0))
    {
        GetLastError();
        return false;
    }

    return true;
}

void UMySQLClient::Close()
{
    //// mysql_real_connect() counterpart. Closes the connection
    mysql_close(mysql);
    mysql_library_end();
    UE_LOG(MySQLClient, Warning, TEXT("shutdown"));
}

TCHAR *UMySQLClient::GetLastError()
{
    return ANSI_TO_TCHAR(mysql_error(mysql));
}

/*
    Convinience function that call UE_LOG with GetLastError()
*/
void UMySQLClient::LogLastError()
{
    UE_LOG(MySQLClient, Error, TEXT("%s"), GetLastError());
}

void UMySQLClient::Query(const TCHAR *query)
{
    if (mysql_query(mysql, TCHAR_TO_ANSI(query)))
    {
        LogLastError();
    }
}

ENetAsyncStatus UMySQLClient::AsyncQuery(const TCHAR *query)
{
    // TODO: what could go wrong?
    // TCHAR_TO_ANSI 126 character default limit ?
    // short lived temp TCHAR allocation?
    const char *ansiQueryStr = TCHAR_TO_ANSI(query);

    return StaticCast<ENetAsyncStatus>(mysql_real_query_nonblocking(mysql, ansiQueryStr, strlen(ansiQueryStr)));
}
