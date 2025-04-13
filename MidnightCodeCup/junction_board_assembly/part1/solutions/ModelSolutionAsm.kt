// Greetings from JetBrains!

@file:OptIn(ExperimentalUnsignedTypes::class)

import java.lang.RuntimeException
import java.util.Scanner

// Made by Alice Sayutina

enum class Register {
    RA, RB, RC, RD, RE, RF, RG, RR, RINS, RST, RFLAG;

    companion object {
        val Count = entries.size

        fun fromInteger(i: Int) = when (i) {
            in entries.indices -> entries[i]
            entries.size -> null
            else -> throw RuntimeException("Illegal register")
        }
    }
}

// one of {RA, RA + 5, 5}-style expressions
data class Expression(val register: Register?, val immediate: Byte = 0)

sealed class Operation

data object NoOp : Operation()

data class LoadOp(val destination: Register, val address: Expression) : Operation()

data class StoreOp(val source: Register, val address: Expression) : Operation()

enum class JumpCondition {
    ALWAYS, ZERO, NONZERO, CARRY, NOTCARRY
}

data class JumpOp(val condition: JumpCondition, val address: Expression) : Operation()

data class PushOp(val expression: Expression) : Operation()

data class PopOp(val register: Register) : Operation()

data class HaltOp(val expression: Expression) : Operation()

data class SetOp(val register: Register, val expression: Expression) : Operation()

enum class OperationType {
    Add, Sub, Mult
}

data class BinaryOp(val op: OperationType, val dst: Register, val a: Register, val b: Register) : Operation()

data class DebugOp(val tag: UByte) : Operation()

data class Exit(val code: UInt)

object CoderDecoder {
    fun decode(data: UInt): Operation {
        val opcode = ByteUtils.getByte(data, 0u)
        val byte2 = ByteUtils.getByte(data, 1u)
        val byte3 = ByteUtils.getByte(data, 2u)
        val byte4 = ByteUtils.getByte(data, 3u)

        val register1 by lazy { Register.fromInteger(byte2.toInt())!! }
        val register2 by lazy { Register.fromInteger(byte3.toInt()) }
        val expr by lazy { Expression(register2, byte4.toByte()) }
        val register3 by lazy { Register.fromInteger(byte4.toInt()) }

        return when (opcode.toInt()) {
            0 -> NoOp
            1 -> LoadOp(register1, expr)
            2 -> StoreOp(register1, expr)
            3 -> PushOp(expr)
            4 -> PopOp(register1)
            5 -> HaltOp(expr)
            6 -> SetOp(register1, expr)
            7 -> DebugOp(byte2)
            in 10 until 10 + JumpCondition.entries.size -> JumpOp(JumpCondition.entries[opcode.toInt() - 10], expr)
            in 20 until 20 + OperationType.entries.size -> BinaryOp(OperationType.entries[opcode.toInt() - 20], register1, register2!!, register3!!)
            else -> throw RuntimeException("Illegal instruction $opcode")
        }
    }

    fun encode(op: Operation): UInt {
        fun fromBytes(a: UByte, b: UByte, c: UByte, d: UByte): UInt {
            return ByteUtils.readByte(a, 0u) or
                    ByteUtils.readByte(b, 1u) or
                    ByteUtils.readByte(c, 2u) or
                    ByteUtils.readByte(d, 3u)
        }
        fun convertRegister(r: Register?): UByte {
            return r?.ordinal?.toUByte() ?: Register.Count.toUByte()
        }
        fun fromRegisterAndExpr(opcode: UByte, r: Register?, expr: Expression): UInt {
            return fromBytes(opcode, convertRegister(r), convertRegister(expr.register), expr.immediate.toUByte())
        }
        fun fromRegister(opcode: UByte, r: Register?): UInt {
            return fromBytes(opcode, convertRegister(r), 0u, 0u)
        }
        fun fromThreeRegisters(opcode: UByte, r1: Register, r2: Register, r3: Register): UInt {
            return fromBytes(opcode, convertRegister(r1), convertRegister(r2), convertRegister(r3))
        }

        return when (op) {
            is NoOp -> fromRegister(0u, null)
            is LoadOp -> fromRegisterAndExpr(1u, op.destination, op.address)
            is StoreOp -> fromRegisterAndExpr(2u, op.source, op.address)
            is PushOp -> fromRegisterAndExpr(3u, null, op.expression)
            is PopOp -> fromRegister(4u, op.register)
            is HaltOp -> fromRegisterAndExpr(5u, null, op.expression)
            is SetOp -> fromRegisterAndExpr(6u, op.register, op.expression)
            is DebugOp -> fromBytes(7u, op.tag, 0u, 0u)
            is JumpOp -> fromRegisterAndExpr((10 + op.condition.ordinal).toUByte(), null, op.address)
            is BinaryOp -> fromThreeRegisters((20 + op.op.ordinal).toUByte(), op.dst, op.a, op.b)
        }
    }
}

