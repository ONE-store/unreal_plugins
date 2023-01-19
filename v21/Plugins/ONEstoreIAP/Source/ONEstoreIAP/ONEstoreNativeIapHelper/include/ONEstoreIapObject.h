/*
 * Do Not Modify This File.
 * Copyright © 2022, ONEstore. All rights reserved.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

namespace ONESTORE_IAP {

#ifndef PURE
#define PURE    =0;
#endif

class IapObject {
public:
    IapObject(){};
    virtual ~IapObject(){};

    virtual void dump() PURE;
};

}

#ifdef __cplusplus
}
#endif
