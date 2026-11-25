# Прошивки AVTOSTAR Home

Среда разработки — PlatformIO, Arduino Framework. В репозитории находятся конфигурации сборки и кодек пакета UART/RS-485. Функциональные драйверы GPIO, ESP-NOW, RS-485, Web, OTA и привязки устройств разрабатываются по [дорожной карте](../docs/roadmap.md).

## Конфигурации сборки

```sh
cd firmware
pio run -e switch2_w
pio run -e switch2_wr
pio run -e relay2_w
pio run -e relay2_wr
pio run -e control
```

| Окружение | Платформа | Плата PlatformIO |
|---|---|---|
| switch2_w, switch2_wr | espressif8266 | esp12e |
| relay2_w, relay2_wr | espressif8266 | esp12e |
| control | espressif32 | esp32-s3-devkitc-1 |

Конфигурация ESP-12F использует целевую плату esp12e; параметры Flash определяются конкретным модулем. Флаг AVTOSTAR_RS485_ENABLED обозначает вариант комплектации, а не наличие реализованного драйвера шины.

Текущая программа выводит диагностические сообщения через UART0. При разработке WR-прошивки необходимо отделить диагностический вывод от кадров RS-485.

## Отладочный модуль ESP-12F

[Схема, распиновка и программирование](../hardware/esp12f-debug-module/README.md).

GPIO1 — TXD, GPIO3 — RXD, GPIO16 — направление MAX3485. LOW — приём, HIGH — передача. Перед подключением программатора снять перемычку J1.4–J1.5; уровни UART — 3,3 В. После прошивки отключить программатор, вернуть перемычку и выполнить RESET.

## Тест кодека на ПК

Из корня репозитория:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic -I firmware/include firmware/test/test_protocol.cpp -o /tmp/avtostar-protocol-test
/tmp/avtostar-protocol-test
```

Тест проверяет кодирование и декодирование пакета версии 1 (16 байт) и CRC. Проверки UART, времени переключения направления, доступа к шине и поведения устройства выполняются на стенде.

[Описание протокола](../docs/protocol.md) · [План испытаний](../docs/validation-plan.md).
