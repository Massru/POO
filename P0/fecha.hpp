#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <iostream>
#include <ctime>

class Fecha{
public:
    //Contructor predeterminado o dia [, mes [, anno]]. 0 = "hoy"
    Fecha(int d = 0, int m = 0, int a = 0); //Valores predeterminados de izq. a der. obligatorio (si d tiene, m y a tienen que tener tmb pero si solo tiene a, d y m no tienen por que tener)
    Fecha(const char* c);

    //Constantes
    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037;

    //Funciones observadoras
    int dia() const {return dia_;};
    int mes() const {return mes_;}
    int anno() const {return anno_;}

    //Clase invalida
    class Invalida{
        public:
            Invalida(const char* inf);
            const char* por_que() const {return info_;};
        private:
            const char* info_;
    };

    //Conversion a const char*
    operator const char*() const;       //REVISAR

    //Operadores
    Fecha& operator++();
    Fecha& operator ++(int);
    Fecha& operator--();
    Fecha& operator--(int);
    Fecha& operator+=(int i);
    Fecha& operator-=(int i);

    Fecha& operator+(int i) const;
    Fecha& operator-(int i) const;

    //Destructor
    ~Fecha() = default;
private:
    int dia_, mes_, anno_;      //Atributos: dia, mes, año
    void valida();              //Valida los atributos (parte privada para que el usuaio vea este metodo(principio de ocultacion))
    int ultimo_dia();
};

bool operator ==(const Fecha& f1, const Fecha& f2);
bool operator !=(const Fecha& f1, const Fecha& f2);
bool operator <(const Fecha& f1, const Fecha& f2);
bool operator >(const Fecha& f1, const Fecha& f2);
bool operator <=(const Fecha& f1, const Fecha& f2);
bool operator >=(const Fecha& f1, const Fecha& f2);

#endif