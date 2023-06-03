#ifndef EDITINGMANAGER_H
#define EDITINGMANAGER_H

#include "imageedit.h"
#include <stack>
#include <memory>

typedef std::stack<std::shared_ptr<ImageEdit>> commandStack;


class EditingManager
{

private:
    commandStack undoStack;
    commandStack redoStack;

public:

    // Editing Commands
    void execute(const std::shared_ptr<ImageEdit>& command);
    void undo();
    void redo();

    // Verifiers
    bool isUndoStackEmpty();
    bool isRedoStackEmpty();
};

#endif // EDITINGMANAGER_H
