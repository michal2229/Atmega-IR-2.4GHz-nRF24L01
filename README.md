# Atmega-IR-2.4GHz-nRF24L01

Projekt obejmuje komunikację pomiędzy dwoma uC atmega 328p za pomocą dwóch dróg:
* między modułami nRF24L01,
* między nadajnikiem i odbiornikiem podczerwieni.

Sygnał wysyłany przez podczerwień z pilota RTV przechwytywany jest przez odbiornik IR, następnie odebrany kod inkrementowany jest o jeden.
Po inkrementacji kod wysyłany jest do drugiego modułu poprzez radio 2.4GHz. Drugi moduł po odbiorze wysyła go spowrotem za pomocą diody IR.

Jest to test jednoczesnej komunikacji przez radio i IR przy użyciu bibliotek Arduino na samodzielnym mikrokontrolerze (bez płytki Arduino).