object ByteUtils {
    fun getByte(num: UInt, byteIndex: UInt): UByte {
        return ((num shr (8 * byteIndex.toInt())) and 255u).toUByte()
    }

    fun readByte(byte: UByte, byteIndex: UInt): UInt {
        return (byte.toUInt() shl (8 * byteIndex.toInt()))
    }
}

@JvmInline
value class Cassette(val code: UByteArray)

class Memory(code: Cassette, input: Cassette) {
    private val data = UByteArray(SIZE)

    private fun bind(addr: Int, cassette: Cassette) {
        for (i in 0 until cassette.code.size) {
            data[addr + i] = cassette.code[i]
        }
    }

    init {
        bind(INPUT_BEGIN, input)
        bind(CODE_BEGIN, code)
    }

    fun load(addr: UInt): UInt {
        require(addr <= SIZE.toUInt() - 4u) { "Segmentation fault: read $addr" }
        var res = 0u
        for (i in 0..3) {
            res = res or ByteUtils.readByte(data[addr.toInt() + i], i.toUInt())
        }
        return res
    }

    fun store(addr: UInt, value: UInt) {
        require(addr <= SIZE.toUInt() - 4u) { "Segmentation fault: store $addr <- $value" }
        for (i in 0..3) {
            data[addr.toInt() + i] = ByteUtils.getByte(value, i.toUInt())
        }
    }

    companion object {
        const val SIZE = 4 * (1 shl 20)
        const val INPUT_BEGIN = 0
        const val USER_MEMORY = 1 * (1 shl 20)
        const val CODE_BEGIN = 2 * (1 shl 20)
        const val STACK_BEGIN = SIZE
    }
}

class Computer(codeDisk: Cassette, input: Cassette) {
    object Flags {
        val FLAG_ZERO = 1u
        val FLAG_OVERFLOW = 2u
    }

    private val memory = Memory(codeDisk, input)
    private val registers = UIntArray(Register.Count)

    private fun store(register: Register, value: UInt) {
        System.err.println("debug: stored $register <- $value")
        registers[register.ordinal] = value
    }

    init {
        System.err.println("Greetings from JetBrains! Running chip simulation.")
        store(Register.RINS, Memory.CODE_BEGIN.toUInt())
        store(Register.RST, Memory.STACK_BEGIN.toUInt())
    }

    fun value(register: Register): UInt {
        return registers[register.ordinal]
    }

    var instructionPointer: UInt
        get() = value(Register.RINS)
        private set(x) {
            store(Register.RINS, x)
        }

    var stackPointer: UInt
        get() = value(Register.RST)
        private set(x) {
            store(Register.RST, x)
        }

    fun value(expr: Expression): UInt {
        val immediate = expr.immediate.toInt().toUInt()
        val registerVal = expr.register ?.let { value(it) } ?: 0u
        val res = immediate + registerVal

        val carryFlag = if (immediate.toInt() >= 0) {
            if (res < immediate) Flags.FLAG_OVERFLOW else 0u
        } else {
            if (res > registerVal) Flags.FLAG_OVERFLOW else 0u
        }

        val flags = carryFlag or (if (res == 0u) Flags.FLAG_ZERO else 0u)
        store(Register.RFLAG, flags)

        return res
    }

    private fun handleBinaryOp(op: BinaryOp) {
        val isCarry: Boolean
        val result: UInt
        val a = value(op.a)
        val b = value(op.b)
        when (op.op) {
            OperationType.Add -> {
                result = a + b
                isCarry = (a + b) < a
            }

            OperationType.Sub -> {
                result = a - b
                isCarry = b > a
            }

            OperationType.Mult -> {
                result = a * b
                isCarry = false
            }
        }

        val newFlags = (if (isCarry) Flags.FLAG_OVERFLOW else 0u) or (if (result == 0u) Flags.FLAG_ZERO else 0u)
        store(op.dst, result)
        store(Register.RFLAG, newFlags)
    }

