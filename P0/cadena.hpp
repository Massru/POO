#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iostream>
#include <cstring>

class Cadena{
public:
    explicit Cadena(size_t tam = 0, char c = ' ');
    Cadena(const char* cadena);
    Cadena(const Cadena& Cadena);

    explicit operator const char*() const;
    size_t length() const;

    Cadena& operator =(const Cadena& c);
    Cadena& operator =(const char* c);
    Cadena operator +=(const Cadena& cadena);

    friend bool operator ==(const Cadena& cad1, const Cadena& cad2);
    friend bool operator !=(const Cadena& cad1, const Cadena& cad2);
    friend bool operator >(const Cadena& cad1, const Cadena& cad2);
    friend bool operator <(const Cadena& cad1, const Cadena& cad2);
    friend bool operator <=(const Cadena& cad1, const Cadena& cad2);
    friend bool operator >=(const Cadena& cad1, const Cadena& cad2);

    ~Cadena();
private:
    static char vacia[1];
    size_t tam_;
    char* s_;
};


Cadena operator +(const Cadena& cad1, const Cadena& cad2);


#endif