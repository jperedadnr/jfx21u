/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSTestOverloadedConstructors.h"

#include "ExceptionCode.h"
#include "JSBlob.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructor.h"
#include <runtime/Error.h>
#include <runtime/FunctionPrototype.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

// Attributes

JSC::EncodedJSValue jsTestOverloadedConstructorsConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::PropertyName);
void setJSTestOverloadedConstructorsConstructor(JSC::ExecState*, JSC::EncodedJSValue, JSC::EncodedJSValue);

class JSTestOverloadedConstructorsPrototype : public JSC::JSNonFinalObject {
public:
    typedef JSC::JSNonFinalObject Base;
    static JSTestOverloadedConstructorsPrototype* create(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestOverloadedConstructorsPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestOverloadedConstructorsPrototype>(vm.heap)) JSTestOverloadedConstructorsPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestOverloadedConstructorsPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};

typedef JSDOMConstructor<JSTestOverloadedConstructors> JSTestOverloadedConstructorsConstructor;

static inline EncodedJSValue constructJSTestOverloadedConstructors1(ExecState* state)
{
    auto* castedThis = jsCast<JSTestOverloadedConstructorsConstructor*>(state->callee());
    if (UNLIKELY(state->argumentCount() < 1))
        return throwVMError(state, createNotEnoughArgumentsError(state));
    ArrayBuffer* arrayBuffer = toArrayBuffer(state->argument(0));
    if (UNLIKELY(state->hadException()))
        return JSValue::encode(jsUndefined());
    RefPtr<TestOverloadedConstructors> object = TestOverloadedConstructors::create(arrayBuffer);
    return JSValue::encode(asObject(toJS(state, castedThis->globalObject(), object.get())));
}

static inline EncodedJSValue constructJSTestOverloadedConstructors2(ExecState* state)
{
    auto* castedThis = jsCast<JSTestOverloadedConstructorsConstructor*>(state->callee());
    if (UNLIKELY(state->argumentCount() < 1))
        return throwVMError(state, createNotEnoughArgumentsError(state));
    RefPtr<ArrayBufferView> arrayBufferView = toArrayBufferView(state->argument(0));
    if (UNLIKELY(state->hadException()))
        return JSValue::encode(jsUndefined());
    RefPtr<TestOverloadedConstructors> object = TestOverloadedConstructors::create(arrayBufferView);
    return JSValue::encode(asObject(toJS(state, castedThis->globalObject(), object.get())));
}

static inline EncodedJSValue constructJSTestOverloadedConstructors3(ExecState* state)
{
    auto* castedThis = jsCast<JSTestOverloadedConstructorsConstructor*>(state->callee());
    if (UNLIKELY(state->argumentCount() < 1))
        return throwVMError(state, createNotEnoughArgumentsError(state));
    Blob* blob = JSBlob::toWrapped(state->argument(0));
    if (UNLIKELY(state->hadException()))
        return JSValue::encode(jsUndefined());
    RefPtr<TestOverloadedConstructors> object = TestOverloadedConstructors::create(blob);
    return JSValue::encode(asObject(toJS(state, castedThis->globalObject(), object.get())));
}

static inline EncodedJSValue constructJSTestOverloadedConstructors4(ExecState* state)
{
    auto* castedThis = jsCast<JSTestOverloadedConstructorsConstructor*>(state->callee());
    if (UNLIKELY(state->argumentCount() < 1))
        return throwVMError(state, createNotEnoughArgumentsError(state));
    String string = state->argument(0).toString(state)->value(state);
    if (UNLIKELY(state->hadException()))
        return JSValue::encode(jsUndefined());
    RefPtr<TestOverloadedConstructors> object = TestOverloadedConstructors::create(string);
    return JSValue::encode(asObject(toJS(state, castedThis->globalObject(), object.get())));
}

static inline EncodedJSValue constructJSTestOverloadedConstructors5(ExecState* state)
{
    auto* castedThis = jsCast<JSTestOverloadedConstructorsConstructor*>(state->callee());
    Vector<int> longArgs = toNativeArguments<int>(state, 0);
    if (UNLIKELY(state->hadException()))
        return JSValue::encode(jsUndefined());
    RefPtr<TestOverloadedConstructors> object = TestOverloadedConstructors::create(longArgs);
    return JSValue::encode(asObject(toJS(state, castedThis->globalObject(), object.get())));
}

template<> EncodedJSValue JSC_HOST_CALL JSTestOverloadedConstructorsConstructor::construct(ExecState* state)
{
    size_t argsCount = std::min<size_t>(1, state->argumentCount());
    JSValue arg0(state->argument(0));
    if ((argsCount == 1 && ((arg0.isObject() && asObject(arg0)->inherits(JSArrayBuffer::info())))))
        return constructJSTestOverloadedConstructors1(state);
    if ((argsCount == 1 && ((arg0.isObject() && asObject(arg0)->inherits(JSArrayBufferView::info())))))
        return constructJSTestOverloadedConstructors2(state);
    if ((argsCount == 1 && ((arg0.isObject() && asObject(arg0)->inherits(JSBlob::info())))))
        return constructJSTestOverloadedConstructors3(state);
    if (argsCount == 1)
        return constructJSTestOverloadedConstructors4(state);
    if ()
        return constructJSTestOverloadedConstructors5(state);
    if (argsCount < 1)
        return throwVMError(state, createNotEnoughArgumentsError(state));
    return throwVMTypeError(state);
}

template<> JSValue JSTestOverloadedConstructorsConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestOverloadedConstructorsConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->prototype, JSTestOverloadedConstructors::getPrototype(vm, &globalObject), DontDelete | ReadOnly | DontEnum);
    putDirect(vm, vm.propertyNames->name, jsNontrivialString(&vm, String(ASCIILiteral("TestOverloadedConstructors"))), ReadOnly | DontEnum);
    putDirect(vm, vm.propertyNames->length, jsNumber(0), ReadOnly | DontEnum);
}

template<> const ClassInfo JSTestOverloadedConstructorsConstructor::s_info = { "TestOverloadedConstructors", &Base::s_info, 0, CREATE_METHOD_TABLE(JSTestOverloadedConstructorsConstructor) };

/* Hash table for prototype */

static const HashTableValue JSTestOverloadedConstructorsPrototypeTableValues[] =
{
    { "constructor", DontEnum, NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestOverloadedConstructorsConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestOverloadedConstructorsConstructor) } },
};

const ClassInfo JSTestOverloadedConstructorsPrototype::s_info = { "TestOverloadedConstructorsPrototype", &Base::s_info, 0, CREATE_METHOD_TABLE(JSTestOverloadedConstructorsPrototype) };

void JSTestOverloadedConstructorsPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestOverloadedConstructorsPrototypeTableValues, *this);
}

const ClassInfo JSTestOverloadedConstructors::s_info = { "TestOverloadedConstructors", &Base::s_info, 0, CREATE_METHOD_TABLE(JSTestOverloadedConstructors) };

JSTestOverloadedConstructors::JSTestOverloadedConstructors(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestOverloadedConstructors>&& impl)
    : JSDOMWrapper<TestOverloadedConstructors>(structure, globalObject, WTFMove(impl))
{
}

JSObject* JSTestOverloadedConstructors::createPrototype(VM& vm, JSGlobalObject* globalObject)
{
    return JSTestOverloadedConstructorsPrototype::create(vm, globalObject, JSTestOverloadedConstructorsPrototype::createStructure(vm, globalObject, globalObject->objectPrototype()));
}

JSObject* JSTestOverloadedConstructors::getPrototype(VM& vm, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSTestOverloadedConstructors>(vm, globalObject);
}

void JSTestOverloadedConstructors::destroy(JSC::JSCell* cell)
{
    JSTestOverloadedConstructors* thisObject = static_cast<JSTestOverloadedConstructors*>(cell);
    thisObject->JSTestOverloadedConstructors::~JSTestOverloadedConstructors();
}

EncodedJSValue jsTestOverloadedConstructorsConstructor(ExecState* state, EncodedJSValue thisValue, PropertyName)
{
    JSTestOverloadedConstructorsPrototype* domObject = jsDynamicCast<JSTestOverloadedConstructorsPrototype*>(JSValue::decode(thisValue));
    if (!domObject)
        return throwVMTypeError(state);
    return JSValue::encode(JSTestOverloadedConstructors::getConstructor(state->vm(), domObject->globalObject()));
}

void setJSTestOverloadedConstructorsConstructor(ExecState* state, EncodedJSValue thisValue, EncodedJSValue encodedValue)
{
    JSValue value = JSValue::decode(encodedValue);
    JSTestOverloadedConstructorsPrototype* domObject = jsDynamicCast<JSTestOverloadedConstructorsPrototype*>(JSValue::decode(thisValue));
    if (UNLIKELY(!domObject)) {
        throwVMTypeError(state);
        return;
    }
    // Shadowing a built-in constructor
    domObject->putDirect(state->vm(), state->propertyNames().constructor, value);
}

JSValue JSTestOverloadedConstructors::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestOverloadedConstructorsConstructor>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

bool JSTestOverloadedConstructorsOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, SlotVisitor& visitor)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    return false;
}

void JSTestOverloadedConstructorsOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestOverloadedConstructors = jsCast<JSTestOverloadedConstructors*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestOverloadedConstructors->wrapped(), jsTestOverloadedConstructors);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestOverloadedConstructors@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore26TestOverloadedConstructorsE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::ExecState*, JSDOMGlobalObject* globalObject, TestOverloadedConstructors* impl)
{
    if (!impl)
        return jsNull();
    return createNewWrapper<JSTestOverloadedConstructors>(globalObject, impl);
}

JSC::JSValue toJS(JSC::ExecState*, JSDOMGlobalObject* globalObject, TestOverloadedConstructors* impl)
{
    if (!impl)
        return jsNull();
    if (JSValue result = getExistingWrapper<JSTestOverloadedConstructors>(globalObject, impl))
        return result;

#if ENABLE(BINDING_INTEGRITY)
    void* actualVTablePointer = *(reinterpret_cast<void**>(impl));
#if PLATFORM(WIN)
    void* expectedVTablePointer = reinterpret_cast<void*>(__identifier("??_7TestOverloadedConstructors@WebCore@@6B@"));
#else
    void* expectedVTablePointer = &_ZTVN7WebCore26TestOverloadedConstructorsE[2];
#if COMPILER(CLANG)
    // If this fails TestOverloadedConstructors does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    COMPILE_ASSERT(__is_polymorphic(TestOverloadedConstructors), TestOverloadedConstructors_is_not_polymorphic);
#endif
#endif
    // If you hit this assertion you either have a use after free bug, or
    // TestOverloadedConstructors has subclasses. If TestOverloadedConstructors has subclasses that get passed
    // to toJS() we currently require TestOverloadedConstructors you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createNewWrapper<JSTestOverloadedConstructors>(globalObject, impl);
}

TestOverloadedConstructors* JSTestOverloadedConstructors::toWrapped(JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestOverloadedConstructors*>(value))
        return &wrapper->wrapped();
    return nullptr;
}

}
