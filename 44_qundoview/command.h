#ifndef COMMAND_H
#define COMMAND_H

#include <QUndoCommand>
#include <QUndoView>

class AddCommand : public QUndoCommand
{
public:
    AddCommand(int *count, QUndoCommand *parent = nullptr);
    ~AddCommand();

    void redo() override;
    void undo() override;

    int *cp_count;
};

#endif // COMMAND_H
