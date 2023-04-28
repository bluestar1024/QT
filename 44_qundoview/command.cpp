#include "command.h"
#include <QDebug>

AddCommand::AddCommand(int *count, QUndoCommand *parent)
{
    Q_UNUSED(parent);

    setText("执行了加1操作");
    cp_count = count;
}

void AddCommand::redo()
{
    (*cp_count)++;
    qDebug() << "redo:" << *cp_count << endl;
}

void AddCommand::undo()
{
    qDebug() << "undo:" << *cp_count << endl;
    (*cp_count)--;
}

AddCommand::~AddCommand()
{

}
