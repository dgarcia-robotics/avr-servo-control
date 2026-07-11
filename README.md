# Bare-Metal AVR Servo Control

Button-driven servo positioning on an ATmega328P using Timer1 hardware PWM configured entirely through registers — mode 14 Fast PWM with ICR1 as TOP for an exact 50 Hz servo signal.

**Course:** RBT211 Assignment 12.1 · **Tools:** C, Microchip (Atmel) Studio, ATmega328P · **Demo:** [YouTube](https://youtu.be/0gJyDRlxFmc)

## Degree Objective

**Objective 2 — Demonstrate embedded microprocessor system and circuit skills.**

This is the standard industry approach to hobby-servo timing: let the 16-bit timer peripheral generate the pulse train in hardware while the CPU only updates the compare register.

## How It Works

Timer1 is set to Fast PWM mode 14 (`WGM13:11`, ICR1 = 39999, prescaler 8) producing a 20 ms period on OC1A (D9). Two push buttons increment or decrement `OCR1A` in fixed steps between calibrated min/max pulse widths, sweeping the servo across its range; the loop delay sets sweep speed.

## Engineering Highlights

- **Hardware-timed pulses:** pulse width never depends on software timing — the compare unit generates it, so servo position is jitter-free regardless of loop activity.
- **Bounds-checked motion:** pulse limits are enforced before every update so the servo can't be commanded past its mechanical range.
- **Minimal, readable register setup:** every TCCR bit is set deliberately and commented — no framework hiding what the silicon is doing.

## Files

- `servo_control.c` — full bare-metal source

## Links

- Demo video: https://youtu.be/0gJyDRlxFmc
- Portfolio: https://www.garciarobotics.com/