    private fun handleJump(op: JumpOp) {
        val flags = value(Register.RFLAG)
        val shouldJump: Boolean = when (op.condition) {
            JumpCondition.ALWAYS -> true
            JumpCondition.ZERO -> (flags and Flags.FLAG_ZERO) != 0u
            JumpCondition.NONZERO -> (flags and Flags.FLAG_ZERO) == 0u
            JumpCondition.CARRY -> (flags and Flags.FLAG_OVERFLOW) != 0u
            JumpCondition.NOTCARRY -> (flags and Flags.FLAG_OVERFLOW) == 0u
        }

        if (shouldJump) {
            registers[Register.RINS.ordinal] = value(op.address)
        }
    }

    private fun printDebug(op: DebugOp) {
        System.err.println("debugop[tag=${op.tag}] " + Register.entries.joinToString(" ") { r ->
            "$r=${value(r)}"
        })
    }

    private fun execOp(op: Operation): Exit? {
        when (op) {
            is HaltOp -> {
                return Exit(value(op.expression))
            }

            is JumpOp -> handleJump(op)
            is LoadOp -> store(op.destination, memory.load(value(op.address)))
            is StoreOp -> memory.store(value(op.address), value(op.source))
            is NoOp -> {}
            is PopOp -> {
                val res = memory.load(stackPointer)
                stackPointer += 4u
                store(op.register, res)
            }

            is PushOp -> {
                stackPointer -= 4u
                memory.store(stackPointer, value(op.expression))
            }

            is BinaryOp -> handleBinaryOp(op)
            is SetOp -> {
                store(op.register, value(op.expression))
            }

            is DebugOp -> {
                printDebug(op)
            }
        }

        return null
    }

    fun step(): Exit? {
        val opcode = memory.load(instructionPointer)
        val op = CoderDecoder.decode(opcode)
        System.err.println("executing $op")
        instructionPointer += 4u
        return execOp(op)
    }

    fun exec(limit: Int): Exit? {
        repeat(limit) {
            step()?.let { return it }
        }
        return null
    }

    fun execTillExit(): Exit {
        while (true) {
            step()?.let {
                return it
            }
        }
    }
}

class CodeBuilder(val segmentStart: UInt) {
    protected val code = mutableListOf<UByte>()
    protected val labels = mutableMapOf<String, UInt>()
    protected var rawPass = true

    fun label(label: String) {
        labels[label] = address()
    }

    fun getLabel(l: String): UInt {
        if (rawPass) {
            return address()
        }
        return labels.get(l)!!
    }

    fun address(): UInt {
        return segmentStart + code.size.toUInt()
    }

    fun byte(b: UByte) {
        code.add(b)
    }

    fun int(i: UInt) {
        for (it in 0u..3u) {
            byte(ByteUtils.getByte(i, it))
        }
    }

    fun Int.toByteSafe(): Byte {
        require(this in Byte.MIN_VALUE.. Byte.MAX_VALUE) { "Can't convert to byte: value too large: $this" }
        return this.toByte()
    }

    fun op(op: Operation) {
        int(CoderDecoder.encode(op))
    }

    fun jumpIf(condition: JumpCondition, goto: String) {
        val pnow = address().toInt() + 4 // PINS going to shift after decoding this op
        val pwant = getLabel(goto).toInt()

        val delta = (pwant - pnow)
        op(JumpOp(condition, Expression(Register.RINS, delta.toByteSafe())))
    }

    fun jump(goto: String) {
        jumpIf(JumpCondition.ALWAYS, goto)
    }

    fun setConst(register: Register, constant: UInt) {
        op(LoadOp(register, Expression(Register.RINS, 4)))
        op(JumpOp(JumpCondition.ALWAYS, Expression(Register.RINS, 4)))
        int(constant)
    }

    fun call(goto: String) {
        op(PushOp(Expression(Register.RINS, 16))) // jump to X
        op(PushOp(Expression(Register.RG)))
        op(LoadOp(Register.RG, Expression(Register.RINS, 4))) // load Y
        op(JumpOp(JumpCondition.ALWAYS, Expression(Register.RG)))
        int(getLabel(goto)) // Y
        op(NoOp)        // X
    }

    fun callPreservingRegisters(goto: String, vararg register: Register) {
        register.forEach { r ->
            op(PushOp(Expression(r)))
        }
        call(goto)
        register.reversed().forEach { r ->
            op(PopOp(r))
        }
    }

    fun ret() {
        op(PopOp(Register.RG))
        op(PopOp(Register.RINS))
    }

