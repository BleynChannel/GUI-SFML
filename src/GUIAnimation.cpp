#include "GUIAnimation.hpp"

//Конструктор
GUI::Animation::Animation(const std::function<void(const Animation&)>& frameHandle, const std::function<void()>& onFinish)
    : startTime(0.f), currentTime(0.f), started(false), duration(0.f), position(0.f), frameHandle(frameHandle), onFinish(onFinish) {}

//Методы

void GUI::Animation::start(float duration)
{
    started = true;
    position = 0.f;
    this->duration = duration;
    clock.restart();
    startTime = clock.getElapsedTime().asSeconds();
    currentTime = startTime;
}

void GUI::Animation::stop()
{
    started = false;
    position = 0.f;
}