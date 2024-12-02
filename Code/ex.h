#include <qapplication.h>
#ifndef EX_H
#define EX_H
class ex {
    int CodeError = 0;
public:
    ex(const int& NumError) { this->CodeError = NumError; }
    int getErrorCode() const { return CodeError; }
};
#endif // !EX_H
