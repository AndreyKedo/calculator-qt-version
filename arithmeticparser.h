#ifndef ARITHMETICPARSER_H
#define ARITHMETICPARSER_H

#include <QStack>
#include <QString>

#define C_FRACTION '.'
#define C_NEGATIVE '_'

class ArithmeticParser
{
    static ArithmeticParser* instance;
    ~ArithmeticParser();
    QString Str;
    bool divideByZero;
    double ExpressionHandling();
    double NumberConcationation(int&);
    void Calc(const QChar&, QStack<double>&);
    unsigned short PriorityOperation(QChar&);
    bool IfBrackEqual();
public:
    static ArithmeticParser* InstanceObject();
    QString ToParse(QString&);
};

#endif // ARITHMETICPARSER_H
