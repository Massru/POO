#include "fecha.hpp"

//Constructor predeterminado de Fecha
Fecha::Fecha(int d /* = 0*/, int m /* = 0*/, int a /* = 0*/): dia_(d), mes_(m), anno_(a)
{
    if (d != 0 && m != 0 && a != 0)
        valida();
    else{
    std::time_t tiempo_calendario = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);

    if (dia_ == 0)
        dia_ = tiempo_descompuesto->tm_mday;
    if (mes_ == 0)
        mes_ = tiempo_descompuesto->tm_mon + 1; // tm_mon: 0 (ene)..11 (dic)
    if (anno_ == 0)
        anno_ = tiempo_descompuesto->tm_year + 1900; // tm_year: a~nos desde 1900

    valida();
    }
}

//Constructor a partir de cadena de caracteres
Fecha::Fecha(const char* cadena)
{
    int dia, mes, anno;
    if (std::sscanf(cadena, "%d/%d/%d", dia, mes, anno) != 3){
        Fecha::Invalida formato("Error en el formato de la fecha");
        throw formato;
    }
    else
    {
        Fecha f(dia, mes, anno);
        dia_ = f.dia();
        mes_ = f.mes();
        anno_ = f.anno();
    }
    
}

//Conversor fecha const char*
Fecha::operator const char *() const{

    std::locale::global(std::locale("es_ES.utf8"));
    char *aux = new char[100];

    std::time_t tiempo_calendario = std::time(nullptr);
    std::tm* f = std::localtime(&tiempo_calendario);

    f->tm_mday = dia_;
    f->tm_mon = mes_ - 1;
    f->tm_year = anno_ - 1900;
    mktime(f);

    strftime(aux, 100, "%A %e de %B de %Y", f);
    return aux;

}

//Funciones privadas para comprobar la fecha
void Fecha::valida(){
    if (anno_ < AnnoMinimo || anno_ > AnnoMaximo){
        Fecha::Invalida a_inval("Año invalido");
        throw a_inval;
    }
    if (dia_ < 1 || dia_ > ultimo_dia()){
        Fecha::Invalida d_inval("Día invalido");
        throw d_inval;
    }
}

int Fecha::ultimo_dia(){
    if(mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12)
        return 31;
    else if(mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11)
        return 30;
    else if(mes_ == 2){
        if((anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)))
            return 29;
        else
            return 28;
    }
    else{
        Fecha::Invalida m_inval("Mes invalido");
        throw m_inval;
        return 0;
    }
}

//Operadores
Fecha& Fecha::operator+=(int i){
    struct tm t={};
    t.tm_mday = dia_;
    t.tm_mon = mes_ - 1;
    t.tm_year = anno_ - 1900;
    t.tm_mday += i;

    mktime(&t);

    this->dia_ = t.tm_mday;
    this->mes_ = t.tm_mon + 1;
    this->anno_ = t.tm_year + 1900;

    valida();

    return *this;
}

Fecha& Fecha::operator-=(int i){
    *this += -i;
    return *this;
}

Fecha& Fecha::operator++(){
    *this += 1;
    return *this;
}

Fecha& Fecha::operator++(int){
    Fecha f;
    f = *this;
    *this += 1;
    return f;
}

Fecha& Fecha::operator--(){
    *this += -1;
    return *this;
}

Fecha& Fecha::operator--(int){
    Fecha f;
    f = *this;
    *this += -1;
    return f;
}

Fecha& Fecha::operator+(int i) const{
    Fecha f;
    f = *this;
    f += i;
    return f;
}

Fecha& Fecha::operator-(int i) const{
    Fecha f;
    f = *this;
    f += -i;
    return f;
}

bool operator==(const Fecha& f1, const Fecha& f2){
    return (f1.anno() == f2.anno() && f1.mes() == f2.mes() && f1.dia() == f2.dia());
}

bool operator!=(const Fecha& f1, const Fecha& f2){
    return !(f1==f2);
}

bool operator <(const Fecha& f1, const Fecha& f2){

    return (f1.anno() < f2.anno() || (f1.anno() == f2.anno() && (f1.mes() < f2.mes() || (f1.mes() == f2.mes() && f1.dia() < f2.dia()))));

}

bool operator >(const Fecha& f1, const Fecha& f2){

    return f2 < f1;

}

bool operator <=(const Fecha& f1, const Fecha& f2){

    return !(f2 < f1);

}

bool operator >=(const Fecha& f1, const Fecha& f2){

    return !(f1 < f2);

}