    fun toCassette(): Cassette {
        return Cassette(code.toUByteArray())
    }

    fun setCleanPass() {
        rawPass = false
        code.clear()
    }

    companion object {
        fun buildWithParams(segmentStart: UInt, script: CodeBuilder.() -> Unit, printSym: Boolean = false): Cassette {
            val builder = CodeBuilder(segmentStart)
            script(builder)
            builder.setCleanPass()
            script(builder)
            if (printSym) {
                builder.labels
                    .entries
                    .sortedBy { entry -> entry.value }
                    .forEach { entry -> System.err.println("sym: ${entry.key} to ${entry.value}") }
            }
            return builder.toCassette()
        }
    }
}

fun buildCode(printSym: Boolean = false, script: CodeBuilder.() -> Unit): Cassette =
    CodeBuilder.buildWithParams(Memory.CODE_BEGIN.toUInt(), script, printSym = printSym)

fun buildData(script: CodeBuilder.() -> Unit): Cassette =
    CodeBuilder.buildWithParams(Memory.INPUT_BEGIN.toUInt(), script)

fun program(): Cassette = buildCode {
    label("main")
    call("run")
    op(HaltOp(Expression(Register.RR)))

    label("loadinput")
    op(LoadOp(Register.RA, Expression(null, (Memory.INPUT_BEGIN + 0).toByte())))
    op(LoadOp(Register.RB, Expression(null, (Memory.INPUT_BEGIN + 4).toByte())))
    op(LoadOp(Register.RC, Expression(null, (Memory.INPUT_BEGIN + 8).toByte())))
    ret()

    label("getn")
    call("loadinput")
    op(BinaryOp(OperationType.Add, Register.RR, Register.RA, Register.RB))
    op(BinaryOp(OperationType.Add, Register.RR, Register.RR, Register.RC))
    ret()

    label("run")
    call("getn")
    op(SetOp(Register.RA, Expression(Register.RR)))
    op(SetOp(Register.RB, Expression(null, 0)))
    op(SetOp(Register.RC, Expression(null, 0)))
    call("brute")
    op(SetOp(Register.RR, Expression(Register.RC)))
    ret()

    label("brute")
    op(BinaryOp( OperationType.Sub, Register.RR,Register.RA, Register.RB))
    jumpIf(JumpCondition.NONZERO, "brute@continue")
    op(DebugOp(1u))
    callPreservingRegisters("check", Register.RA, Register.RB, Register.RC)
    op(BinaryOp(OperationType.Add, Register.RC, Register.RC, Register.RR))
    op(DebugOp(2u))
    ret()
    label("brute@continue")
    op(SetOp(Register.RB, Expression(Register.RB, +1)))

    op(SetOp(Register.RE, Expression(null, 'A'.code.toByte())))
    label("inner")
    callPreservingRegisters("push", Register.RA, Register.RB)
    callPreservingRegisters("brute", Register.RE)
    callPreservingRegisters("pop", Register.RA, Register.RB)
    op(SetOp(Register.RE, Expression(Register.RE, 1)))
    op(SetOp(Register.RG, Expression(Register.RE, (-'D'.code).toByte())))
    jumpIf(JumpCondition.NONZERO, "inner")

    op(SetOp(Register.RB, Expression(Register.RB, -1)))
    ret()

    label("#begin")
    int(Memory.USER_MEMORY.toUInt())
    label("#head")
    int(Memory.USER_MEMORY.toUInt())

    label("push")
    op(SetOp(Register.RA, Expression(Register.RINS,
        (getLabel("#head").toInt() - address().toInt() - 4).toByte())))
    op(LoadOp(Register.RB, Expression(Register.RA)))
    op(StoreOp(Register.RE, Expression(Register.RB)))
    op(SetOp(Register.RB, Expression(Register.RB, 4)))
    op(StoreOp(Register.RB, Expression(Register.RA)))
    ret()

    label("pop")
    op(SetOp(Register.RA, Expression(Register.RINS,
        (getLabel("#head").toInt() - address().toInt() - 4).toByte())))
    op(LoadOp(Register.RB, Expression(Register.RA)))
    op(SetOp(Register.RB, Expression(Register.RB, -4)))
    op(StoreOp(Register.RB, Expression(Register.RA)))
    ret()

    label("check")
    call("loadinput")
    op(SetOp(Register.RR, Expression(null, 1)))
    op(DebugOp(tag=30u))
    op(SetOp(Register.RD, Expression(Register.RINS,
        (getLabel("#begin").toInt() - address().toInt() - 4).toByte())))
    op(SetOp(Register.RE, Expression(Register.RINS,
        (getLabel("#head").toInt() - address().toInt() - 4).toByte())))
    op(LoadOp(Register.RD, Expression(Register.RD)))
    op(LoadOp(Register.RE, Expression(Register.RE)))

    op(SetOp(Register.RF, Expression(null, 0)))
    label("check@loop")
    op(SetOp(Register.RG, Expression(Register.RF)))
    op(LoadOp(Register.RF, Expression(Register.RD)))

    op(DebugOp(tag=31u))
    op(BinaryOp(OperationType.Sub, Register.RG, Register.RF, Register.RG))
    op(JumpOp(JumpCondition.NONZERO, Expression(Register.RINS, 4)))
    op(SetOp(Register.RR, Expression(null, 0)))
    op(DebugOp(tag=32u))

    op(PushOp(Expression(Register.RE)))
    op(SetOp(Register.RE, Expression(null, 4)))
    op(SetOp(Register.RG, Expression(Register.RF, (-'='.code).toByte())))

    op(BinaryOp(OperationType.Mult, Register.RG, Register.RE, Register.RG))
    op(BinaryOp(OperationType.Add, Register.RG, Register.RINS, Register.RG))
    op(LoadOp(Register.RE, Expression(Register.RG)))
    op(StoreOp(Register.RE, Expression(Register.RINS)))
    op(DebugOp(tag=39u))

    op(SetOp(Register.RINS, Expression(Register.RINS, 16)))
    op(SetOp(Register.RA, Expression(Register.RA, -1)))
    op(SetOp(Register.RB, Expression(Register.RB, -1)))
    op(SetOp(Register.RC, Expression(Register.RC, -1)))
    op(SetOp(Register.RD, Expression(Register.RD, -1)))

    op(PopOp(Register.RE))
    op(DebugOp(tag=33u))
    op(SetOp(Register.RD, Expression(Register.RD, 4)))
    op(BinaryOp(OperationType.Sub,Register.RG, Register.RD, Register.RE))
    jumpIf(JumpCondition.NONZERO, "check@loop") // go to check@false

    op(SetOp(Register.RG, Expression(Register.RA)))
    op(JumpOp(JumpCondition.ZERO, Expression(Register.RINS, 4)))
    op(SetOp(Register.RR, Expression(null, 0)))

    op(SetOp(Register.RG, Expression(Register.RB)))
    op(JumpOp(JumpCondition.ZERO, Expression(Register.RINS, 4)))
    op(SetOp(Register.RR, Expression(null, 0)))

    op(SetOp(Register.RG, Expression(Register.RC)))
    op(JumpOp(JumpCondition.ZERO, Expression(Register.RINS, 4)))
    op(SetOp(Register.RR, Expression(null, 0)))

    op(DebugOp(tag=35u))

    ret()
    label("check@false")
    op(SetOp(Register.RR, Expression(null, -1)))
    ret()
}

