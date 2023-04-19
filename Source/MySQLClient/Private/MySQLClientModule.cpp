#include "MySQLClientModule.h"
#include "Modules/ModuleManager.h"


#define LOCTEXT_NAMESPACE "FMySQLClientModule"

void FMySQLClientModule::StartupModule()
{
    // Put your module initialization code here
}

void FMySQLClientModule::ShutdownModule()
{
    // Put your module termination code here
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMySQLClientModule, MySQLClient)

