struct operandos {
    int a;
    int b;
};

program CALCULADROA_PROG {
    version CALCULADORA_vers {
        int SUMAR(operandos) = 1;
    } = 1;
} = 0x20000001;