fun testProgram(): Cassette = buildCode {
    op(LoadOp(Register.RA, Expression(null, (Memory.INPUT_BEGIN + 0).toByte())))
    call("sumall")
    op(HaltOp(Expression(Register.RR)))

    label("squareOf")
    op(BinaryOp(OperationType.Mult, Register.RR, Register.RC, Register.RC))
    ret()

    label("sumall")
    op(SetOp(Register.RC, Expression(Register.RA)))
    op(SetOp(Register.RF, Expression(null)))

    label("sumall@loop")
    call("squareOf")
    op(BinaryOp(OperationType.Add, Register.RF, Register.RF, Register.RR))
    op(SetOp(Register.RC, Expression(Register.RC, -1)))
    jumpIf(JumpCondition.NONZERO, "sumall@loop")

    op(SetOp(Register.RR, Expression(Register.RF)))
    ret()
}

fun input(a: UInt, b: UInt, c: UInt): Cassette = buildData {
    int(a)
    int(b)
    int(c)
}

fun testInput(n: UInt): Cassette = buildData {
    int(n)
}

fun main() {
    val p = program()
    val reader = Scanner(System.`in`.buffered());
    val a = reader.nextInt()
    val b = reader.nextInt()
    val c = reader.nextInt()
    val inputData = input(a.toUInt(), b.toUInt(), c.toUInt())
    val computer = Computer(p, inputData)
    val exit = computer.execTillExit()
    println(exit.code)
}