/*
 * Copyright (C) 2015-2017 Apple Inc. All rights reserved.
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

#pragma once

#if ENABLE(B3_JIT)

#include "AirArg.h"
#include "AirKind.h"
#include "MacroAssembler.h"
#include <wtf/ScopedLambda.h>

namespace JSC {

class CCallHelpers;
class RegisterSetBuilder;

namespace B3 {

class Value;

namespace Air {

struct GenerationContext;

struct Inst {
    typedef Vector<Arg, 3> ArgList;

    Inst()
        : origin(nullptr)
    {
    }

    Inst(Kind kind, Value* origin)
        : origin(origin)
        , kind(kind)
    {
    }

    template<typename... Arguments>
    Inst(Kind kind, Value* origin, Arg arg, Arguments... arguments)
        : args{ arg, arguments... }
        , origin(origin)
        , kind(kind)
    {
    }

    Inst(Kind kind, Value* origin, const ArgList& arguments)
        : args(arguments)
        , origin(origin)
        , kind(kind)
    {
    }

    Inst(Kind kind, Value* origin, ArgList&& arguments)
        : args(WTFMove(arguments))
        , origin(origin)
        , kind(kind)
    {
    }

    explicit operator bool() const { return origin || kind || args.size(); }

    void append() { }

    template<typename... Arguments>
    void append(Arg arg, Arguments... arguments)
    {
        args.append(arg);
        append(arguments...);
    }

    // Note that these functors all avoid using "const" because we want to use them for things that
    // edit IR. IR is meant to be edited; if you're carrying around a "const Inst&" then you're
    // probably doing it wrong.

    // This only walks those Tmps that are explicitly mentioned, and it doesn't tell you their role
    // or type.
    template<typename Functor>
    void forEachTmpFast(const Functor& functor)
    {
        for (Arg& arg : args)
            arg.forEachTmpFast(functor);
    }

    typedef void EachArgCallback(Arg&, Arg::Role, Bank, Width);

    // Calls the functor with (arg, role, type, width). This function is auto-generated by
    // opcode_generator.rb.
    template<typename Functor>
    void forEachArg(const Functor&);

    // Calls the functor with (tmp, role, type, width).
    template<typename Functor>
    void forEachTmp(const Functor& functor)
    {
        forEachArg(
            [&] (Arg& arg, Arg::Role role, Bank bank, Width width) {
                arg.forEachTmp(role, bank, width, functor);
            });
    }

    // Thing can be either Arg, Tmp, or StackSlot*.
    template<typename Thing, typename Functor>
    void forEach(const Functor&);

    // Reports any additional registers clobbered by this operation. Note that for efficiency,
    // extraClobberedRegs() only works for the Patch opcode.
    RegisterSetBuilder extraClobberedRegs();
    RegisterSetBuilder extraEarlyClobberedRegs();

    // Iterate over all Def's that happen at the end of an instruction. You supply a pair
    // instructions. The instructions must appear next to each other, in that order, in some basic
    // block. You can pass null for the first instruction when analyzing what happens at the top of
    // a basic block. You can pass null for the second instruction when analyzing what happens at the
    // bottom of a basic block.
    template<typename Thing, typename Functor>
    static void forEachDef(Inst* prevInst, Inst* nextInst, const Functor&);

    // Iterate over all Def's that happen at the end of this instruction, including extra clobbered
    // registers. Note that Thing can only be Arg or Tmp when you use this functor.
    template<typename Thing, typename Functor>
    static void forEachDefWithExtraClobberedRegs(Inst* prevInst, Inst* nextInst, const Functor&);

    template<typename Thing, typename Functor>
    static void forEachUse(Inst* prevInst, Inst* nextInst, const Functor&);

    // Some summaries about all arguments. These are useful for needsPadding().
    bool hasEarlyDef();
    bool hasLateUseOrDef();

    // Check if there needs to be a padding Nop between these two instructions.
    static bool needsPadding(Inst* prevInst, Inst* nextInst);

    // Use this to report which registers are live. This should be done just before codegen. Note
    // that for efficiency, reportUsedRegisters() only works for the Patch opcode.
    void reportUsedRegisters(const RegisterSetBuilder&);

    // Is this instruction in one of the valid forms right now? This function is auto-generated by
    // opcode_generator.rb.
    bool isValidForm();

    // Assuming this instruction is in a valid form right now, will it still be in one of the valid
    // forms if we put an Addr referencing the stack (or a StackSlot or CallArg, of course) in the
    // given index? Spilling uses this: it walks the args by index to find Tmps that need spilling;
    // if it finds one, it calls this to see if it can replace the Arg::Tmp with an Arg::Addr. If it
    // finds a non-Tmp Arg, then it calls that Arg's forEachTmp to do a replacement that way.
    //
    // This function is auto-generated by opcode_generator.rb.
    bool admitsStack(unsigned argIndex);
    bool admitsStack(Arg&);

    bool admitsExtendedOffsetAddr(unsigned argIndex);
    bool admitsExtendedOffsetAddr(Arg&);

    // Defined by opcode_generator.rb.
    bool isTerminal();

    // Returns true if this instruction can have any effects other than control flow or arguments.
    bool hasNonArgNonControlEffects();

    // Returns true if this instruction can have any effects other than what is implied by arguments.
    // For example, "Move $42, (%rax)" will return false because the effect of storing to (%rax) is
    // implied by the second argument.
    bool hasNonArgEffects();

    // Tells you if this operation has arg effects.
    bool hasArgEffects();

    // Tells you if this operation has non-control effects.
    bool hasNonControlEffects() { return hasNonArgNonControlEffects() || hasArgEffects(); }

    // Generate some code for this instruction. This is, like, literally our backend. If this is the
    // terminal, it returns the jump that needs to be linked for the "then" case, with the "else"
    // case being fall-through. This function is auto-generated by opcode_generator.rb.
    MacroAssembler::Jump generate(CCallHelpers&, GenerationContext&);

    // If source arguments benefits from being aliased to a destination argument,
    // this return the index of the destination argument.
    // The source are assumed to be at (index - 1) and (index - 2)
    // For example,
    //     Add Tmp1, Tmp2, Tmp3
    // returns 2 if 0 and 1 benefit from aliasing to Tmp3.
    std::optional<unsigned> shouldTryAliasingDef();

    // This computes a hash for comparing this to JSAir's Inst.
    unsigned jsHash() const;

    void dump(PrintStream&) const;

    ArgList args;
    Value* origin; // The B3::Value that this originated from.
    Kind kind;

private:
    template<typename Func>
    void forEachArgSimple(const Func&);
    void forEachArgCustom(ScopedLambda<EachArgCallback>);
};

} } } // namespace JSC::B3::Air

#endif // ENABLE(B3_JIT)
