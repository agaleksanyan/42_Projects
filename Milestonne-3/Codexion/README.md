*This project has been created as part of the 42 curriculum by agaleksa.*

# Codexion

## Description

Codexion is a POSIX threads concurrency simulation. Several coders share a
circular table of USB dongles. A coder needs two neighboring dongles to compile,
then releases them, debugs, refactors, and tries again.

The simulation stops when one coder burns out or when every coder has completed
the required number of compiles.

## Instructions

Build the project:

```sh
make
```

Run it:

```sh
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

Example:

```sh
./codexion 4 800 200 200 100 3 10 fifo
./codexion 4 800 200 200 100 3 10 edf
```

The scheduler must be either `fifo` or `edf`.

## Blocking cases handled

- Deadlock prevention: coders do not lock one dongle and then wait while holding
  only half of the required resources. Requests are registered in both dongle
  queues and the arbiter grants both dongles atomically.
- Starvation control: each dongle uses a heap-based priority queue. FIFO serves
  the earliest request first. EDF serves the earliest burnout deadline first,
  with deterministic tie-breaking.
- Cooldown handling: after release, each dongle stores its release timestamp and
  cannot be granted again before `dongle_cooldown` milliseconds have passed.
- Single coder case: one coder has only one dongle available and therefore burns
  out through the monitor instead of duplicating a dongle.
- Precise burnout detection: a monitor thread checks coder deadlines every
  millisecond and stops the simulation when a deadline is missed.
- Log serialization: output is protected by a mutex so log lines cannot
  interleave.

## Thread synchronization mechanisms

The project uses `pthread_mutex_t` and `pthread_cond_t`.

- `arbiter_mutex` protects shared simulation state: dongle availability,
  cooldown timestamps, request heaps, compile counters, burnout timestamps, and
  the stop flag.
- `arbiter_cond` wakes waiting coder threads when a dongle is released or the
  simulation stops.
- `log_mutex` serializes writes to standard output.

A coder waiting for dongles inserts one request into each neighboring dongle
heap. It may compile only when it is the top request for both dongles and both
dongles are available after cooldown. This prevents races where two coders could
take the same dongle.

The monitor reads `last_compile_start` while holding `arbiter_mutex`, so it sees
consistent deadlines. A coder updates `last_compile_start` in the same critical
section where the two dongles are granted.

## Resources

- `man pthread_create`
- `man pthread_mutex_lock`
- `man pthread_cond_wait`
- `man gettimeofday`
- POSIX Threads Programming documentation
- 42 peer review and subject requirements

AI was used to review the subject, identify missing concurrency requirements,
draft implementation structure, and help test edge cases. The final code should
be reviewed and understood by the student before evaluation.
