#include <chrono>
#include "Fecha.h"

Fecha::Fecha() : _dia(1), _mes(1), _anio(2000) {}

Fecha::Fecha(int dia, int mes, int anio) : _dia(dia), _mes(mes), _anio(anio) {}

void Fecha::setDia(int dia) {
    _dia = dia;
}

void Fecha::setMes(int mes) {
    _mes = mes;
}

void Fecha::setAnio(int anio) {
    _anio = anio;
}

int Fecha::getDia() const {
    return _dia;
}

int Fecha::getMes() const {
    return _mes;
}

int Fecha::getAnio() const {
    return _anio;
}

void Fecha::setCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&now_c);

    _dia = localTime->tm_mday;
    _mes = localTime->tm_mon + 1;
    _anio = localTime->tm_year + 1900;
}
