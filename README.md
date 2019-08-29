# Decoders generation for Polar codes

This project is made to generate Polar decoders (unrolled decoders). Given a specific codeword size and Signal Noise Ratio (SNR) the tree structure of the Polar codes gives the opportunity to completely replace the recursive function calls by a flat and fully unrolled source code.

# How to compile this project

Get the AFF3CT library:

    $ git submodule update --init --recursive

Compile the AFF3CT library on Linux/MacOS/MinGW:

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

Generates an Polar Successive Cancellation (SC) decoder with a 8 bits codeword size (N), 4 information bits (K) and optimized for a SNR of 2.5 dB (Eb/N0):

    $ ./bin/polar_decoder_gen --dec-type SC -N 8 -K 4 --fbg-snr 2.5

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
