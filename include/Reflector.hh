/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : Reflect.hh
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Version  : 0.1
*  Date     : Sun 08 Jan 2023 03:03:54 PM CST
================================================================*/

#pragma once

#ifndef REFLECTOR_HH_
#define REFLECTOR_HH_

#include <functional>
#include <iostream>
#include <map>
#include <memory>

#define FUNC std::function<void*(void)>

class Reflector {
  private:
    std::map<std::string, FUNC>       objectMap;
    static std::shared_ptr<Reflector> ptr;

  public:
    void* CreateObject(const std::string& str) {
        for (auto& x : objectMap) {
            if (x.first == str)
                return x.second();
        }
        return nullptr;
    }

    void Register(const std::string& class_name, FUNC&& generator) {
        objectMap[class_name] = generator;
    }

    static std::shared_ptr<Reflector> Instance() {
        if (ptr == nullptr) {
            ptr.reset(new Reflector());
        }

        return ptr;
    }
};

class RegisterAction {
  public:
    RegisterAction(const std::string& class_name, FUNC&& generator) {
        Reflector::Instance()->Register(class_name, std::forward<FUNC>(generator));
    }
};

#define REGISTER_APPLICATION(CLASS_NAME)                              \
    RegisterAction g_register_action_##CLASS_NAME(#CLASS_NAME, []() { \
        return new CLASS_NAME();                                      \
    });

#endif