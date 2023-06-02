#ifndef IMAGEEDIT_H
#define IMAGEEDIT_H

class ImageEdit
{

public:
    virtual void execute() = 0;

    virtual void undo() = 0;

    virtual void redo() = 0;

    virtual ~ImageEdit() = default;

};


#endif // IMAGEEDIT_H
