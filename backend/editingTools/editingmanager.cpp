#include "editingmanager.h"

void EditingManager::execute(const std::shared_ptr<ImageEdit>& command)
{
    // Clear the Stack
    redoStack = commandStack();
    command->execute();
    undoStack.push(command);
}


void EditingManager::undo()
{
    if(!undoStack.empty())
    {
        undoStack.top()->undo();
        redoStack.push(undoStack.top());
        undoStack.pop();
    }
}

void EditingManager::redo()
{
    if(!redoStack.empty())
    {
        redoStack.top()->redo();
        undoStack.push(redoStack.top());
        redoStack.pop();
    }
}


bool EditingManager::isUndoStackEmpty()
{
    if(undoStack.empty())
    {
        return true;
    }
    else{
        return false;
    }
}


bool EditingManager::isRedoStackEmpty()
{
    if(redoStack.empty())
    {
        return true;
    }
    else{
        return false;
    }
}
