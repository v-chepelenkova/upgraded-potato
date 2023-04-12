#include "console_view.h"

#include "storage_event.h"

struct StorageEventHandler;

void ConsoleView::Refresh(const EventVariant &context) {
  auto handler = StorageEventHandler(context);
  handler.Handle();
}