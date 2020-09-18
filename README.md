<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-generate-toc again -->
**Table of Contents**

- [About](#about)
- [Installation](#installation)
- [Theory](#theory)
- [Usage](#usage)
- [References](#references)

<!-- markdown-toc end -->
# About

RTAMT-CPP is a C++ library for online monitoring of bounded-future 
Signal Temporal Logic (STL). 

# Installation

## Dependencies

```
sudo apt-get update
sudo apt-get install build-essential cmake uuid-dev
sudo apt-get install libgtest-dev google-mock libgmock-dev
```

## Building the project

```
mkdir bin
cd bin
cmake ../source
make -j4
```

## Generating the grammar

How to compile the grammar. Note that the library is released with the pre-compiled library. The grammar needs to be compiled only if you change the parser or the lexer.

```
cd grammar/stl
java -jar ../../antlr-4.8-complete.jar -package grammar -Dlanguage=Cpp -no-listener -visitor StlLexer.g4 -o ../../source/grammar
java -jar ../../antlr-4.8-complete.jar -package grammar -Dlanguage=Cpp -no-listener -visitor StlParser.g4 -o ../../source/grammar
```

# Theory

RTAMT-CPP is a C++ library for online monitoring of bounded-future 
Signal Temporal Logic (STL). The library is inspired by several theoretical and practical 
works:
- The overall library is inspired by RTAMT and implements the same functionlity in C++ instead of Python
- The bounded-future fragment of STL is inspired by [2]
- The interface-aware interpretation of STL quantitative semantics is inspired by [3]
- The periodic-sampling interpretation of specifications (even in presence of timestamps that are not prefectly periodic) is inpired by [4]
- The translation of bounded-future STL to "equirobust" past STL prior to the monitoring phase is inpired by [2] 

## Specification Language

RTAMT-CPP uses the bounded-future interface-aware 
fragment of Signal Temporal Logic (STL).

The library supports a variant of STL with past and future temporal operators as well as basic arithmetic and absolute value operators. 
Semantics of STL is defined in terms of a robustess degree `rho(phi,w,t)`, a function defined over reals extended with `+inf` and `-inf` that takes as input an STL specification `phi`, an input signal 
`w` and time index `t`, and computes how far is the signal `w` at time `t` from satisfying/violating `phi`. The robustness degree function is defined inductively as follows
(`c` is a real constant, `x` is a variable, `w_x(t)` denotes the value of `w` projected to `x` at time `t`, `a,b` are rational constants such that `0 <= a <= b` and `|w|` is the length of `w`):
```
% Constant
rho(c,w,t) = c

% Variable
rho(x,w,t) = w_x(t)

% Absolute value
rho(abs(phi),w,t) = |rho(phi,w,t)|

% Arithmetic operators
rho(phi + psi,w,t) = rho(phi,w,t) + rho(psi,w,t)
rho(phi - psi,w,t) = rho(phi,w,t) - rho(psi,w,t)
rho(phi * psi,w,t) = rho(phi,w,t) * rho(psi,w,t)
rho(phi / psi,w,t) = rho(phi,w,t) / rho(psi,w,t)

% Numeric predicates
rho(phi <= psi,w,t) = rho(psi,w,t) - rho(phi,w,t) 
rho(phi < psi,w,t) = rho(psi,w,t) - rho(phi,w,t)
rho(phi >= psi,w,t) = rho(phi,w,t) - rho(psi,w,t)
rho(phi >= psi,w,t) = rho(phi,w,t) - rho(psi,w,t)
rho(phi == psi,w,t) = -|rho(phi,w,t) - rho(psi,w,t)|
rho(phi !== psi,w,t) = |rho(phi,w,t) - rho(psi,w,t)|

% Boolean operators
rho(not(phi),w,t) = -rho(phi,w,t)
rho(phi or psi,w,t) = max(rho(phi,w,t),rho(psi,w,t))
rho(phi and psi,w,t) = min(rho(phi,w,t),rho(psi,w,t))
rho(phi -> psi,w,t) = max(-rho(phi,w,t),rho(psi,w,t))
rho(phi <-> psi,w,t) = -|rho(phi,w,t) - rho(psi,w,t)|
rho(phi xor psi,w,t) = |rho(phi,w,t) - rho(psi,w,t)|

% Events
rho(rise(phi),w,t) = rho(phi,w,t)                     if t=0
                     min(-rho(phi,w,t-1),rho(phi,w,t) otherwise
rho(fall(phi),w,t) = -rho(phi,w,t)                    if t=0
                     min(rho(phi,w,t-1),-rho(phi,w,t) otherwise

% Past untimed temporal operators
rho(once phi,w,t) = max_{t' in [0,t]} rho(phi,w,t')
rho(historically phi,w,t) = min_{t' in [0,t]} rho(phi,w,t')
rho(phi since psi,w,t) = max_{t' in [0,t]}(min(rho(psi,w,t'), min_{t'' in (t',t]}rho(psi,w,t') rho(phi,w,t'')))

% Past untimed temporal operators
rho(once[a,b] phi,w,t) = -inf                                                            if t-a < 0
                         max_{t' in ([0,t] intersect [t-a,t-b])} rho(phi,w,t')           otherwise
rho(historically[a,b] phi,w,t) = inf                                                     if t-a < 0
                                 min_{t' in ([0,t] intersect [t-a,t-b])} rho(phi,w,t')   otherwise
rho(phi since[a,b] psi,w,t) = -inf                                                       if t-a < 0 
                              max_{t' in ([0,t] intersect [t-a,t-b]} (min(rho(psi,w,t'), 
                              min_{t'' in (t',t]}rho(psi,w,t') rho(phi,w,t'')))          otherwise

% Future untimed temporal operators
rho(eventually phi,w,t) = max_{t' in [0,t]} rho(phi,w,t')
rho(always phi,w,t) = min_{t' in [0,t]} rho(phi,w,t')

% Future timed temporal operators
rho(eventually[a,b] phi,w,t) = -inf                                                     if t+a >= |w|
                               max_{t' in ([0,t] intersect [t+a,t+b])} rho(phi,w,t')    otherwise
rho(always[a,b] phi,w,t) = inf                                                          if t+a >= |w|
                           min_{t' in ([0,t] intersect [t+a,t+b])} rho(phi,w,t')        otherwise
rho(phi until[a,b] psi,w,t) = -inf                                                      if t+a >= |w|
                              max_{t' in ([0,t] intersect [t+a,t+b]}(min(rho(psi,w,t'), 
                              min_{t'' in [t,t')}rho(psi,w,t') rho(phi,w,t'')))         otherwise   
```

We define the robustness degree `rho(phi,w)` as `rho(phi,w,0)`.

There are several important points to note about the above syntax and semantics:
- The library allows only bounded-future STL specifications, meaning that _unbounded_ future operators `always` and `eventually` can appear only at the top level of the specification. For example, `always(x<=2)` is a bounded-future STL specification, while `always(eventually(x<=2))` is not.
- The library does not allow _unbounded_ `until` operator.
- The library uses _non-standard_ semantics for unbounded `always` and `eventually` operators. For instance, standard TL semantics says that `always phi` holds at time `t` iff `phi` holds at all future times `t'>=t`. This interpretation cannot be monitored in online fashion. We define semantics that says that `always phi` holds at time `t` iff `phi` has been continuously holding so far. Note that this interpretation of `always` is equivalent to the `historically`operator. The situation is symmetric for the non-standard semantics of  `eventually` and `once`.

We can see from the semantics of bounded-future STL that the direct evaluation of a formula `phi` at time `t` may depend on inputs at `t'>t` that have not arrived yet.
The library monitors bounded-future STL formulas with a fixed _delay_. In order to compute `rho(phi,w,t)`, the monitor waits for all inputs required to evaluate `phi` to become available before computing the robustness degree. This delay is fixed and depends on the specification. For instance, the specification `always((req >= 3) -> eventually[0:2]always[0:3](gnt >= 3)`is evaluated with delay `5` - the time needed to capture all inputs required for evaluating bounded `eventually` and `always` operators. We refer the reader to [2] for algorithmic details regarding monitoring with delay.

# Usage

## Example of a standard usage

The use of the library is illustrated with the following example.

```
#include <rtamt/stl_specification.hpp>
#include <rtamt/stl_exception.hpp>

using namespace std;
using namespace rtamt;
using In = Input;

int main(int argc, char **argv) {
    StlSpecification spec;

    spec.name("Bounded-response Request-Grant");
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.var_io_type("req", StlIOType::IN);
    spec.var_io_type("gnt", StlIOType::OUT);
    
    spec.default_unit(Unit::MS);
    spec.sampling_period(10, Unit::MS, 0.1);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = (req >= 3) -> (eventually[0:50ms](gnt >= 3))");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(10, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(20, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(30, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(40, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(50, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    out = spec.update(60, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    out = spec.update(70, {In("req", 0.0), In("gnt", 6.0)}); // out = 3
    out = spec.update(80, {In("req", 0.0), In("gnt", 6.0)}); // out = 3
    out = spec.update(90, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    out = spec.update(100, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    out = spec.update(110, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
}


```
The user first names the specification using the 
`spec.name()` function. The explicit naming of the specification 
is optional and is intended to facilitate tracing of the 
formal specifications and monitors to the requirements. 
The default value for the STL specification name is 
`"STL Specification"`.

Next, the user needs to declare typed variables that are used 
in the specification. In this example, 
the program declares three variables `req`, `gnt` and 
`out`, all of them of type `float`.

In addition, the program declares `req` as _input_ (`StlIOType::IN`) 
and `gnt` as _output_ (`StlIOType::OUT`) variable. The definition 
of the I/O signatures for specification variables is _optional_. 
Variables have by default a 
neutral _default_ type (`StlIOType::DEFAULT`). The I/O signature 
indicates whether a variable is an input (output) 
to the system-under-scrutiny (SuS) and 
not to the monitor and is used to support interface-aware (IA) 
STL semantics.

The program then declares the quantitative IA-STL semantics used 
for the evaluation. The options are _standard_ 
(`StlSemantics::STANDARD`), 
_output-robustness_ (`StlSemantics::OUT_ROBUSTNESS`), 
_input-vacuity_ (`StlSemantics::IN_VACUITY`),    
_input-robustness_ (`StlSemantics::IN_ROBUSTNESS`) and 
_output-vacuity_ (`StlSemantics::OUT_VACUITY`). In this example, the program uses _standard_ 
semantics.  Explicit choice of the semantics is _optional_. By default, standard semantics 
is used. 

Next, the program defines the _default_ _time_ unit to _milliseconds_ (`spec.default_unit(Unit::MS)`). The default time unit is used to define time units of:
- the input sample timestamps
- the timing bounds of the temporal operators (unless explicitly 
using a different time unit)
- the sampling period (unless explicitly 
using a different time unit)

Finally, the program defines the duration of the _sampling_ _period_ as well as its tolerance (`spec.sampling_period(100, Unit::MS, 0.1)`). The sampling period is defined to be 100ms with 10% tolerance. We recall that RTAMT-CPP implements a _discrete_ _time_ monitoring algorithm that assumes that consecutive samples have a _perfect_ distance defined by the sampling period. This level of accuracy is often not possible, and the user allows defining a _tolerance_ value (between 0 and 100% of the sampling period value) for the actual distance between two consecutive sample timestamps.

## Resetting the monitoring state

RTAMT-CPP allows resetting the internal state of the monitor. After invoking `reset()`, the monitor assumes that the next update starts from the initial state of the monitor. We note that the reset _only_ resets the internal state of the monitor, but _not_ the specification. All the attributes of the specification (name, specification tex, variables and their types and I/O signatures, default unit and sampling time period) remain intact. The following program shows how to use the reset. 

```
#include <rtamt/stl_specification.hpp>
#include <rtamt/stl_exception.hpp>

using namespace std;
using namespace rtamt;
using In = Input;

int main(int argc, char **argv) {
    StlSpecification spec;

    spec.name("Bounded-response Request-Grant");
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.var_io_type("req", StlIOType::IN);
    spec.var_io_type("gnt", StlIOType::OUT);
    
    spec.default_unit(Unit::MS);
    spec.sampling_period(10, Unit::MS, 0.1);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = (req >= 3) -> (eventually[0:50ms](gnt >= 3))");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(10, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(20, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(30, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(40, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(50, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    out = spec.update(60, {In("req", 0.0), In("gnt", 0.0)}); // out = 3

    spec.reset();

    out = spec.update(70, {In("req", 0.0), In("gnt", 6.0)}); // out = inf
    out = spec.update(80, {In("req", 0.0), In("gnt", 6.0)}); // out = inf
}
```

## Working with time units and timing assumptions

The default unit in RTAMT is seconds, and the default expected period between two consecutive input samples is `1s` with `10%` tolerance. The following program uses these default values to implicitely set up the monitor. The specification intuitively states that whenever the `req` is above `3`, eventually within `5s` `gnt` also goes above `3`. The user feeds the monitor with values timestamped _exactly_ `1s` apart from each other. It follows that the periodic sampling assumption holds.

RTAMT-CPP counts how many times the periodic sampling assumption has been violated up to the moment of being invoked via the `sampling_violation_counter()` function. In this example, this violation obviously occurs `0` times.

```
#include <rtamt/stl_specification.hpp>
#include <rtamt/stl_exception.hpp>

using namespace std;
using namespace rtamt;
using In = Input;

int main(int argc, char **argv) {
    StlSpecification spec;

    spec.name("Bounded-response Request-Grant");
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.var_io_type("req", StlIOType::IN);
    spec.var_io_type("gnt", StlIOType::OUT);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = (req >= 3) -> (eventually[0:5](gnt >= 3))");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(1, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(2, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(3, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(4, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(5, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    out = spec.update(6, {In("req", 0.0), In("gnt", 0.0)}); // out = 3

    double nb_violations = spec.sampling_violation_counter(); // nb_violations = 0
}
```
The same program, but with slightly different timestamps still reports `0` number of periodic sampling assumption violations. This is because the difference between all consecuting sampling timestamps remains within the (implicitely) specified `10%` tolerance.


```
    ...
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(1.01, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(1.98, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(3.03, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(4.01, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(4.99, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    out = spec.update(6.01, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    
    double nb_violations = spec.sampling_violation_counter(); // nb_violations = 0
```
On the other hand, the following sequence of inputs results in `1` reported violation of periodic sampling assumption. This is because the second input is `1.11s` away from the first sample, which is `11%` above the assumed `1s` period. 

```
    ...
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(1.11, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(2.08, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(3.03, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(4.01, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(4.99, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    out = spec.update(6.01, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    
    double nb_violations = spec.sampling_violation_counter(); // nb_violations = 1
```
This same sequence of inputs results in `0` reported violation of periodic sampling assumption if we explicitely set the sampling period tolerance value to `20%`. 

```
    ...
    spec.sampling_period(1, Unit::S, 0.2);
    ...
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(1.11, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(2.08, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(3.03, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(4.01, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(4.99, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    out = spec.update(6.01, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    
    double nb_violations = spec.sampling_violation_counter(); // nb_violations = 1
```

The user can also explicitely set the default unit, as well as the expected period and tolerance. In that case, the user must ensure that the timing bounds declared in the specification are divisible by the sampling period. The following specification is correct, since the sampling period is set to `500ms`, the default unit is set to seconds, and the specification implicitely defines the bound from `0.5s = 500ms` and `1.5s = 1500ms`, i.e. between `1` amd `3` sampling periods. 

```
#include <rtamt/stl_specification.hpp>
#include <rtamt/stl_exception.hpp>

using namespace std;
using namespace rtamt;
using In = Input;

int main(int argc, char **argv) {
    StlSpecification spec;

    spec.name("Bounded-response Request-Grant");
    
    spec.declare_var("req", Type::FLOAT);
    spec.declare_var("gnt", Type::FLOAT);
    spec.declare_var("out", Type::FLOAT);
    
    spec.var_io_type("req", StlIOType::IN);
    spec.var_io_type("gnt", StlIOType::OUT);
    
    spec.default_unit(Unit::S);
    spec.sampling_period(500, Unit::MS, 0.1);
    
    spec.semantics(StlSemantics::STANDARD);
    
    spec.spec("out = (req >= 3) -> (eventually[0.5:1.5](gnt >= 3))");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(0.5, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(1, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(1.5, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(2, {In("req", 6.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(2.5, {In("req", 0.0), In("gnt", 0.0)}); // out = 3
    out = spec.update(3, {In("req", 0.0), In("gnt", 0.0)}); // out = 3

    double nb_violations = spec.sampling_violation_counter(); // nb_violations = 0
}
```
The following defines the same program, but now with `ms` as the default unit. 

```
    ...
    spec.default_unit(Unit::MS);
    spec.sampling_period(500, Unit::MS, 0.1);
    ...
    spec.spec("out = (req >= 3) -> (eventually[500:1500](gnt >= 3))");
    
    spec.parse();
    
    double out;
    
    out = spec.update(0, {In("req", 0.0), In("gnt", 0.0)}); // out = inf
    out = spec.update(500, {In("req", 0.0), In("gnt", 0.0)}); // out = inf

    double nb_violations = spec.sampling_violation_counter(); // nb_violations = 0
}
```

The following program throws an exception - the temporal bound is defined between `500ms` and `1500ms`, while the sampling period equals to `1s = 1000ms`. 

```
    ...
    spec.default_unit(Unit::MS);
    spec.sampling_period(1, Unit::S, 0.1);
    ...
    spec.spec("out = (req >= 3) -> (eventually[500:1500](gnt >= 3))");
    ...
    spec.parse();
    ...
    
}
```

Finally, the following program is correct, because the temporal bound is explicitely defined between `500s` and `1500s`, while the sampling period equals to `1s`. 

```
    ...
    spec.default_unit(Unit::MS);
    spec.sampling_period(1, Unit::S, 0.1);
    ...
    spec.spec("out = (req >= 3) -> (eventually[500s:1500s](gnt >= 3))");
    ...
    spec.parse();
    ...
    
}
```
 
# References

- [1] Dejan Nickovic, Tomoya Yamaguchi: RTAMT: Online Robustness Monitors from STL. CoRR abs/2005.11827 (2020)
- [2] Stefan Jaksic, Ezio Bartocci, Radu Grosu, Reinhard Kloibhofer, Thang Nguyen, Dejan Nickovic: From signal temporal logic to FPGA monitors. MEMOCODE 2015: 218-227
- [3] Thomas Ferrère, Dejan Nickovic, Alexandre Donzé, Hisahiro Ito, James Kapinski: Interface-aware signal temporal logic. HSCC 2019: 57-66
- [4] Thomas A. Henzinger, Zohar Manna, Amir Pnueli: What Good Are Digital Clocks? ICALP 1992: 545-558

