/*MIT License
Copyright (c) 2024 Alan Uthoff*/

#pragma once

#include "fteng/signals.hpp"
//fteng/signals.hpp from https://github.com/TheWisp/signals under the MIT License
#include <chrono>
#include <set>
class STimer
{
public:
    STimer();
    ~STimer();
    fteng::signal<void()> timeout;
    void start(int interval);
    void start(std::chrono::milliseconds interval);
    void start();
    void stop();
    void setInterval(std::chrono::milliseconds interval);
    bool isActive();
    static void updateAll();
    static void regeisterTimer(STimer * timer);
protected:
    void update();
    std::chrono::milliseconds m_startTime;
    std::chrono::milliseconds m_interval;
    bool m_active = false;
};

