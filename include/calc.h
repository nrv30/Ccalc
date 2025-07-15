#pragma once



typedef struct {
    char name; // +, -, *, / , (, )
    int orgIndex;
    opPrec prec; // this is an enum
} Operator;
