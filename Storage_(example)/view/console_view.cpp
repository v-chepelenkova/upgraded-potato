#include "console_view.h"

#include "storage_event.h"

struct StorageEventHandler;

void ConsoleView::Refresh(EventHandler &context) {
    context.Handle();
}