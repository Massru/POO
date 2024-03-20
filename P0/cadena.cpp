#include "cadena.hpp"

char Cadena::vacia[1] = {'\0'};

//Constructor general
Cadena::Cadena(size_t tam, char c) : tam_(tam)
{
    if (tam_ > 0)
    {
        s_ = new char[tam_ + 1];
        for (size_t i = 0; i < tam_; i++)
        {
            s_[i] = c;
        }
        s_[tam_] = '\0';
    }
    else
    {
        s_ = vacia;
    }
}

//Constructor de copia
Cadena::Cadena(const Cadena& cad) : tam_(cad.tam_)
{
    if(tam_ > 0)
    {
        s_ = new char[tam_ + 1];
        strcpy(s_, cad.s_);
        s_[tam_ + 1] = '\0';
    }
    else
    {
        s_ = vacia;
    }
    
}

//Conatructor a partir de const char*
Cadena::Cadena(const char* str) : tam_(strlen(str))
{
    s_ = new char[tam_ + 1];
    strcpy(s_, str);
    s_[tam_ + 1] = '\0';
}

//
Cadena& Cadena::operator =(const Cadena& otra)
{
    if(this != &otra)
    {
        if(tam_ > 0)
            delete[] s_;
        tam_ = otra.tam_;
        if(otra.tam_ > 0)
        {
            s_ = new char[tam_ + 1];
            strcpy(s_, otra.s_);
            s_[tam_ + 1] = '\0';
        }
        else
            s_ = vacia;
    }
}

//Caracteres de una cadena
size_t Cadena::length() const
{
    return tam_;
}

//Operadores lógicos
bool operator ==(const Cadena& cad1, const Cadena& cad2)
{
    return !strcmp(cad1, cad2);
}

bool operator !=(const Cadena& cad1, const Cadena& cad2)
{
    return strcmp(cad1, cad2);
}

bool operator >(const Cadena& cad1, const Cadena& cad2)
{
    return (strcmp(cad1, cad2) > 0);
}

bool operator <(const Cadena& cad1, const Cadena& cad2)
{
    return cad2 > cad1;
}

bool operator >=(const Cadena& cad1, const Cadena& cad2)
{
    return !(cad1 > cad2);
}

bool operator <=(const Cadena& cad1, const Cadena& cad2)
{
    return !(cad2 > cad1);
}

Cadena operator +(const Cadena& cad1, const Cadena& cad2)
{
    Cadena aux(cad1);
    return aux += cad2;
}

//Destructor
Cadena::~Cadena()
{
    if(tam_ > 0)
    {
    delete[] s_;
    }
}

