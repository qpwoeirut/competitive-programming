import kotlin.math.min
import kotlin.math.sqrt

fun readInt(): Int {
    return readln().toInt()
}

fun readStrings(): List<String> {
    return readln().split(" ")
}

fun readInts(): List<Int> {
    return readStrings().map { it.toInt() }
}


interface Entity {
    val x: Int
    val y: Int

    fun dist(other: Pair<Int, Int>) =
        sqrt(((x - other.first) * (x - other.first) + (y - other.second) * (y - other.second)).toDouble())

    fun dist(other: Entity) = dist(Pair(other.x, other.y))
}


data class CreatureData(val id: Int, val color: Int, val type: Int) {
    constructor(ints: List<Int>) : this(ints[0], ints[1], ints[2]) {
        assert(ints.size == 3)
    }
}

data class CreaturePosition(val id: Int, override val x: Int, override val y: Int, val vx: Int, val vy: Int) : Entity {
    constructor(ints: List<Int>) : this(ints[0], ints[1], ints[2], ints[3], ints[4]) {
        assert(ints.size == 5)
    }
}


data class Drone(val id: Int, override val x: Int, override val y: Int, val emergency: Int, val battery: Int) : Entity {
    constructor(ints: List<Int>) : this(ints[0], ints[1], ints[2], ints[3], ints[4]) {
        assert(ints.size == 5)
    }
}


data class RadarBlip(val droneId: Int, val creatureId: Int, val radar: String)


data class Scan(val droneId: Int, val creatureId: Int) {
    constructor(ints: List<Int>) : this(ints[0], ints[1]) {
        assert(ints.size == 2)
    }
}

const val TURNS = 200
const val SIZE = 10000
const val THRESHOLD = 100
const val EXTRA_STEPS = 8

private fun getTarget(stage: Int, start: Pair<Int, Int>): Pair<Int, Int> {
    return when (stage) {
        0 -> Pair(start.first, SIZE)
        1 -> Pair(SIZE - start.first, SIZE)
        2 -> Pair(SIZE - start.first, 0)
        else -> {
            val x = if (stage % 2 == 0) 0 else SIZE
            val y = SIZE - (((stage - 2) % (EXTRA_STEPS + 1)) * SIZE / EXTRA_STEPS)
            Pair(x, y)
        }
    }
}

fun main() {
    val creatureCount = readInt()
    val creatures = List(creatureCount) { CreatureData(readInts()) }

    val stage = mutableMapOf<Int, Int>()
    val startPos = mutableMapOf<Int, Pair<Int, Int>>()

    for (turn in 0 until TURNS) {
        val myScore = readInt()

        val foeScore = readInt()

        val myScanCount = readInt()
        val myScannedCreatures = List(myScanCount) { readInt() }

        val foeScanCount = readInt()
        val foeScannedCreatures = List(foeScanCount) { readInt() }

        val myDroneCount = readInt()
        val myDrones = List(myDroneCount) {
            Drone(readInts()).also {
                if (it.id !in stage) stage[it.id] = 0
                if (it.id !in startPos) startPos[it.id] = Pair(it.x, it.y)
            }
        }

        val foeDroneCount = readInt()
        val foeDrones = List(foeDroneCount) { Drone(readInts()) }

        val scanCount = readInt()
        val scans = List(scanCount) { Scan(readInts()) }

        val visibleCreatureCount = readInt()
        val visibleCreatures = List(visibleCreatureCount) { CreaturePosition(readInts()) }

        val radarBlipCount = readInt()
        val radarBlips = List(radarBlipCount) {
            val strs = readStrings()
            RadarBlip(strs[0].toInt(), strs[1].toInt(), strs[2])
        }

        for (drone in myDrones) {
            var target = getTarget(stage[drone.id]!!, startPos[drone.id]!!)

            while (drone.dist(target) <= THRESHOLD) {
                stage[drone.id] = stage[drone.id]!! + 1
                target = getTarget(stage[drone.id]!!, startPos[drone.id]!!)
            }

            val phase = min(5, 2 + (turn / 10))
            val light: Int = if (turn % phase == 0) 1 else 0
            println("MOVE ${target.first} ${target.second} $light")
        }
    }
}
