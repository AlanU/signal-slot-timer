/*MIT License
Copyright (c) 2024 Alan Uthoff*/
#pragma once
#include <iostream>
#include "fteng/signals.hpp"
#include "STimer.h"
//fteng/signals.hpp from https://github.com/TheWisp/signals under the MIT License

class TimerUser{
public:
    explicit TimerUser(std::chrono::milliseconds  interval){
        m_connectTimerSlot =  m_timer.timeout.connect<&TimerUser::onTimerExpired>(this);
        updateTimeStamp();
        m_timer.start(interval);
    }
    ~TimerUser()
    {
        m_timer.stop();
    }

    void onTimerExpired(){
        const auto currentTimeMil = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        std::cout<<"Timer Expired delta:" <<currentTimeMil.count()-m_lastUpdate.count()<<"ms\n";
        updateTimeStamp();
    }

private:
    void updateTimeStamp()
    {
        m_lastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    }
    STimer m_timer;
    fteng::connection m_connectTimerSlot; //User to auto disconnect on destruction of TimerUser
    std::chrono::milliseconds m_lastUpdate;
};