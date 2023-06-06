#ifndef INPUTSTRINGDIALOG_H
#define INPUTSTRINGDIALOG_H


#include <QLineEdit>
#include <QDialog>

class QLabel;

class InputStringDialog : public QDialog
{
    Q_OBJECT
public:
    static QList<QString> getStringFields(QWidget* parent, const QList<QString>& fields, bool* ok);

private:
    explicit InputStringDialog(const QList<QString>& fields, QWidget* parent = nullptr);
    QList<QLineEdit*> values;
    QList<QString> fields;
};

#endif // INPUTSTRINGDIALOG_H
