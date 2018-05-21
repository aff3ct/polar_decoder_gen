#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

#include "Generator_polar_TTA.hpp"

using namespace aff3ct::generator;
using namespace aff3ct::tools;

Generator_polar_TTA
::Generator_polar_TTA(const int& K,
					  const int& N,
					  const float& snr,
					  const std::vector<bool>& frozen_bits,
					  const std::vector<tools::Pattern_polar_i*> &patterns,
					  const tools::Pattern_polar_i &pattern_rate0,
					  const tools::Pattern_polar_i &pattern_rate1,
					  std::string mother_class_name,
					  std::string MOTHER_CLASS_NAME,
					  std::ostream &dec_stream        ,
					  std::ostream &short_dec_stream  ,
					  std::ostream &graph_stream      ,
					  std::ostream &short_graph_stream,
					  const bool enable_short_decoder)
: Generator_polar(K,
                  N,
                  snr,
                  frozen_bits,
                  patterns,
                  pattern_rate0,
                  pattern_rate1,
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
	const auto n_lines = (int)ceil((float)frozen_bits.size() / 32.f);
	stringstream fbits;
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
		if (i < (int)frozen_bits.size()) fbits << endl;
	}

	string pragma_name = MOTHER_CLASS_NAME + "_N"   + to_string(N) +
						 "_K"   + to_string(K) +
						 "_SNR" + to_string((int)(snr*10)) + "_HPP_";
	stream << "#ifndef " << pragma_name                                                                  << endl;
	stream << "#define " << pragma_name                                                                  << endl;
	stream                                                                                               << endl;
	stream << "#include <vector>"                                                                        << endl;
	stream << "#include <cassert>"                                                                       << endl;
	stream                                                                                               << endl;
	stream << "#include \"../" << mother_class_name << ".hpp\""                                          << endl;
	stream                                                                                               << endl;
	stream << "namespace aff3ct"                                                                         << endl;
	stream << "{"                                                                                        << endl;
	stream << "namespace module"                                                                         << endl;
	stream << "{"                                                                                        << endl;
	stream << "static const std::vector<bool> " << fbits_name << " = {"                                  << endl;
	stream << fbits.str() << "};"                                                                        << endl;
	stream                                                                                               << endl;

}

void Generator_polar_TTA
::generate_footer(std::ostream &stream)
{
	stream << "}"      << endl;
	stream << "}"      << endl;
	stream << "#endif" << endl;
}