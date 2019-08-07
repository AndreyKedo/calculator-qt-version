#include "viewmodel.h"

ViewModel::ViewModel(QObject *parent) : QObject(parent)
{
    parse = ArithmeticParser::InstanceObject();
}

QString ViewModel::getExpression() const{
    return expression;
}

void ViewModel::setResult(const QString& result){
    expression.clear();
    expression = result;
    emit expressionPropetyChanged(result);
}

void ViewModel::setExpression(const QString& str){
    expression.append(str);
    emit expressionPropetyChanged(str);
}

void ViewModel::calcButton(){
    setResult(parse->ToParse(expression));
}

void ViewModel::clearButton(){
    if(expression.length() != 0){
        expression.clear();
        emit expressionPropetyChanged();
    }
}

QStringList ViewModel::getExpressionHistory() const
{
    return m_expressionHistory;
}

void ViewModel::setExpressionHistory(const QStringList &expressionHistory)
{
    m_expressionHistory = expressionHistory;
}

QStringList ViewModel::getExpressionHistory() const
{
    return m_expressionHistory;
}

void ViewModel::setExpressionHistory(const QStringList &expressionHistory)
{
    m_expressionHistory = expressionHistory;
}

void ViewModel::operationButton(const QString &str){
    setExpression(str);
}

void ViewModel::numberButton(const QString& str){
    setExpression(str);
}
