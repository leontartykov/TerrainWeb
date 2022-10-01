#include <iostream>

#include "core/entry/entry.h"
#include "core/entry/app_command/app_command.h"
#include "core/entry/app_facade/app_facade.h"

int main()
{
    std::unique_ptr<EntrySystem> system;
    system = std::unique_ptr<EntrySystem>(new EntrySystem());
    system->enter_system();

    return 0;
}
