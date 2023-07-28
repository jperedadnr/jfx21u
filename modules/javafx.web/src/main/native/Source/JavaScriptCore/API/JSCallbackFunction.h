/*
 * Copyright (C) 2006-2022 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef JSCallbackFunction_h
#define JSCallbackFunction_h

#include "InternalFunction.h"
#include "JSObjectRef.h"

namespace JSC {

#define JSCALLBACK_FUNCTION_METHOD(method) \
    WTF_VTBL_FUNCPTR_PTRAUTH_STR("JSCallbackFunction." #method) method

class JSCallbackFunction final : public InternalFunction {
    friend struct APICallbackFunction;
public:
    typedef InternalFunction Base;

    template<typename CellType, SubspaceAccess mode>
    static GCClient::IsoSubspace* subspaceFor(VM& vm)
    {
        return vm.callbackFunctionSpace<mode>();
    }

    static JSCallbackFunction* create(VM&, JSGlobalObject*, JSObjectCallAsFunctionCallback, const String& name);

    DECLARE_INFO;

    // InternalFunction mish-mashes constructor and function behavior -- we should
    // refactor the code so this override isn't necessary
    static Structure* createStructure(VM& vm, JSGlobalObject* globalObject, JSValue proto)
    {
        return Structure::create(vm, globalObject, proto, TypeInfo(InternalFunctionType, StructureFlags), info());
    }

private:
    JSCallbackFunction(VM&, Structure*, JSObjectCallAsFunctionCallback);
    void finishCreation(VM&, const String& name);

    JSObjectCallAsFunctionCallback functionCallback() { return m_callback; }

    JSObjectCallAsFunctionCallback JSCALLBACK_FUNCTION_METHOD(m_callback) { nullptr };
};

#undef JSCALLBACK_FUNCTION_METHOD

} // namespace JSC

#endif // JSCallbackFunction_h
