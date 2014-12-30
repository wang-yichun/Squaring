/*
 * Copyright (C) 2012 Soomla Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __cocos2dx_store__VirtualItemNotFoundException__
#define __cocos2dx_store__VirtualItemNotFoundException__

#include <iostream>
#include <exception>

using namespace std;

class cocos2dx_VirtualItemNotFoundException : public exception {
    
public:
    
    virtual const char* what() const throw() {
        return "The requested virtual item was not found !";
    }
};

#endif
