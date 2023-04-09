#include "console_view.h"

#include "storage_event.h"

struct StorageEvent;

void ConsoleView::Refresh(StorageEvent &context) {
    context.Handle();
}