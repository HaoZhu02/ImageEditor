#include "inputstringdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>

InputStringDialog::InputStringDialog(const QList<QString>& fields, QWidget* parent) : QDialog(parent), fields(fields)
{
    QFormLayout* layout = new QFormLayout(this);

    for (const QString& field : fields) {
        QLabel* label = new QLabel(field, this);
        QLineEdit* edit = new QLineEdit(this);
        layout->addRow(label, edit);
        values << edit;
    }

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);

    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &InputStringDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &InputStringDialog::reject);

    setLayout(layout);
}

QList<QString> InputStringDialog::getStringFields(QWidget* parent, const QList<QString>& fields, bool* ok)
{
    InputStringDialog* dialog = new InputStringDialog(fields, parent);

    QList<QString> list;

    bool okInput = dialog->exec();

    if (okInput) {
        *ok = okInput;
        foreach (auto value, dialog->values) {
            list << value->text();
        }
    }

    dialog->deleteLater();
    return list;
}
