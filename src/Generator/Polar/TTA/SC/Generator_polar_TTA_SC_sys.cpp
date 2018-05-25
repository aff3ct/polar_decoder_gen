#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

#include "Generator_polar_TTA_SC_sys.hpp"

using namespace aff3ct::tools;
using namespace aff3ct::generator;

Generator_polar_TTA_SC_sys
::Generator_polar_TTA_SC_sys(const int& K,
                         const int& N,
                         const float& snr,
                         const std::vector<bool>& frozen_bits,
                         const std::vector<Pattern_polar_i*> &patterns,
                         const Pattern_polar_i &pattern_rate0,
                         const Pattern_polar_i &pattern_rate1,
                         ostream &dec_stream,
                         ostream &short_dec_stream,
                         ostream &graph_stream,
                         ostream &short_graph_stream)
: Generator_polar_TTA(K,
                      N,
                      snr,
                      frozen_bits,
                      patterns,
                      pattern_rate0,
                      pattern_rate1,
                      "Decoder_polar_SC_fast_sys",
                      "DECODER_POLAR_SC_FAST_SYS",
                      dec_stream,
					  dec_stream,
                      graph_stream,
					  graph_stream,
                      false)
{
}

Generator_polar_TTA_SC_sys
::~Generator_polar_TTA_SC_sys()
{
}
//Decoder               (K, N, n_frames, 1, name),
void Generator_polar_TTA_SC_sys
::generate_class_header(const std::string   class_name,
                        const std::string   fbits_name,
                              std::ostream &stream1,
                              std::ostream &stream2)
{
	stream1        << "#include \"Decoder_simd_unrolled.h\"" << endl;
	stream1        <<                                           endl;
	stream1        << "void Decoder_simd_unrolled::decode()" << endl;
	stream1        << "{"                                    << endl;
	stream1 << tab << "char64 l_a;"                          << endl;
	stream1 << tab << "char64 l_b;"                          << endl;
	stream1 << tab << "char64 l_c;"                          << endl;
	stream1 << tab << "char8  temp_s;"                       << endl;
	stream1 << tab <<                                           endl;
}

void Generator_polar_TTA_SC_sys
::generate_class_footer(std::ostream &stream)
{
	stream << "};" << "" << endl;
}

void Generator_polar_TTA_SC_sys
::recursive_generate_decoder(const Binary_node<Pattern_polar_i>* node_curr, ostream &stream)
{
	n_nodes_before_compression++;

	if (!node_curr->is_leaf()) // stop condition
	{
		if (!node_curr->get_c()->apply_f().empty())
			stream << tab << node_curr->get_c()->apply_f();

		this->recursive_generate_decoder(node_curr->get_left(), stream); // recursive call

		if (!node_curr->get_c()->apply_g().empty())
			stream << tab << node_curr->get_c()->apply_g();

		this->recursive_generate_decoder(node_curr->get_right(), stream); // recursive call
	}

	if (!node_curr->get_c()->apply_h().empty())
		stream << tab << node_curr->get_c()->apply_h();
}

void Generator_polar_TTA_SC_sys
::recursive_generate_short_decoder(const Binary_node<Pattern_polar_i>* node_curr, ostream &stream)
{
	// TODO
}
