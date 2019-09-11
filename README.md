# Decoders generation for Polar codes

This project is made to generate **channel coding Polar decoders** (unrolled
decoders): **Successive Cancellation** (SC) and **CRC Aided Successive
Cancellation List** (CA-SCL) algorithms are supported. Given a specific codeword
size and Signal Noise Ratio (Eb/N0) the tree structure of the Polar codes gives
the opportunity to completely replace the recursive function calls by a flat and
**fully unrolled source code**.

The code is able to **match some simplifications in the Polar trees to reduce
the decoders latency** like ``Rate 0``, ``Rate 1``, ``Repetition`` (rep) and
``Single Parity Check`` (spc) nodes. It is possible to select which tree cuts to
enable/disable from the command line and see the impact on the generated source
code. For large codewords the size of the generated source code can exceed the
size of the instruction cache of the CPU, this lead to reduced performances. In
this project **a compression algorithm is implemented** to push the codeword
size limit and keep best possible performance.

Additionally, the code generates ``.dot`` files compatible with
[Graphviz](https://www.graphviz.org/) to visualize the Polar tree with the
simplifications used to generate the source code of the decoder. The following
figure is an example of a generated Polar tree with *N = 128*, *K = 64*,
*Eb/N0 = 2.5 dB* and with ``Rate 0``, ``Rate 1``, ``Repetition`` and ``Single
Parity Check`` tree cut simplifications:

![Polar tree](img/polar_tree_(128,64)_(2.5dB)_(r0,r1,rep,spc).svg)

# Scientific publications

This code has been used to generate both software and hardware implementations
in the following publications:

Mathieu Léonardon, Camille Leroux, David Binet, J.M. Pierre Langlois, Christophe Jégo and Yvon Savaria,  
[**Custom Low Power Processor for Polar Decoding**](https://doi.org/10.1109/ISCAS.2018.8351739),  
*The 51st IEEE International Symposium on Circuits & Systems (ISCAS 2018), May 2018.*


Adrien Cassagne, Olivier Aumage, Camille Leroux, Denis Barthou and Bertrand Le Gal,  
[**Energy Consumption Analysis of Software Polar Decoders on Low Power Processors**](https://doi.org/10.1109/EUSIPCO.2016.7760327),  
*The 24nd European Signal Processing Conference (EUSIPCO 2016), September 2016.*


Adrien Cassagne, Bertrand Le Gal, Camille Leroux, Olivier Aumage and Denis Barthou,  
[**An Efficient, Portable and Generic Library for Successive Cancellation Decoding of Polar Codes**](https://doi.org/10.1007/978-3-319-29778-1_19),  
*The 28th International Workshop on Languages and Compilers for Parallel Computing (LCPC 2015), September 2015.*

# How to compile this project

Get the [AFF3CT](https://github.com/aff3ct/aff3ct) library:

    $ git submodule update --init --recursive

Compile the [AFF3CT](https://github.com/aff3ct/aff3ct) library on Linux/MacOS/MinGW:

    $ cd lib/aff3ct
    $ mkdir build
    $ cd build
    $ cmake .. -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-funroll-loops -march=native" -DAFF3CT_COMPILE_EXE="OFF" -DAFF3CT_COMPILE_STATIC_LIB="ON" -DAFF3CT_EXT_STRINGS="OFF" -DCMAKE_INSTALL_PREFIX="install"
    $ make -j4
    $ make install
    $ cd ../../../

Compile this project:

    $ mkdir cmake && mkdir cmake/Modules
    $ cp lib/aff3ct/build/install/lib/cmake/aff3ct-*/* cmake/Modules
    $ mkdir build
    $ cd build
    $ cmake .. -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-funroll-loops -march=native"
    $ make -j4

The source code of this project is in the `src/` directory.
The compiled binary is in `build/bin/polar_decoder_gen`.

# Run example

Generates an Polar SC decoder with a *N = 8*, *K = 4* and optimized for a *Eb/N0 = 2.5 dB*:

    $ ./bin/polar_decoder_gen --dec-type SC -N 8 -K 4 --fbg-noise 2.5

Expected outpout:

    # -------------------------------------------------
    # ----  POLAR DECODER GENERATOR (with AFF3CT)  ----
    # -------------------------------------------------
    # Parameters :
    # * Frozen bits generator -------------------------
    #    ** Fb gen. method       = GA
    #    ** Fb info. bits (K)    = 4
    #    ** Fb codeword size (N) = 8
    #    ** Fb sigma             = 0.749894
    # * Decoder Polar ---------------------------------
    #    ** Type (D)             = SC
    #    ** Implementation       = FAST
    #    ** Info. bits (K)       = 4
    #    ** Codeword size (N)    = 8
    #    ** Code rate (R)        = 0.500000
    #    ** Systematic           = yes
    #    ** Inter frame level    = 1
    #    ** Polar node types     = {R0,R0L,R1,REP,REPL,SPC}
    #    ** Base path            = .
    #
    General statistics:
    -------------------
       Generated decoder file name = ./Decoder_polar_SC_fast_sys_N8_K4_SNR25.hpp
       Associate graph file name   = ./Decoder_polar_SC_fast_sys_N8_K4_SNR25.dot
       Nodes number before pruning = 7
       Nodes number  after pruning = 3
       Terminal nodes (alias pruning rules):
           -      Rate 0:     0 / 3
           -      Rate 1:     0 / 3
           -         Rep:     1 / 3
           -         SPC:     1 / 3
       Non-terminal nodes (alias specialization rules):
           -     Default:     0 / 3
           - Rate 0 left:     0 / 3
           -    Rep left:     1 / 3

    Per layer (graph depth) statistics:
    -----------------------------------
       * Graph depth = 0
          Sub-code length = 8
          Nodes number before pruning = 1
          Nodes number  after pruning = 1
          Terminal nodes (alias pruning rules)
              -      Rate 0:     0 / 1
              -      Rate 1:     0 / 1
              -         Rep:     0 / 1
              -         SPC:     0 / 1
          Non-terminal nodes (alias specialization rules):
              -     Default:     0 / 1
              - Rate 0 left:     0 / 1
              -    Rep left:     1 / 1

       * Graph depth = 1
          Sub-code length = 4
          Nodes number before pruning = 2
          Nodes number  after pruning = 2
          Terminal nodes (alias pruning rules)
              -      Rate 0:     0 / 2
              -      Rate 1:     0 / 2
              -         Rep:     1 / 2
              -         SPC:     1 / 2
          Non-terminal nodes (alias specialization rules):
              -     Default:     0 / 2
              - Rate 0 left:     0 / 2
              -    Rep left:     0 / 2

       * Graph depth = 2
          Sub-code length = 2
          Nodes number before pruning = 4
          Nodes number  after pruning = 0
          Terminal nodes (alias pruning rules)
              -      Rate 0:     0 / 0
              -      Rate 1:     0 / 0
              -         Rep:     0 / 0
              -         SPC:     0 / 0
          Non-terminal nodes (alias specialization rules):
              -     Default:     0 / 0
              - Rate 0 left:     0 / 0
              -    Rep left:     0 / 0

       * Graph depth = 3
          Sub-code length = 1
          Nodes number before pruning = 8
          Nodes number  after pruning = 0
          Terminal nodes (alias pruning rules)
              -      Rate 0:     0 / 0
              -      Rate 1:     0 / 0
              -         Rep:     0 / 0
              -         SPC:     0 / 0
          Non-terminal nodes (alias specialization rules):
              -     Default:     0 / 0
              - Rate 0 left:     0 / 0
              -    Rep left:     0 / 0
    #

# Generated Source Code

The previous command line generates the following Polar tree:

![Polar tree](img/polar_tree_(8,4)_(2.5dB)_(rep,spc).svg)

And the associated source code is:

```cpp
// ...
static const std::vector<bool> Decoder_polar_SC_fast_sys_fb_8_4_25 = {
1, 1, 1, 0, 1, 0, 0, 0};

template <typename B, typename R, class API_polar>
class Decoder_polar_SC_fast_sys_N8_K4_SNR25 : public Decoder_polar_SC_fast_sys<B, R, API_polar>
{
public:
  // ...
  void _decode()
  {
    // ...
    API_polar::template f  <4>(   l,  0+ 0,  0+ 4,         0+ 8, 4);
    API_polar::template rep<4>(s, l,  8+ 0,                0+ 0, 4);
    API_polar::template gr <4>(s, l,  0+ 0,  0+ 4,  0+ 0,  0+ 8, 4);
    API_polar::template spc<4>(s, l,  8+ 0,                4+ 0, 4);
    API_polar::template xo <4>(s,     0+ 0,  0+ 4,         0+ 0, 4);
  }
};
// ...
```

This is an header only class compatible with the
[AFF3CT](https://github.com/aff3ct/aff3ct) simulator. The frozen bits are
statically declared in the ``Decoder_polar_SC_fast_sys_fb_8_4_25`` vector
and the generated code is in the ``_decode()`` method. ``l`` is the vector of
LLRs from the channel and ``s`` is the partial sums vector. The generated source
code looks like a dedicated Polar decoder instruction set. For instance
``API_polar::template f<4>(l, 0+0, 0+4, 0+8, 4);`` means that a ``f``
function is performed four times (``<4>`` from the template parameter and
``4`` from the last method parameter). The ``f`` function is working on the LLRs
(first ``l`` argument in the method). The second method parameter (``0+0``)
specifies the memory location of the left operands for the ``f`` function, the
third method parameter (``0+4``) specifies the memory location of the right
operands for the ``f`` function and the fourth parameter (``0+8``) specifies
where the results on the ``f`` functions will be stored. The same philosophy is
used for the next Polar decoder instructions.
