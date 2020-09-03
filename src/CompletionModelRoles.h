#pragma once

#include <QAbstractItemModel>

// Interface for completion models
namespace CompletionModel {

// Start at Qt::UserRole * 2 to prevent clashes
enum Roles
{
        CompletionRole = Qt::UserRole * 2, // The string to replace the active completion
        SearchRole,                        // String completer uses for search
};

}
