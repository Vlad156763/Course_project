#ifndef EX_H
#define EX_H
class ex {
    int CodeError = 0;
    const char* msg;
public:
    ex(const int& NumError, const char* msg = "") { this->CodeError = NumError; this->msg = msg; }
    int getErrorCode() const { return CodeError; }
    const char* getErrorMsg() const { return this->msg; }
};
#endif // !EX_H
