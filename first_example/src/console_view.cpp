#include "console_view.h"

#include "inhabitant.h"

void ConsoleView::Refresh(Inhabitant *context) {
    context->Show();
}