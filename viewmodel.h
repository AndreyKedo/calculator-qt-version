#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include "arithmeticparser.h"

class ViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString expression READ getExpression WRITE setExpression NOTIFY expressionPropetyChanged)
public:
    explicit ViewModel(QObject *parent = nullptr);
    QString getExpression() const;
    void setExpression(const QString&);
    void setResult(const QString&);
    /*Обработчики событий*/
    Q_INVOKABLE void calcButton();
    Q_INVOKABLE void operationButton(const QString&);
    Q_INVOKABLE void numberButton(const QString&);
    Q_INVOKABLE void clearButton();
signals:
    void expressionPropetyChanged(const QString& = nullptr);
private:
    QStringList m_expressionHistory;
    ArithmeticParser *parse;
    QString expression;
};

#endif // VIEWMODEL_H
