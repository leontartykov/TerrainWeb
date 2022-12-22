#include <gtest/gtest.h>

#include "core/entry/entry.h"

TEST(test_entry_system_proxy_to_actions_admin, positive)
{
    std::unique_ptr<EntrySystem> system;

    system = std::make_unique<EntrySystem>();
    system->enter_system();
}
