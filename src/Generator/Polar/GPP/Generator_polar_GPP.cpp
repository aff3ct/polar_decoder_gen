#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include "Generator_polar_GPP.hpp"

using namespace aff3ct;
using namespace aff3ct::generator;

Generator_polar_GPP
::Generator_polar_GPP(const int& K,
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

Generator_polar_GPP
::~Generator_polar_GPP()
{
}

void Generator_polar_GPP
::generate_header(const std::string mother_class_name, const std::vector<bool> &frozen_bits,
				  const std::string fbits_name, std::ostream &stream)
{
	const auto n_lines = (int)ceil((float)frozen_bits.size() / 32.f);
	std::stringstream fbits;
	auto i = 0;
	for (auto j = 0; j < n_lines; j++)
	{
		auto k = 0;
		while (k < 32 && i < (int)frozen_bits.size())
		{
			fbits << frozen_bits[i];
			if (i < (int)frozen_bits.size() -1) fbits << ", ";
			i++; k++;
		}
		if (i < (int)frozen_bits.size()) fbits << std::endl;
	}

	std::string pragma_name = MOTHER_CLASS_NAME + "_N"   + std::to_string(N) +
	                          "_K"   + std::to_string(K) +
	                          "_SNR" + std::to_string((int)(snr*10)) + "_HPP_";
	stream << "#ifndef " << pragma_name                                 << std::endl;
	stream << "#define " << pragma_name                                 << std::endl;
	stream                                                              << std::endl;
	stream << "#include <vector>"                                       << std::endl;
	stream << "#include <cassert>"                                      << std::endl;
	stream                                                              << std::endl;
	stream << "#include \"../" << mother_class_name << ".hpp\""         << std::endl;
	stream                                                              << std::endl;
	stream << "namespace aff3ct"                                        << std::endl;
	stream << "{"                                                       << std::endl;
	stream << "namespace module"                                        << std::endl;
	stream << "{"                                                       << std::endl;
	stream << "static const std::vector<bool> " << fbits_name << " = {" << std::endl;
	stream << fbits.str() << "};"                                       << std::endl;
	stream                                                              << std::endl;
}

void Generator_polar_GPP
::generate_footer(std::ostream &stream)
{
	stream << "}"      << std::endl;
	stream << "}"      << std::endl;
	stream << "#endif" << std::endl;
}