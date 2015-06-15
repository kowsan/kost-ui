#ifndef NONREGISTEREDAWSUI_H
#define NONREGISTEREDAWSUI_H

#include <QWidget>

namespace Ui {
class NonRegisteredAWSUi;
}

class NonRegisteredAWSUi : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString armId READ armId WRITE setArmId NOTIFY armIdChanged)

public:
    explicit NonRegisteredAWSUi(QWidget *parent = 0);
    ~NonRegisteredAWSUi();

    QString armId() const
    {
        return m_armId;
    }

public slots:
    void setArmId(QString armId);

signals:
    void armIdChanged(QString armId);

private:
    Ui::NonRegisteredAWSUi *ui;
    QString m_armId;
};

#endif // NONREGISTEREDAWSUI_H
