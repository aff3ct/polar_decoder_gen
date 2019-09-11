#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include "Generator_polar_TTA.hpp"

using namespace aff3ct;
using namespace aff3ct::generator;

Generator_polar_TTA
::Generator_polar_TTA(const int& K,
                      const int& N,
                      const float& snr,
                      const std::vector<bool>& frozen_bits,
                      const std::vector<tools::Pattern_polar_i*> &patterns,
                      const int idx_r0,
                      const int idx_r1,
                      std::string mother_class_name,
                      std::string MOTHER_CLASS_NAME,
                      std::ostream &dec_stream,
                      std::ostream &short_dec_stream,
                      std::ostream &graph_stream,
                      std::ostream &short_graph_stream,
                      const bool enable_short_decoder)
: Generator_polar(K,
                  N,
                  snr,
                  frozen_bits,
                  patterns,
                  idx_r0,
                  idx_r1,
                  mother_class_name,
                  MOTHER_CLASS_NAME,
                  dec_stream,
                  short_dec_stream,
                  graph_stream,
                  short_graph_stream,
                  enable_short_decoder)
{
}

Generator_polar_TTA
::~Generator_polar_TTA()
{
}

void Generator_polar_TTA
::generate_header(const std::string mother_class_name, const std::vector<bool> &frozen_bits,
                  const std::string fbits_name, std::ostream &stream)
{
}

void Generator_polar_TTA
::generate_footer(std::ostream &stream)
{
}