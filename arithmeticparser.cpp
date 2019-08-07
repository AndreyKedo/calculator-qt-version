#include "arithmeticparser.h"

ArithmeticParser* ArithmeticParser::instance = nullptr;

ArithmeticParser* ArithmeticParser::InstanceObject()
{
    if(instance == nullptr)
        instance = new ArithmeticParser();
    return instance;
}

QString ArithmeticParser::ToParse(QString& str){
    divideByZero = false;
    double outpute;
    Str = "(" + str + ")";
    if(IfBrackEqual()){
        outpute = ExpressionHandling();
        Str.clear();
        if(divideByZero)
            return "Деление на ноль не возможно";
        QString result = QString::number(outpute);
        return  result.at(0) == '-' ? result.replace('-','_') : result;
    }
    return "Нехватает скобок";
}

double ArithmeticParser::ExpressionHandling(){
    int i = 0;
    QChar chr;
    QStack<double> number;
    QStack<QChar> operation;
    while (i < Str.size()) {
        chr = Str.at(i);
        if(chr.isDigit() || chr == C_NEGATIVE){
            number.push(NumberConcationation(i));
        }
        else if (operation.size() == 0 || chr == '(') {
            operation.push(chr);
        }
        else if (chr == '+' || chr == '-' || chr == '*' || chr == '/') {
            if(PriorityOperation(chr) > PriorityOperation(operation.first())){
                operation.push(chr);
            }
            else if (PriorityOperation(chr) == PriorityOperation(operation.top())) {
                while (operation.size() != 0 && (PriorityOperation(chr) == PriorityOperation(operation.top()))) {
                    if(divideByZero)
                        break;
                    Calc(operation.pop(), number);
                }
                if(operation.size() != 0 && (PriorityOperation(chr) > PriorityOperation(operation.top()))){
                    operation.push(chr);
                }
            }
            else {
                while (PriorityOperation(chr) < PriorityOperation(operation.top())) {
                    if(divideByZero)
                        break;
                    Calc(operation.pop(), number);
                }
                operation.push(chr);
            }
        }
        else {
            while (operation.top() != '(') {
                if(divideByZero)
                    break;
                Calc(operation.pop(), number);
            }
            operation.pop();
        }
        i++;
    }
    return number.pop();
}

double ArithmeticParser::NumberConcationation(int& index){
    int i = index;
    bool isNegative = false;
    QString buffer;

    if(Str.at(i) == C_NEGATIVE){
        isNegative = true;
        i++;
    }

    short countComma = 0;
    while (Str.at(i).isDigit() || Str.at(i) == C_FRACTION) {
        if(Str.at(i) == C_FRACTION)
            countComma++;
        if(countComma == 2)
            break;
        buffer += Str.at(i);
        i++;
    }
    index = --i;
    return isNegative ? buffer.toDouble() * -1 : buffer.toDouble();
}

void ArithmeticParser::Calc(const QChar &chr, QStack<double> &number){
    double buffer = number.pop();

    switch (chr.unicode()) {
        case '+':
            number.push(number.pop() + buffer);
        break;
        case '-':
            number.push(number.pop() - buffer);
        break;
        case '*':
            number.push(number.pop() * buffer);
        break;
        case '/':
        if(buffer == 0.0){
            divideByZero = true;
            break;
        }
        number.push(number.pop() / buffer);
        break;
    }
}

unsigned short ArithmeticParser::PriorityOperation(QChar& chr){
    switch (chr.unicode()) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

bool ArithmeticParser::IfBrackEqual(){
    return Str.count('(') == Str.count(')');
}

ArithmeticParser::~ArithmeticParser(){
    delete this->instance;
}
